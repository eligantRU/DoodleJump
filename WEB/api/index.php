<?php
    require_once("../php/include/common.inc.php");

    if (array_key_exists("PATH_INFO", $_SERVER))
    {
        $apiHandler = new ApiHandler($_SERVER["REQUEST_METHOD"], $_SERVER["PATH_INFO"]);
        $response = $apiHandler->handle();
        echo($response);
    }
