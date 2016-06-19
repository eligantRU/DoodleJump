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
              <div class="large-12 columns">
                <h1>Top-100 records</h1>
              </div>
            </div>
            <div class="large-9">
              <table class="hover">
                <thead>
                  <tr>
                    <th>Nickname</th>
                    <th>Score</th>
                  </tr>
                </thead>
                <tbody>
                  {foreach $records as $record}
                    <tr>
                      <td>{$record.nickname}</td>
                      <td>{$record.score}</td>
                    </tr>
                  {/foreach}
                </tbody>
              </table>
            </div>
          </div>
        </div>

        {include file="footer.tpl"}

        <!-- close wrapper, no more content after this -->
      </div>
    </div>
  </body>
</html>
