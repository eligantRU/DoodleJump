<?php
    require_once("common.inc.php");

    class dbHandler
    {
        private $m_mysqli = null;
        function __construct()
        {
            $this->m_mysqli = new mysqli(DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT);
            $this->m_mysqli->set_charset("utf8");
            if (mysqli_connect_errno())
            {
                die("Unable to connect to DB die to error: " .  mysqli_connect_error());
            }
        }

        public function query($query)
        {
            $result = $this->m_mysqli->query($query);
            return ($result !== false);
        }

        public function queryGetAsoc($query)
        {
            $data = array();
            $result = $this->m_mysqli->query($query);
            if ($result)
            {
                while ($row = $result->fetch_assoc())
                {
                    array_push($data, $row);
                }
            }
            return $data;
        }

        public function getLastInsertId()
        {
            return $this->m_mysqli->insert_id;
        }

        public function quote($value)
        {
            return $this->m_mysqli->real_escape_string($value);
        }
    }
