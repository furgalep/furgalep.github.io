/*
 * Escape Room Countdown Timer
 * 
 * Features:
 * - Configurable countdown time, secret code, and penalty time
 * - TFT display with countdown and messages
 * - Keypad input for code entry
 * - LED indicators (green=success, red=error)
 * - Audio feedback with different beeps per minute
 * - Reset/config mode: Hold * and # for 5 seconds
 * 
 * Wiring: See wiring_diagram.md
 */

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Keypad.h>

// ==================== PIN DEFINITIONS ====================

// TFT Display pins
#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9

// LED pins
#define GREEN_LED_PIN 2
#define RED_LED_PIN   A3

// Speaker pin
#define SPEAKER_PIN 3

// Keypad pins
const byte ROWS = 4;
const byte COLS = 3;
byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {A0, A1, A2};

// ==================== KEYPAD SETUP ====================

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ==================== TFT SETUP ====================

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// ==================== STATE MACHINE ====================

enum GameState {
  CONFIG_TIME,      // Entering countdown time
  CONFIG_CODE,      // Entering secret code
  CONFIG_PENALTY,   // Entering penalty time
  WAITING,          // Waiting for first keypress to start
  RUNNING,          // Timer running
  SUCCESS,          // Correct code entered
  CHECKING_RESET    // Checking for reset combo
};

GameState currentState = CONFIG_TIME;

// ==================== GAME VARIABLES ====================

unsigned long countdownSeconds = 900;  // Default 15 minutes
String secretCode = "1234";            // Default code
unsigned long penaltySeconds = 300;    // Default 5 minutes penalty
String gameMessage = "SOLVE THE PUZZLE!";
String enteredCode = "";
unsigned long timerStartMillis = 0;
unsigned long lastSecondMillis = 0;
unsigned long lastMinuteSeconds = 999999;
String configBuffer = "";
unsigned long resetHoldStartMillis = 0;
bool resetComboActive = false;

// ==================== SETUP ====================

void setup() {
  Serial.begin(9600);
  Serial.println("Escape Room Timer Starting...");
  
  // Initialize pins
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  
  // Initialize display
  tft.begin();
  tft.setRotation(0);  // Portrait mode
  tft.fillScreen(ILI9341_BLACK);
  
  // Show welcome screen
  showWelcomeScreen();
  delay(2000);
  
  // Start in configuration mode
  currentState = CONFIG_TIME;
  promptForCountdownTime();
}

// ==================== MAIN LOOP ====================

void loop() {
  // Check for reset combo (hold * and # for 5 seconds)
  checkResetCombo();
  
  // Get keypad input
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key: ");
    Serial.println(key);
    handleKeyPress(key);
  }
  
  // Update timer if running
  if (currentState == RUNNING) {
    updateTimer();
  }
  
  delay(10);
}

// ==================== KEY HANDLING ====================

void handleKeyPress(char key) {
  switch (currentState) {
    case CONFIG_TIME:
      handleConfigTime(key);
      break;
      
    case CONFIG_CODE:
      handleConfigCode(key);
      break;
      
    case CONFIG_PENALTY:
      handleConfigPenalty(key);
      break;
      
    case WAITING:
      // Any key starts the timer
      startTimer();
      break;
      
    case RUNNING:
      handleCodeEntry(key);
      break;
      
    case SUCCESS:
      // Ignore keys after success
      break;
  }
}

// ==================== CONFIGURATION MODE ====================

void handleConfigTime(char key) {
  if (key == '#') {
    if (configBuffer.length() > 0) {
      countdownSeconds = configBuffer.toInt() * 60;  // Convert minutes to seconds
      Serial.print("Countdown set to: ");
      Serial.print(countdownSeconds);
      Serial.println(" seconds");
      
      configBuffer = "";
      currentState = CONFIG_CODE;
      promptForSecretCode();
    }
  } else if (key >= '0' && key <= '9') {
    configBuffer += key;
    updateConfigDisplay("Time: " + configBuffer + " min");
    beep(800, 50);
  }
}

void handleConfigCode(char key) {
  if (key == '#') {
    if (configBuffer.length() >= 1) {
      secretCode = configBuffer;
      Serial.print("Secret code set to: ");
      Serial.println(secretCode);
      
      configBuffer = "";
      currentState = CONFIG_PENALTY;
      promptForPenaltyTime();
    }
  } else if (key >= '0' && key <= '9') {
    configBuffer += key;
    String masked = "";
    for (int i = 0; i < configBuffer.length(); i++) {
      masked += "*";
    }
    updateConfigDisplay("Code: " + masked);
    beep(800, 50);
  }
}

void handleConfigPenalty(char key) {
  if (key == '#') {
    if (configBuffer.length() > 0) {
      penaltySeconds = configBuffer.toInt() * 60;  // Convert minutes to seconds
      Serial.print("Penalty time set to: ");
      Serial.print(penaltySeconds);
      Serial.println(" seconds");
      
      configBuffer = "";
      currentState = WAITING;
      showWaitingScreen();
    }
  } else if (key >= '0' && key <= '9') {
    configBuffer += key;
    updateConfigDisplay("Penalty: " + configBuffer + " min");
    beep(800, 50);
  }
}

// ==================== CODE ENTRY DURING GAME ====================

void handleCodeEntry(char key) {
  if (key == '#') {
    // Check if code is correct
    if (enteredCode == secretCode) {
      handleCorrectCode();
    } else {
      handleWrongCode();
    }
    enteredCode = "";
  } else if (key == '*') {
    // Clear entered code
    enteredCode = "";
    updateTimerDisplay();
  } else if (key >= '0' && key <= '9') {
    enteredCode += key;
    beep(800, 50);
    updateTimerDisplay();
  }
}

// ==================== TIMER FUNCTIONS ====================

void startTimer() {
  Serial.println("Timer started!");
  currentState = RUNNING;
  timerStartMillis = millis();
  lastSecondMillis = millis();
  lastMinuteSeconds = 999999;
  enteredCode = "";
  updateTimerDisplay();
  beep(1000, 200);  // Start beep
}

void updateTimer() {
  unsigned long currentMillis = millis();
  
  // Update every second
  if (currentMillis - lastSecondMillis >= 1000) {
    lastSecondMillis = currentMillis;
    
    unsigned long elapsedSeconds = (currentMillis - timerStartMillis) / 1000;
    
    if (elapsedSeconds >= countdownSeconds) {
      // Timer expired!
      handleTimerExpired();
    } else {
      unsigned long remainingSeconds = countdownSeconds - elapsedSeconds;
      
      // Check if a minute just passed
      unsigned long remainingMinutes = remainingSeconds / 60;
      if (remainingMinutes < lastMinuteSeconds) {
        lastMinuteSeconds = remainingMinutes;
        playMinuteBeep(remainingMinutes);
      }
      
      updateTimerDisplay();
    }
  }
}

void handleTimerExpired() {
  Serial.println("Timer expired! Adding penalty time...");
  
  // Show "Transmission Error" message
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.setCursor(20, 100);
  tft.println("TRANSMISSION");
  tft.setCursor(60, 130);
  tft.println("ERROR!");
  
  // Flash screen and buzz
  for (int i = 0; i < 3; i++) {
    digitalWrite(RED_LED_PIN, HIGH);
    tone(SPEAKER_PIN, 150, 300);
    delay(400);
    digitalWrite(RED_LED_PIN, LOW);
    delay(100);
  }
  
  delay(1000);
  
  // Add penalty time and restart
  countdownSeconds += penaltySeconds;
  timerStartMillis = millis();
  lastMinuteSeconds = 999999;
  
  Serial.print("Added ");
  Serial.print(penaltySeconds);
  Serial.println(" seconds penalty");
  
  updateTimerDisplay();
}

// ==================== SUCCESS/ERROR HANDLERS ====================

void handleCorrectCode() {
  Serial.println("CORRECT CODE!");
  currentState = SUCCESS;
  
  // Flash green LED
  for (int i = 0; i < 6; i++) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    tone(SPEAKER_PIN, 523, 100);
    delay(150);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(100);
  }
  
  // Success melody
  tone(SPEAKER_PIN, 523, 200);
  delay(250);
  tone(SPEAKER_PIN, 659, 200);
  delay(250);
  tone(SPEAKER_PIN, 784, 200);
  delay(250);
  tone(SPEAKER_PIN, 1047, 400);
  
  // Show success screen
  showSuccessScreen();
  
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void handleWrongCode() {
  Serial.println("WRONG CODE!");
  
  // Flash red LED and screen
  for (int i = 0; i < 4; i++) {
    digitalWrite(RED_LED_PIN, HIGH);
    tft.fillScreen(ILI9341_RED);
    tone(SPEAKER_PIN, 100, 150);
    delay(200);
    digitalWrite(RED_LED_PIN, LOW);
    tft.fillScreen(ILI9341_BLACK);
    delay(100);
  }
  
  // Show error message
  showErrorMessage();
  delay(1500);
  
  // Resume timer
  updateTimerDisplay();
}

// ==================== RESET COMBO ====================

void checkResetCombo() {
  bool starPressed = (keypad.findInList('*') != -1);
  bool hashPressed = (keypad.findInList('#') != -1);
  
  if (starPressed && hashPressed) {
    if (!resetComboActive) {
      resetComboActive = true;
      resetHoldStartMillis = millis();
      Serial.println("Reset combo detected, hold for 5 seconds...");
    } else {
      unsigned long holdTime = millis() - resetHoldStartMillis;
      if (holdTime >= 5000 && currentState != CHECKING_RESET) {
        Serial.println("RESET TRIGGERED!");
        triggerReset();
      }
    }
  } else {
    resetComboActive = false;
  }
}

void triggerReset() {
  // Reset to configuration mode
  currentState = CONFIG_TIME;
  configBuffer = "";
  enteredCode = "";
  
  // Visual/audio feedback
  tft.fillScreen(ILI9341_BLUE);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.setCursor(40, 140);
  tft.println("RESET!");
  
  tone(SPEAKER_PIN, 1000, 500);
  delay(1000);
  
  promptForCountdownTime();
}

// ==================== DISPLAY FUNCTIONS ====================

void showWelcomeScreen() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(3);
  tft.setCursor(20, 80);
  tft.println("ESCAPE");
  tft.setCursor(30, 120);
  tft.println("ROOM");
  tft.setCursor(25, 160);
  tft.println("TIMER");
  
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(60, 220);
  tft.println("Initializing...");
}

void promptForCountdownTime() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(10, 40);
  tft.println("CONFIGURATION");
  
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 80);
  tft.println("Enter countdown time");
  tft.setCursor(10, 100);
  tft.println("in MINUTES");
  tft.setCursor(10, 120);
  tft.println("then press #");
  
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(10, 160);
  tft.println("Time: ");
}

void promptForSecretCode() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(10, 40);
  tft.println("CONFIGURATION");
  
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 80);
  tft.println("Enter SECRET CODE");
  tft.setCursor(10, 100);
  tft.println("then press #");
  
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(10, 160);
  tft.println("Code: ");
}

void promptForPenaltyTime() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(10, 40);
  tft.println("CONFIGURATION");
  
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 80);
  tft.println("Enter PENALTY TIME");
  tft.setCursor(10, 100);
  tft.println("(added when timer");
  tft.setCursor(10, 115);
  tft.println("expires) in MINUTES");
  tft.setCursor(10, 135);
  tft.println("then press #");
  
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(10, 180);
  tft.println("Pen: ");
}

void updateConfigDisplay(String text) {
  // Clear previous input area
  tft.fillRect(0, 150, 240, 100, ILI9341_BLACK);
  
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(10, 160);
  tft.println(text);
}

void showWaitingScreen() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(2);
  tft.setCursor(30, 80);
  tft.println("READY!");
  
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 130);
  tft.println("Press any key");
  tft.setCursor(10, 145);
  tft.println("to start countdown");
  
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setCursor(10, 180);
  
  unsigned long mins = countdownSeconds / 60;
  unsigned long secs = countdownSeconds % 60;
  
  tft.print("Time: ");
  if (mins < 10) tft.print("0");
  tft.print(mins);
  tft.print(":");
  if (secs < 10) tft.print("0");
  tft.println(secs);
}

void updateTimerDisplay() {
  unsigned long elapsedSeconds = (millis() - timerStartMillis) / 1000;
  unsigned long remainingSeconds = countdownSeconds - elapsedSeconds;
  
  if (elapsedSeconds >= countdownSeconds) {
    remainingSeconds = 0;
  }
  
  unsigned long mins = remainingSeconds / 60;
  unsigned long secs = remainingSeconds % 60;
  
  // Clear and redraw
  tft.fillScreen(ILI9341_BLACK);
  
  // Message at top
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.println(gameMessage);
  
  // Big countdown in middle
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(5);
  tft.setCursor(30, 100);
  
  if (mins < 10) tft.print("0");
  tft.print(mins);
  tft.print(":");
  if (secs < 10) tft.print("0");
  tft.print(secs);
  
  // Show entered code
  if (enteredCode.length() > 0) {
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_YELLOW);
    tft.setCursor(10, 200);
    tft.print("Code: ");
    
    for (int i = 0; i < enteredCode.length(); i++) {
      tft.print("*");
    }
    
    tft.setCursor(10, 230);
    tft.setTextSize(1);
    tft.println("Press # to submit");
    tft.println("Press * to clear");
  } else {
    tft.setTextSize(1);
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(30, 220);
    tft.println("Enter code to escape!");
  }
}

void showSuccessScreen() {
  tft.fillScreen(ILI9341_BLACK);
  
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(4);
  tft.setCursor(20, 80);
  tft.println("SUCCESS!");
  
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(10, 150);
  tft.println("You escaped!");
  
  tft.setTextSize(1);
  tft.setCursor(20, 200);
  tft.println("Hold * and # for 5 sec");
  tft.setCursor(20, 215);
  tft.println("to reset");
}

void showErrorMessage() {
  tft.fillScreen(ILI9341_BLACK);
  
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.setCursor(30, 100);
  tft.println("WRONG");
  tft.setCursor(30, 140);
  tft.println("CODE!");
  
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setCursor(30, 200);
  tft.println("Try again!");
}

// ==================== AUDIO FUNCTIONS ====================

void beep(int frequency, int duration) {
  tone(SPEAKER_PIN, frequency, duration);
}

void playMinuteBeep(unsigned long remainingMinutes) {
  // Different tone for each minute (C major scale)
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784};
  int index = remainingMinutes % 12;
  
  Serial.print("Minute beep: ");
  Serial.print(remainingMinutes);
  Serial.println(" minutes remaining");
  
  tone(SPEAKER_PIN, frequencies[index], 300);
}

