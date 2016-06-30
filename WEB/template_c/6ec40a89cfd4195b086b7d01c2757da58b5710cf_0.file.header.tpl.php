<?php
/* Smarty version 3.1.29, created on 2016-06-21 10:13:27
  from "E:\!git\!web_backend\server2go\server2go\htdocs\web_backend\DoodleJump\templates\header.tpl" */

if ($_smarty_tpl->smarty->ext->_validateCompiled->decodeProperties($_smarty_tpl, array (
  'has_nocache_code' => false,
  'version' => '3.1.29',
  'unifunc' => 'content_5768f7278d1f95_33455454',
  'file_dependency' => 
  array (
    '6ec40a89cfd4195b086b7d01c2757da58b5710cf' => 
    array (
      0 => 'E:\\!git\\!web_backend\\server2go\\server2go\\htdocs\\web_backend\\DoodleJump\\templates\\header.tpl',
      1 => 1466496806,
      2 => 'file',
    ),
  ),
  'includes' => 
  array (
  ),
),false)) {
function content_5768f7278d1f95_33455454 ($_smarty_tpl) {
?>
<!-- off-canvas title bar for 'small' screen -->
<div class="title-bar" data-responsive-toggle="widemenu" data-hide-for="medium">
  <div class="title-bar-left">
    <button class="menu-icon" type="button" data-open="offCanvasLeft"></button>
    <span class="title-bar-title"><a href="index.php" style="display: inline; color: #FFFFFF">DoodleJump</a></span>
  </div>
  <div class="title-bar-right">
    <span class="title-bar-title">Log In</span>
    <!--button class="menu-icon" type="button" data-open="offCanvasRight"></button-->
  </div>
</div>

<!-- off-canvas left menu -->
<div class="off-canvas position-left" id="offCanvasLeft" data-off-canvas>
  <ul class="vertical dropdown menu" data-dropdown-menu>
    <li><a href="records.php">Records</a></li>
    <li><a href="download.php">Download</a></li>
  </ul>
</div>

<!-- "wider" top-bar menu for 'medium' and up -->
<div id="widemenu" class="top-bar">
  <div class="top-bar-left">
    <ul class="dropdown menu" data-dropdown-menu>
      <li class="menu-text has-submenu"><a href="index.php" style="display: inline">DoodleJump</a></li>
      <!--li class="menu-text has-submenu"><a href="index.php"><span class="couch">DoodleJump</span></a></li-->
      <li class="has-submenu">
        <a href="records.php">Records</a>
      </li>
      <li class="has-submenu">
        <a href="download.php">Download</a>
      </li>
    </ul>
  </div>
  <div class="top-bar-right">
    <ul class="menu">
      <!--li><button class="button">Search</button></li-->
      <li>
        <a href="#" data-reveal-id="myModal" class="button">Log In</a>
        <!--div id="myModal" class="reveal-modal remove-whitespace" data-reveal>
          <div class="row">
            <div class="large-6 columns auth_plain">
              <div class="signup_panel left_solid">
                <p class="welcome">Registered Users</p>
                <form>
                  <div class="row collapse">
                    <div class="small-2  columns">
                      <span class="prefix"><i class="fi-torso-female"></i></span>
                    </div>
                    <div class="small-10  columns">
                      <input type="text" placeholder="username">
                    </div>
                  </div>
                  <div class="row collapse">
                    <div class="small-2 columns ">
                      <span class="prefix"><i class="fi-lock"></i></span>
                    </div>
                    <div class="small-10 columns ">
                      <input type="text" placeholder="password">
                    </div>
                  </div>
                </form>
                <a href="#" class="button ">Log In </a>
              </div>
            </div>

            <div class="large-6 columns auth_plain">
              <div class="signup_panel new_users">
                <p class="welcome">New User?</p>
                <p>By creating an account with us, you will be able to move through the checkout process faster, view and track your orders, and more.</p><br>
                <a href="#" class="button ">Sign Up</a></br>
              </div>
            </div>

          </div>
          <a class="close-reveal-modal">&#215;</a>
        </div-->
      </li>
    </ul>
  </div>
</div>
<?php }
}
