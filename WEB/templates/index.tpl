<!DOCTYPE html>
<html class="no-js" lang="en" dir="ltr">
  {include file="head.tpl"}
  <body>
    <div class="off-canvas-wrapper">
      <div class="off-canvas-wrapper-inner" data-off-canvas-wrapper>

        {include file="header.tpl"}

        <!-- original content goes in this container -->
        <div class="off-canvas-content" data-off-canvas-content>
          <div class="row column">
            <div class="row">
              <div class="orbit large-12 medium-12 small-12" role="region" aria-label="Favorite Space Pictures" data-orbit>
                <ul class="orbit-container">
                  <button class="orbit-previous"><span class="show-for-sr">Previous Slide</span>&#9664;&#xFE0E;</button>
                  <button class="orbit-next"><span class="show-for-sr">Next Slide</span>&#9654;&#xFE0E;</button>
                  <li class="is-active orbit-slide">
                    <img class="orbit-image" src="img/01.jpg" alt="Space">
                    <figcaption class="orbit-caption">Text 1</figcaption>
                  </li>
                  <li class="orbit-slide">
                    <img class="orbit-image" src="img/02.jpg" alt="Space">
                    <figcaption class="orbit-caption">Text 2</figcaption>
                  </li>
                  <li class="orbit-slide">
                    <img class="orbit-image" src="img/03.jpg" alt="Space">
                    <figcaption class="orbit-caption">Text 3</figcaption>
                  </li>
                  <li class="orbit-slide">
                    <img class="orbit-image" src="img/04.jpg" alt="Space">
                    <figcaption class="orbit-caption">Text 4</figcaption>
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
                <p>DoodleJump is a popular game in over the world with very simple rule: u must get max points.</p>
                <p>Bonuses like a hat-helicopter, rocket, trampoline & spring can help u in it.</p>
                <p>But be careful: if u touch the window-bottom u lose.</p>
              </div>
            </div>
          </div>
        </div>

        {include file="footer.tpl"}

        <!-- close wrapper, no more content after this -->
      </div>
    </div>
  </body>
</html>
