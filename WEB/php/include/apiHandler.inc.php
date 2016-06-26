<?php
    class apiHandler
    {
        private $method = null;
        private $request = null;
        private $dbHandler = null;

        function __construct($method, $request)
        {
            $this->dbHandler = new dbHandler(DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT);

            $this->method = $method;
            $this->request = $this->clearRequest($request);
        }

        public function handle()
        {
            $response = null;
            switch ($this->method)
            {
                case "GET":;
                    if (count($this->request) == 2 && $this->request[0] == "records")
                    {
                        $response = $this->getRecords($this->request[1]);
                    }
                    elseif (count($this->request) == 1 && $this->request[0] == "records")
                    {
                        $response = $this->getAllRecords();
                    }
                    break;
                case "POST":
                    if (count($this->request) == 3 && $this->request[0] == "record")
                    {
                        $userInfo = $this->dbHandler->queryGetAssoc("SELECT nickname, score FROM records WHERE nickname = '{$this->request[1]}'");
                        if (!empty($userInfo))
                        {
                            if ($userInfo[0]["score"] < $this->request[2])
                            {
                                $this->updateRecord($this->request[1], $this->request[2]);
                            }
                        }
                        else
                        {
                            $this->addRecord($this->request[1], $this->request[2]);
                        }
                    }
                    break;
                case "PUT":
                    break;
                case "UPDATE":
                    break;
                case "DELETE":
                    break;
                default:
                    echo("Invalid method");
                    break;
            }
            return $response;
        }

        private function clearRequest($request)
        {
            $request = explode("/", trim($request, "/"));
            foreach ($request as $data)
            {
                $data = $this->dbHandler->quote($data);
            }
            return $request;
        }

        private function getRecords($num)
        {
            $records = $this->dbHandler->queryGetAssoc("SELECT nickname, score FROM
                                                           records
                                                       ORDER BY
                                                            score DESC
                                                       LIMIT
                                                           0, {$num}");
            foreach ($records as $record)
            {
                $record["nickname"] = strval($record["nickname"]);
                $record["score"] = intval($record["score"]);
            }
            return json_encode($records, JSON_NUMERIC_CHECK);
        }

        private function getAllRecords()
        {
            $records = $this->dbHandler->queryGetAssoc("SELECT nickname, score FROM
                                                           records
                                                       ORDER BY
                                                            score DESC");
            foreach ($records as $record)
            {
                $record["nickname"] = strval($record["nickname"]);
                $record["score"] = intval($record["score"]);
            }
            return json_encode($records, JSON_NUMERIC_CHECK);
        }

        private function addRecord($nickname, $score)
        {
            $this->dbHandler->query("INSERT INTO records
                                         (nickname, score)
                                     VALUES
                                         ('{$nickname}', '{$score}')");
        }

        private function updateRecord($nickname, $score)
        {
            $this->dbHandler->query("UPDATE records
                                         SET score = {$score}
                                     WHERE
                                         nickname = '{$nickname}'");
        }
    }
