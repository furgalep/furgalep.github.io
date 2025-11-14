/*
 * Keypad Test
 * Tests the 3x4 matrix keypad
 * Open Serial Monitor at 9600 baud to see key presses
 */

#include <Keypad.h>

// Keypad layout
const byte ROWS = 4;
const byte COLS = 3;

// Define the keypad layout
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Connect keypad ROW pins to these Arduino pins
byte rowPins[ROWS] = {7, 6, 5, 4};

// Connect keypad COL pins to these Arduino pins  
byte colPins[COLS] = {A0, A1, A2};

// Create keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("     Keypad Test Program");
  Serial.println("=================================");
  Serial.println();
  Serial.println("Press keys on the keypad...");
  Serial.println("Each key press will be displayed below.");
  Serial.println();
  Serial.println("Test holding * and # together for 3 seconds");
  Serial.println("(this is the reset combo for the main program)");
  Serial.println();
}

unsigned long starHeldTime = 0;
unsigned long hashHeldTime = 0;
bool starHeld = false;
bool hashHeld = false;
bool comboDetected = false;

void loop() {
  // Check for key presses
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    
    // Test multi-key detection for reset combo
    if (key == '*') {
      starHeld = true;
      starHeldTime = millis();
    } else if (key == '#') {
      hashHeld = true;
      hashHeldTime = millis();
    }
  }
  
  // Check if both keys are being held
  KeyState starState = keypad.getState();
  bool starStillHeld = (keypad.findInList('*') != -1);
  bool hashStillHeld = (keypad.findInList('#') != -1);
  
  if (starStillHeld && hashStillHeld && !comboDetected) {
    unsigned long holdTime = min(millis() - starHeldTime, millis() - hashHeldTime);
    if (holdTime > 3000) {
      Serial.println();
      Serial.println("*** COMBO DETECTED! ***");
      Serial.println("* and # held for 3+ seconds");
      Serial.println("This would trigger RESET mode");
      Serial.println();
      comboDetected = true;
    }
  }
  
  // Reset combo detection when keys released
  if (!starStillHeld) {
    starHeld = false;
    comboDetected = false;
  }
  if (!hashStillHeld) {
    hashHeld = false;
    comboDetected = false;
  }
  
  delay(10);
}

