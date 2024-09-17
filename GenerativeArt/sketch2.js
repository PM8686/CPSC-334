// Global variables for circle and ball properties
let circ_size = 0;
let circ_start = 0;
let circ_end = 0;
let inc_rate = 0;
let inc_time_conv = 0;
let window_margins = 5;
let max_size = 0;
let min_size = 0;
let bouncing_balls = [];
let num_balls = 0;
let gravity = 0.02;
let dampening = 0.98;

// Variables for delay between ball drops
let is_growing = true;
let delay_start = 0;
let delay_duration = 1000;

// Colors array and properties for balls
let colors = [];
let growing_ball_color;
let prev_ball_color;
let transparency;

function setup() {
  // Set up canvas and initialize variables
  createCanvas(windowWidth - window_margins, windowHeight - window_margins);
  initialize_vars();
}

function draw() {
  // Clear the background and manage different states
  background(255);

  if (is_growing) {
    grow(); // growing circle state
  } else if (millis() - delay_start >= delay_duration) {
    start_growing(); // Transition to the growing state
  } else {
    delay(); // delay between ball drops
  }

  bounce_balls(); // Update and draw bouncing balls
}

function initialize_vars() {
  // Initialize size and timing for the growing circle
  circ_start = millis();
  max_size = min(windowWidth, windowHeight) / 3;
  min_size = min(windowWidth, windowHeight) / 10
  inc_rate = 1 * (max_size / 270);
  inc_time_conv = 50 * (0.2 / inc_rate);
  circ_end = random(min_size * inc_time_conv, max_size * inc_time_conv);

  // Define pallette
  let red_ball = color(255, 0, 0);
  let yellow_ball = color(255, 255, 0);
  let green_ball = color(0, 255, 0);
  let blue_ball = color(0, 0, 255);
  colors = [red_ball, green_ball, blue_ball, yellow_ball];

  // Set initial colors and boundary radius
  growing_ball_color = random(colors);
  prev_ball_color = growing_ball_color;
}

function grow() {
  // Update transparency and draw the growing circle
  transparency = 255 * ((millis() - circ_start) / 10000);
  stroke(0);
  fill(
    growing_ball_color.levels[0],
    growing_ball_color.levels[1],
    growing_ball_color.levels[2],
    transparency
  );
  rect(
    width / 2 - windowWidth / 2,
    height / 2 - windowHeight / 2,
    windowWidth,
    windowHeight
  );

  // Increase circle size until it reaches the end time
  if (millis() - circ_start < circ_end) {
    circ_size += inc_rate;
  } else {
    add_bouncing_ball(); // Add a new bouncing ball
    reset_grow_vars(); // Reset variables for the next cycle
  }
  fill(255);
  circle(width / 2, height * 0.15, circ_size); // Draw the growing circle
}

function add_bouncing_ball() {
  // Add a new bouncing ball with random speed and properties
  bouncing_balls.push({
    x: width / 2,
    y: height * 0.15,
    size: circ_size,
    x_speed: random(0.5, 2) * random([-1, 1]),
    y_speed: 0,
    start: millis(),
    duration: (circ_size / max_size) * 75000,
    transparency: 255,
    bcolor: growing_ball_color,
  });
  num_balls++;
}

function reset_grow_vars() {
  // Reset variables after the growing state ends
  circ_size = 0;
  circ_start = millis();
  circ_end = random(min_size * inc_time_conv, max_size * inc_time_conv);
  is_growing = false;
  delay_start = millis();
  prev_ball_color = growing_ball_color;
  growing_ball_color = random(colors);
}

function start_growing() {
  // Transition to the growing state
  is_growing = true;
  circ_start = millis();
  circ_end = random(min_size * inc_time_conv, max_size * inc_time_conv);
}

function delay() {
  // delay between ball drops with fading effect
  fill(
    prev_ball_color.levels[0],
    prev_ball_color.levels[1],
    prev_ball_color.levels[2],
    transparency * (1 - (millis() - delay_start) / (delay_duration / 4))
  );
  rect(
    width / 2 - windowWidth / 2,
    height / 2 - windowHeight / 2,
    windowWidth,
    windowHeight
  );
}

function bounce_balls() {
  // Update and draw bouncing balls
  for (let i = bouncing_balls.length - 1; i >= 0; i--) {
    let ball = bouncing_balls[i];

    if (millis() - ball.start > ball.duration) {
      // Remove balls that have exceeded their duration
      bouncing_balls.splice(i, 1);
      continue;
    }

    // Update ball transparency and draw it
    ball.transparency = 255 * (1 - (millis() - ball.start) / ball.duration);
    stroke(0, 0, 0, ball.transparency);
    fill(
      ball.bcolor.levels[0],
      ball.bcolor.levels[1],
      ball.bcolor.levels[2],
      ball.transparency
    );
    circle(ball.x, ball.y, ball.size);

    // Update ball position and velocity
    ball.x += ball.x_speed;
    ball.y_speed += gravity;
    ball.y += ball.y_speed;

    wall_collision(ball);
    ball_collision(i);
  }
}

function wall_collision(ball) {
  // collisions with the walls of the canvas
  if (ball.x > width - ball.size / 2) {
    ball.x_speed *= -1;
    ball.x = width - ball.size / 2;
  } else if (ball.x < ball.size / 2) {
    ball.x_speed *= -dampening;
    ball.x = ball.size / 2;
  }

  if (ball.y > height - ball.size / 2) {
    ball.y_speed *= -dampening * 0.92; // Slightly reduced dampening for vertical collisions
    ball.y = height - ball.size / 2;
  }
}

function ball_collision(current_index) {
  // collisions between balls
  for (let j = current_index + 1; j < bouncing_balls.length; j++) {
    let ball = bouncing_balls[current_index];
    let other_ball = bouncing_balls[j];

    let dist_between_balls = dist(ball.x, ball.y, other_ball.x, other_ball.y);
    let min_dist = ball.size / 2 + other_ball.size / 2;

    if (dist_between_balls < min_dist) {
      // Swap speeds and adjust positions for ball collision
      let temp_x_speed = ball.x_speed;
      let temp_y_speed = ball.y_speed;

      ball.x_speed = other_ball.x_speed * dampening;
      ball.y_speed = other_ball.y_speed * dampening;

      other_ball.x_speed = temp_x_speed * dampening;
      other_ball.y_speed = temp_y_speed * dampening;

      let angle = atan2(other_ball.y - ball.y, other_ball.x - ball.x);
      let overlap = min_dist - dist_between_balls;

      ball.x -= (cos(angle) * overlap) / 2;
      ball.y -= (sin(angle) * overlap) / 2;
      other_ball.x += (cos(angle) * overlap) / 2;
      other_ball.y += (sin(angle) * overlap) / 2;
    }
  }
}

function windowResized() {
  // Update canvas size and boundary radius on window resize
  resizeCanvas(windowWidth - window_margins, windowHeight - window_margins);
  circ_start = millis();
  max_size = min(windowWidth, windowHeight) / 3;
  min_size = min(windowWidth, windowHeight) / 10;
  inc_rate = 1 * (max_size / 270);
  inc_time_conv = 50 * (0.2 / inc_rate);
  circ_end = random(min_size * inc_time_conv, max_size * inc_time_conv);
  bouncing_balls = [];
  circ_size = 0;
  is_growing = false;
  delay_start = millis();
}
