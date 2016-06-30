<?php
/* Smarty version 3.1.29, created on 2016-06-30 23:32:55
  from "E:\!git\!web_backend\server2go\server2go\htdocs\web_backend\DoodleJump\template\about.tpl" */

if ($_smarty_tpl->smarty->ext->_validateCompiled->decodeProperties($_smarty_tpl, array (
  'has_nocache_code' => false,
  'version' => '3.1.29',
  'unifunc' => 'content_57759007d412a6_98735190',
  'file_dependency' => 
  array (
    'c9362c945460170fe358e1f69b4c2482a2ad7142' => 
    array (
      0 => 'E:\\!git\\!web_backend\\server2go\\server2go\\htdocs\\web_backend\\DoodleJump\\template\\about.tpl',
      1 => 1466496323,
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
function content_57759007d412a6_98735190 ($_smarty_tpl) {
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
                <h1>About</h1>
              </div>
            </div>
            <div class="large-9">
              <p>This application was written on C++ with using "<a href="http://sfml-dev.org">SFML</a>" & "<a href="https://github.com/nlohmann/json">JSON for Moder C++</a>"</p>
              <p>The site was created with "<a href="http://foundation.zurb.com/">Foundation Framework</a>" & "<a href="http://www.smarty.net/">Smarty</a>"</p>
              <p>My progress u can c there:</p>
              <ul>
                <li><a href="https://docs.google.com/document/d/1kjto9LA2BcVBjXd9e6DH0zrALFZ8bdjKzAkJJ4RckCQ/edit">Specification I</a></li>
                <li><a href="https://docs.google.com/spreadsheets/d/1fvFr4tqhUAbG9Rj28kTvcEmp7yTPssYyyDevOqoEVwE/edit#gid=0">RoadMap I</a></li>
                <li><a href="https://docs.google.com/document/d/1RMM_ous2-aTqk7FYdlNmu_2mANp_jVlbcpziu0aR158/edit">Specification II</a></li>
                <li><a href="https://docs.google.com/spreadsheets/d/1KDjUXYfd_gr6iIjH8IsOAPN4TTmO8ufnkgn2Pgd_7qY/edit#gid=0">RoadMap I</a></li>
                <li><a href="https://github.com/eligantRU/DoodleJump">GitHub repository</a></li>
              </ul>
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
