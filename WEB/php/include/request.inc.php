<?php
    class Request
    {
        static public function getFromPost($param, $defaultValue = "")
        {
            return isset($_POST[$param]) ? $_POST[$param] : $defaultValue;
        }

        static public function getFromGet($param, $defaultValue = "")
        {
            return isset($_GET[$param]) ? $_GET[$param] : $defaultValue;
        }
    }
