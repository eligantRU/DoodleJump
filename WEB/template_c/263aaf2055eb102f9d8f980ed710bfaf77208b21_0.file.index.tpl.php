<?php
/* Smarty version 3.1.29, created on 2016-06-30 23:35:04
  from "E:\!git\!web_backend\server2go\server2go\htdocs\web_backend\DoodleJump\template\index.tpl" */

if ($_smarty_tpl->smarty->ext->_validateCompiled->decodeProperties($_smarty_tpl, array (
  'has_nocache_code' => false,
  'version' => '3.1.29',
  'unifunc' => 'content_577590887a0510_63722481',
  'file_dependency' => 
  array (
    '263aaf2055eb102f9d8f980ed710bfaf77208b21' => 
    array (
      0 => 'E:\\!git\\!web_backend\\server2go\\server2go\\htdocs\\web_backend\\DoodleJump\\template\\index.tpl',
      1 => 1466497755,
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
function content_577590887a0510_63722481 ($_smarty_tpl) {
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
              <div class="orbit large-12  medium-12 small-12 hide-for-large hide-for-medium" role="region" aria-label="Favorite Space Pictures" data-orbit>
                <ul class="orbit-container">
                  <button class="orbit-previous"><span class="show-for-sr">Previous Slide</span>&#9664;&#xFE0E;</button>
                  <button class="orbit-next"><span class="show-for-sr">Next Slide</span>&#9654;&#xFE0E;</button>
                  <li class="is-active orbit-slide">
                    <img class="orbit-image" src="img/01.png" alt="Space">
                    <figcaption class="orbit-caption">The main menu</figcaption>
                  </li>
                  <li class="orbit-slide">
                    <img class="orbit-image" src="img/02.png" alt="Space">
                    <figcaption class="orbit-caption">Get scores</figcaption>
                  </li>
                  <li class="orbit-slide">
                    <img class="orbit-image" src="img/03.png" alt="Space">
                    <figcaption class="orbit-caption">Use bonuses</figcaption>
                  </li>
                  <li class="orbit-slide">
                    <img class="orbit-image" src="img/04.png" alt="Space">
                    <figcaption class="orbit-caption">C records</figcaption>
                  </li>
                </ul>
                <nav class="orbit-bullets">
                  <button class="is-active" data-slide="0"><span class="show-for-sr">First slide details.</span><span class="show-for-sr">Current Slide</span></button>
                  <button data-slide="1"><span class="show-for-sr">Second slide details.</span></button>
                  <button data-slide="2"><span class="show-for-sr">Third slide details.</span></button>
                  <button data-slide="3"><span class="show-for-sr">Fourth slide details.</span></button>
                </nav>
              </div>
            </div>

            <div class="row">
              <div class="large-12 columns">
                <h1>DoodleJump</h1>
              </div>
            </div>

            <div class="row">
              <div class="large-12 columns panel">
                <p>DoodleJump is a popular game in over the world with very simple rule: u must get max points. <br />
                   Bonuses like a hat-helicopter, rocket, trampoline & spring can help u in it.</p>
                <p>But be careful: if u touch the window-bottom u lose.</p>
                <div class="flex-video widescreen">
                  <iframe width="420" height="315" src="https://www.youtube.com/embed/tDyM_bNjtKs" frameborder="0" allowfullscreen></iframe>
                </div>
              </div>
            </div>
            <div class="row">
              <div class="large-10 columns">
                <h4>Minimum system requirements</h4>
                <ul>
                  <li>Windows (XP, Vista, 7, 8, 8.1, 10)</li>
                  <li>32 Mb RAM</li>
                  <li>20 Mb HDD</li>
                  <li>Keyboard</li>
                  <li>Mouse</li>
                </ul>
                <h4>Recommendations:</h4>
                <ul>
                  <li>Network connection</li>
                </ul>
              </div>
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
