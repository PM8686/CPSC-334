let balls = [];
let max_size = 0;
let min_size = 0;
let num_balls = 0;

// Variables for delay between ball drops
let delay_start = 0;
let delay_duration = 1000;

// Colors array and properties for balls
let colors = [];

function setup() {
  createCanvas(windowWidth, windowHeight);
  // Reduce pixel density to lower resolution (default is usually 2 for high-DPI screens)
  if (min(windowWidth, windowHeight) < 1000) pixelDensity(1); // 1 means 1:1 pixel ratio, lower resolution
  else pixelDensity(0.75);
  initialize_vars();
}

function draw() {
  // Clear the background to ensure proper drawing
  background(255);

  if (millis() - delay_start >= delay_duration) {
    add_ball(); // Add a ball
    delay_start = millis(); // Reset the delay timer
  }

  display_balls();
}

function initialize_vars() {
  // Initialize size limits for the balls
  max_size = min(windowWidth, windowHeight) / 3;
  min_size = min(windowWidth, windowHeight) / 10;
  delay_start = millis();

  // Define color palette
  let red_ball = color(255, 0, 0);
  let yellow_ball = color(255, 255, 0);
  let green_ball = color(0, 255, 0);
  let blue_ball = color(0, 0, 255);
  colors = [red_ball, green_ball, blue_ball, yellow_ball];
}

function add_ball() {
  // Add a new ball with random size and properties
  let tmp_sz = random(min_size, max_size);
  balls.push({
    x: random(tmp_sz / 2, width - tmp_sz / 2),
    y: random(tmp_sz / 2, height - tmp_sz / 2),
    size: tmp_sz,
    start: millis(),
    duration: (tmp_sz / max_size) * 60000,
    transparency: 0, // Start with transparency at 0 for the fade-in
    bcolor: random(colors),
    fade_in_duration: 200 // Duration of the fade-in effect (in milliseconds)
  });
  num_balls++;
}

function display_balls() {
  // Update and draw the balls
  for (let i = balls.length - 1; i >= 0; i--) {
    let ball = balls[i];
    let elapsed_time = millis() - ball.start;

    if (elapsed_time > ball.duration) {
      // Remove balls that have exceeded their duration
      // print(balls.length);
      balls.splice(i, 1);
      
      // make the balls all disappear after some time
      if (balls.length >= 35) delay_duration = Infinity;
      else if (balls.length <= 0) 
      {
        // a small delay
        let small_delay = 3000;
        let start = millis();
        while(millis() - start < small_delay);
        delay_duration = 1000;
      }
      continue;
    }

    // Handle fade-in transition
    if (elapsed_time < ball.fade_in_duration) {
      ball.transparency = map(elapsed_time, 0, ball.fade_in_duration, 0, 255);
    } else {
      // Handle fade-out after the fade-in is complete
      ball.transparency = 255 * (1 - (elapsed_time - ball.fade_in_duration) / (ball.duration - ball.fade_in_duration));
    }

    // Draw the ball with updated transparency
    stroke(0, 0, 0, ball.transparency);
    fill(
      ball.bcolor.levels[0],
      ball.bcolor.levels[1],
      ball.bcolor.levels[2],
      ball.transparency
    );
    circle(ball.x, ball.y, ball.size);
  }
}

function windowResized() {
  // Update canvas size and reset boundaries on window resize
  resizeCanvas(windowWidth, windowHeight);
  max_size = min(windowWidth, windowHeight) / 3;
  min_size = min(windowWidth, windowHeight) / 10;
  // Reduce pixel density to lower resolution (default is usually 2 for high-DPI screens)
  if (min(windowWidth, windowHeight) < 1000) pixelDensity(1); // 1 means 1:1 pixel ratio, lower resolution
  else pixelDensity(0.75);
  balls = [];
  delay_start = millis();
}
