<?php
    require_once("php/include/common.inc.php");
    require_once("libs/Smarty.class.php");
    $smarty = new Smarty();
    // $smarty->setCaching(Smarty::CACHING_LIFETIME_CURRENT); // Only for release

    $dbHandler = new DbHandler(DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT);
    $records = $dbHandler->queryGetAssoc("SELECT nickname, score FROM records ORDER BY score DESC LIMIT 0, 100");

    $smarty->assign("records", $records);
    $smarty->display("records.tpl");
