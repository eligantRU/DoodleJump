<?php
    require_once("libs/Smarty.class.php");
    $smarty = new Smarty();
    // $smarty->setCaching(Smarty::CACHING_LIFETIME_CURRENT); // Only for release

    $smarty->display("index.tpl");