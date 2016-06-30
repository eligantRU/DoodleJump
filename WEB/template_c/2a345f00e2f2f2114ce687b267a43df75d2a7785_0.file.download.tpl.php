<?php
/* Smarty version 3.1.29, created on 2016-06-30 12:10:25
  from "E:\!git\!web_backend\server2go\server2go\htdocs\web_backend\DoodleJump\templates\download.tpl" */

if ($_smarty_tpl->smarty->ext->_validateCompiled->decodeProperties($_smarty_tpl, array (
  'has_nocache_code' => false,
  'version' => '3.1.29',
  'unifunc' => 'content_5774f0116fe544_23678498',
  'file_dependency' => 
  array (
    '2a345f00e2f2f2114ce687b267a43df75d2a7785' => 
    array (
      0 => 'E:\\!git\\!web_backend\\server2go\\server2go\\htdocs\\web_backend\\DoodleJump\\templates\\download.tpl',
      1 => 1467281126,
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
function content_5774f0116fe544_23678498 ($_smarty_tpl) {
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
                <h1>Download</h1>
              </div>
            </div>

            <div class="row">
              <h3>U can get the latest version by clicking on this button:</h3>
              <a href="downloads/DoodleJump.7z" class="large button">Download</a>
              <p>Or u can visit my GitHub repository & learn my sources:</p>
              <a class="success button" href="https://github.com/eligantRU/DoodleJump">GitHub</a>
            </div>
          </div>
        </div>
      </div>

      <?php $_smarty_tpl->smarty->ext->_subtemplate->render($_smarty_tpl, "file:footer.tpl", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, $_smarty_tpl->cache_lifetime, array(), 0, false);
?>


      <!-- close wrapper, no more content after this -->
    </div>
  </body>
</html>
<?php }
}
