<?php
/* Smarty version 3.1.29, created on 2016-06-30 23:35:08
  from "E:\!git\!web_backend\server2go\server2go\htdocs\web_backend\DoodleJump\template\faq.tpl" */

if ($_smarty_tpl->smarty->ext->_validateCompiled->decodeProperties($_smarty_tpl, array (
  'has_nocache_code' => false,
  'version' => '3.1.29',
  'unifunc' => 'content_5775908c13a8e2_12084084',
  'file_dependency' => 
  array (
    '6727107c6eec06018845555f925cde67354042f9' => 
    array (
      0 => 'E:\\!git\\!web_backend\\server2go\\server2go\\htdocs\\web_backend\\DoodleJump\\template\\faq.tpl',
      1 => 1467235433,
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
function content_5775908c13a8e2_12084084 ($_smarty_tpl) {
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
                <h1>FAQ</h1>
              </div>
            </div>
          </div>
        </div>

        <div class="row">
          <div class="primary callout">
            <h5>This page was reserved for doodle-tournament</h5>
            <p>U can <a href="about.php">read more in developer's RoadMap</a></p>
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
