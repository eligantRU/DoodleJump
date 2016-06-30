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

        {include file="footer.tpl"}

        <!-- close wrapper, no more content after this -->
      </div>
    </div>
  </body>
</html>
