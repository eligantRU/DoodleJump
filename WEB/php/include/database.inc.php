<?php
    require_once("common.inc.php");

    class dbHandler
    {
        private $m_mysqli = null;

        function __construct($dbHost, $dbUser, $dbPass, $dbName, $dbPort)
        {
            $this->m_mysqli = new mysqli($dbHost, $dbUser, $dbPass, $dbName, $dbPort);
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

        public function queryGetAssoc($query)
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

        public function quote($query)
        {
            return $this->m_mysqli->real_escape_string($query);
        }

        public function getRows($query)
        {
            $bla = $this->m_mysqli->query($query);
            return $bla->fetch_row();
        }
    }
