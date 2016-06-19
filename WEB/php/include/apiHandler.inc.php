<?php
    class apiHandler
    {
        private $method = null;
        private $request = null;
        private $dbHandler = null;

        function __construct($method, $request)
        {
            $this->dbHandler = new dbHandler();

            $this->method = $method;
            $this->request = $this->clearRequest($request);
        }

        public function handle()
        {
            $response = null;
            switch ($this->method)
            {
                case "GET":
                    if ($this->request[0] == "records") // 127.0.0.1:4001/web_backend/DoodleJump/api/index.php/records
                    {
                        $response = $this->getRecords($this->request[1]);
                    }
                    break;
                case "POST":
                    if ($this->request[0] == "record") // 127.0.0.1:4001/web_backend/DoodleJump/api/index.php/record/me
                    {
                        $this->addRecord($this->request[1], $this->request[2]);
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
            return $request = explode("/", trim($request, "/"));
        }

        private function getRecords($num)
        {
            $records = $this->dbHandler->queryGetAsoc("SELECT nickname, score FROM
                                                           records
                                                       ORDER BY
                                                            score DESC
                                                       LIMIT
                                                           0, {$num}");

            foreach ($records as $record)
            {
                $record["score"] = intval($record["score"]);
            }
            
            return json_encode($records, JSON_NUMERIC_CHECK);
        }

        private function addRecord($nickname, $score)
        {
            $records = $this->dbHandler->query("INSERT INTO records
                                                    (nickname, score)
                                                VALUES
                                                    ('{$nickname}', '{$score}')");
        }
    }
