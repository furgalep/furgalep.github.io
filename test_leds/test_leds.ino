/*
 * LED Test
 * Tests the green (success) and red (error) LEDs
 */

#define GREEN_LED_PIN 2
#define RED_LED_PIN A3

void setup() {
  Serial.begin(9600);
  Serial.println("LED Test Program");
  Serial.println("================");
  Serial.println();
  
  // Initialize LED pins
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  
  // Turn off both LEDs
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  
  delay(1000);
  
  // Test 1: Green LED steady
  Serial.println("Test 1: Green LED steady (2 seconds)");
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(2000);
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(500);
  
  // Test 2: Red LED steady
  Serial.println("Test 2: Red LED steady (2 seconds)");
  digitalWrite(RED_LED_PIN, HIGH);
  delay(2000);
  digitalWrite(RED_LED_PIN, LOW);
  delay(500);
  
  // Test 3: Green LED flashing
  Serial.println("Test 3: Green LED flashing (success pattern)");
  for (int i = 0; i < 5; i++) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(150);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(150);
  }
  delay(500);
  
  // Test 4: Red LED flashing
  Serial.println("Test 4: Red LED flashing (error pattern)");
  for (int i = 0; i < 5; i++) {
    digitalWrite(RED_LED_PIN, HIGH);
    delay(100);
    digitalWrite(RED_LED_PIN, LOW);
    delay(100);
  }
  delay(500);
  
  // Test 5: Alternating
  Serial.println("Test 5: Alternating LEDs");
  for (int i = 0; i < 6; i++) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    delay(250);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    delay(250);
  }
  digitalWrite(RED_LED_PIN, LOW);
  
  delay(1000);
  
  Serial.println();
  Serial.println("All tests complete!");
  Serial.println("Both LEDs should have lit up and flashed.");
}

void loop() {
  // Continuous test pattern
  Serial.println("Pattern: Green -> Red -> Both");
  
  // Green only
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  delay(500);
  
  // Red only
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(500);
  
  // Both
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(500);
  
  // Off
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  delay(500);
}

