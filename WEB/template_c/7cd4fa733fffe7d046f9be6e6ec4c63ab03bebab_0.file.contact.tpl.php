<?php
/* Smarty version 3.1.29, created on 2016-06-30 12:17:28
  from "E:\!git\!web_backend\server2go\server2go\htdocs\web_backend\DoodleJump\templates\contact.tpl" */

if ($_smarty_tpl->smarty->ext->_validateCompiled->decodeProperties($_smarty_tpl, array (
  'has_nocache_code' => false,
  'version' => '3.1.29',
  'unifunc' => 'content_5774f1b86e0247_14152465',
  'file_dependency' => 
  array (
    '7cd4fa733fffe7d046f9be6e6ec4c63ab03bebab' => 
    array (
      0 => 'E:\\!git\\!web_backend\\server2go\\server2go\\htdocs\\web_backend\\DoodleJump\\templates\\contact.tpl',
      1 => 1467281845,
      2 => 'file',
    ),
  ),
  'includes' => 
  array (
    'file:head.tpl' => 1,
    'file:header.tpl' => 1,
    'file:footer.tpl' => 1,
  ),
),false)) {
function content_5774f1b86e0247_14152465 ($_smarty_tpl) {
?>
<!DOCTYPE html>
<html class="no-js" lang="en" dir="ltr">

  <?php $_smarty_tpl->smarty->ext->_subtemplate->render($_smarty_tpl, "file:head.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>


  <body>
    <div class="off-canvas-wrapper">
      <div class="off-canvas-wrapper-inner" data-off-canvas-wrapper>

        <?php $_smarty_tpl->smarty->ext->_subtemplate->render($_smarty_tpl, "file:header.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>


        <!-- original content goes in this container -->
        <div class="off-canvas-content" data-off-canvas-content>
          <div class="row column">
            <div class="row">
              <div class="large-12 columns">
                <h1>Contact</h1>
              </div>
            </div>
          </div>
        </div>

        <div class="row">
          <div class="row">
            <div id="contactForm" class="small-12 medium-9 large-8 columns">
              <form id="myForm" method="post" data-abide>
                <h5>Contact Us</h5>
                <label>Name</label>
                <small class="error">Your full name is required.</small>
                <input type="text" placeholder="Full Name" required>
                <label>Email</label>
                <small class="error">An email address is required.</small>
                <input type="email" placeholder="username@address.com" required>
                <label>Your Message</label>
                <small class="error">Your message is required.</small>
                <textarea placeholder="Enter your message here" required></textarea>
                <input type="submit" class="nice blue radius button" value="Send Message"></button></a>
              </form>
            </div>
          </div>
        </div>

        <?php $_smarty_tpl->smarty->ext->_subtemplate->render($_smarty_tpl, "file:footer.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>


        <!-- close wrapper, no more content after this -->
      </div>
    </div>
  </body>
</html>
<?php }
}
