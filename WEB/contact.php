<?php
    require_once("libs/Smarty.class.php");

    $smarty = new Smarty();
    $smarty->template_dir = "template";
    $smarty->compile_dir  = "template_c";
    $smarty->cache_dir = "cache";
    $smarty->config_dir = "configs";
    // $smarty->setCaching(Smarty::CACHING_LIFETIME_CURRENT); // Only for release

    $smarty->display("contact.tpl");
