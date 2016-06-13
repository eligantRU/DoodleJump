<?php
    function getFromPost($param, $defaultValue = "")
    {
        return isset($_POST[$param]) ? $_POST[$param] : defaultValue;
    }

    function getFromGet($param, $defaultValue = "")
    {
        return isset($_GET[$param]) ? $_GET[$param] : defaultValue;
    }
