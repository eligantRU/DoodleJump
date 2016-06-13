<?php
    require_once("config.inc.php");

    $fileTree = scandir(INCLUDE_DIR);
    foreach ($fileTree as $fileName)
    {
        if (is_file(INCLUDE_DIR . "/" . $fileName) && stristr($fileName, ".inc.php"))
        {
            require_once($fileName);
        }
    }
