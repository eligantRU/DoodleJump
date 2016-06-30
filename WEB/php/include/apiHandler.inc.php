<?php
    class ApiHandler
    {
        private $m_method = null;
        private $m_request = null;
        private $m_dbHandler = null;

        function __construct($method, $request)
        {
            $this->m_dbHandler = new DbHandler(DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT);

            $this->m_method = $method;
            $this->m_request = $this->clearRequest($request);
        }

        public function handle()
        {
            $response = null;

            switch ($this->m_method)
            {
                case "GET":;
                    $response = $this->getResponseByGet($this->m_request);
                    break;
                case "POST":
                    $response = $this->getResponseByPost($this->m_request);
                    break;
                case "PUT":
                    break;
                case "UPDATE":
                    break;
                case "DELETE":
                    break;
                default:
                    break;
            }
            return $response;
        }

        private function getRecords($num)
        {
            $records = $this->m_dbHandler->queryGetAssoc("SELECT
                                                            nickname, score
                                                          FROM
                                                            records
                                                          ORDER BY
                                                            score DESC
                                                          LIMIT
                                                            0, {$num}");
            foreach ($records as $record)
            {
                strval($record["nickname"]);
                intval($record["score"]);
            }
            return json_encode($records, JSON_NUMERIC_CHECK);
        }

        private function getAllRecords()
        {
            $records = $this->m_dbHandler->queryGetAssoc("SELECT
                                                            nickname, score
                                                          FROM
                                                            records
                                                          ORDER BY
                                                            score DESC");
            foreach ($records as $record)
            {
                strval($record["nickname"]);
                intval($record["score"]);
            }
            return json_encode($records, JSON_NUMERIC_CHECK);
        }

        private function addRecord($nickname, $score)
        {
            $this->m_dbHandler->query("INSERT INTO records
                                         (nickname, score)
                                       VALUES
                                         ('{$nickname}', '{$score}')");
        }

        private function updateRecord($nickname, $score)
        {
            $this->m_dbHandler->query("UPDATE
                                         records
                                       SET
                                         score = {$score}
                                       WHERE
                                         nickname = '{$nickname}'");
        }

        private function clearRequest($request)
        {
            $request = explode("/", trim($request, "/"));
            foreach ($request as $data)
            {
                $this->m_dbHandler->quote($data);
            }
            return $request;
        }

        private function getResponseByGet($request)
        {
            $response = null;

            switch ($this->getTaskByGet($request))
            {
                case GET_N_RECORDS:
                    $response = $this->getRecords($request[1]);
                    break;
                case GET_ALL_RECORDS:
                    $response = $this->getAllRecords();
                    break;
                default:
                    break;
            }
            return $response;
        }

        private function getResponseByPost($request)
        {
            $response = null;

            switch ($this->getTaskByPost($request))
            {
                case ADD_RECORD:
                    $this->addRecord($request[1], $request[2]);
                    break;
                case UPDATE_RECORD:
                    $this->updateRecord($request[1], $request[2]);
                    break;
                default:
                    break;
            }
            return $response;
        }

        private function getTaskByGet($request)
        {
            $task = UNEXPECTED_TASK;

            if (count($request) == 2 && $request[0] == "records")
            {
                $task = GET_N_RECORDS;
            }
            elseif (count($this->m_request) == 1 && $request[0] == "records")
            {
                $task = GET_ALL_RECORDS;
            }
            return $task;
        }

        private function getTaskByPost($request)
        {
            $task = UNEXPECTED_TASK;

            if (count($request) == 3 && $request[0] == "record")
            {
                $userInfo = $this->m_dbHandler->queryGetAssoc("SELECT
                                                                 nickname, score
                                                               FROM
                                                                 records
                                                               WHERE
                                                                 nickname = '{$request[1]}'");
                if (!empty($userInfo))
                {
                    if ($userInfo[0]["score"] < $request[2])
                    {
                        $task = UPDATE_RECORD;
                    }
                }
                else
                {
                    $task = ADD_RECORD;
                }
            }
            return $task;
        }
    }
