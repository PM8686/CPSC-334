#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin definitions
int x_pin = 35;
int y_pin = 34;
int sw_pin = 2;
int button_pin = 4;
int switch_pin = 0;

// Screen setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI   23
#define OLED_CLK    18
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Game variables
int ball_x, ball_y, ball_dx, ball_dy;
int paddle_x = SCREEN_WIDTH / 2 - 10;
int paddle_width = 20;
int paddle_color = 1;  // 1 = Red, 0 = Blue
int hit_counter = 0;
bool gravity_on = false;
bool game_paused = false;
int selected_option = 0;  // For pause menu

void setup() {
  // Initialize serial communication at 115200 bits per second
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(sw_pin, INPUT_PULLUP);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(switch_pin, INPUT_PULLUP);

  // Set analog resolution
  analogReadResolution(12);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  display.clearDisplay();
  display.display();

  // Initialize game variables
  ball_x = SCREEN_WIDTH / 2;
  ball_y = SCREEN_HEIGHT / 2;
  ball_dx = 2;  // Initial horizontal velocity
  ball_dy = 1;  // Initial vertical velocity
}

void loop() {
  // Read input values
  int analogValue_x = analogRead(x_pin);
  int sw = digitalRead(sw_pin);
  int button = digitalRead(button_pin);
  int sw1tch = digitalRead(switch_pin);
  
  // Control gravity based on the switch
  gravity_on = (sw1tch == LOW);

  // Check if the game is paused
  if (sw == LOW) {
    if (!game_paused) {
      game_paused = true;
      displayPauseMenu();
    } else {
      handlePauseMenu(analogValue_x, button);
    }
    return;
  } else {
    game_paused = false;
  }

  // Handle paddle movement with joystick
  paddle_x = map(analogValue_x, 0, 4095, 0, SCREEN_WIDTH - paddle_width);

  // Handle paddle color change with button
  if (button == LOW) {
    paddle_color = !paddle_color;
  }

  // Update ball position and handle collisions
  updateBall();

  // Check for collisions between ball and paddle
  if (ball_y >= SCREEN_HEIGHT - 10 && ball_x >= paddle_x && ball_x <= paddle_x + paddle_width) {
    if ((paddle_color == 1 && ball_dx > 0) || (paddle_color == 0 && ball_dx < 0)) {
      ball_dy = -ball_dy;  // Bounce the ball
      hit_counter++;       // Increment hit counter
    }
  }

  // Display game screen
  displayGameScreen();
  delay(100);  // Delay for smoother gameplay
}

void updateBall() {
  ball_x += ball_dx;
  ball_y += ball_dy;

  // Check for wall collisions
  if (ball_x <= 0 || ball_x >= SCREEN_WIDTH) {
    ball_dx = -ball_dx;  // Reverse horizontal direction
  }

  if (ball_y <= 0) {
    ball_dy = -ball_dy;  // Reverse vertical direction
  }

  // Apply gravity if enabled
  if (gravity_on) {
    ball_dy += 1;  // Apply downward acceleration
  }
}

void displayGameScreen() {
  display.clearDisplay();

  // Draw ball
  display.fillCircle(ball_x, ball_y, 2, SSD1306_WHITE);

  // Draw paddle
  display.fillRect(paddle_x, SCREEN_HEIGHT - 5, paddle_width, 3, (paddle_color == 1) ? SSD1306_WHITE : SSD1306_BLACK);

  // Draw hit counter
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Hits: ");
  display.print(hit_counter);

  display.display();
}

void displayPauseMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("PAUSED");
  
  display.setCursor(10, 30);
  display.println("1. Continue");
  
  display.setCursor(10, 40);
  display.println("2. Start Over");
  
  display.setCursor(10, 50);
  display.println("3. Turn Off");
  
  display.display();
}

void handlePauseMenu(int analogValue_x, int button) {
  if (button == LOW) {
    if (selected_option == 0) {
      game_paused = false;  // Continue
    } else if (selected_option == 1) {
      resetGame();  // Start over
    } else if (selected_option == 2) {
      turnOffGame();  // Turn off
    }
  }

  selected_option = map(analogValue_x, 0, 4095, 0, 2);
}

void resetGame() {
  ball_x = SCREEN_WIDTH / 2;
  ball_y = SCREEN_HEIGHT / 2;
  ball_dx = 2;
  ball_dy = 1;
  hit_counter = 0;
}

void turnOffGame() {
  display.clearDisplay();
  display.display();
  for(;;);  // Infinite loop to halt the game
}
