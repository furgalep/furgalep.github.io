/*
 * Speaker/Buzzer Test
 * Tests the passive speaker with various tones
 */

#define SPEAKER_PIN 3

void setup() {
  Serial.begin(9600);
  Serial.println("Speaker/Buzzer Test");
  Serial.println("===================");
  Serial.println();
  
  pinMode(SPEAKER_PIN, OUTPUT);
  
  delay(1000);
  
  // Test 1: Simple beep
  Serial.println("Test 1: Simple beep (1000 Hz)");
  tone(SPEAKER_PIN, 1000, 500);
  delay(1000);
  
  // Test 2: Low tone
  Serial.println("Test 2: Low tone (200 Hz)");
  tone(SPEAKER_PIN, 200, 500);
  delay(1000);
  
  // Test 3: High tone
  Serial.println("Test 3: High tone (2000 Hz)");
  tone(SPEAKER_PIN, 2000, 500);
  delay(1000);
  
  // Test 4: Ascending scale (minute beeps simulation)
  Serial.println("Test 4: Ascending scale (different minute beeps)");
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523}; // C major scale
  for (int i = 0; i < 8; i++) {
    Serial.print("Tone ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(frequencies[i]);
    Serial.println(" Hz");
    tone(SPEAKER_PIN, frequencies[i], 300);
    delay(500);
  }
  
  delay(1000);
  
  // Test 5: Error buzz
  Serial.println("Test 5: Error buzz (harsh sound)");
  for (int i = 0; i < 3; i++) {
    tone(SPEAKER_PIN, 100, 200);
    delay(250);
  }
  delay(1000);
  
  // Test 6: Success melody
  Serial.println("Test 6: Success melody");
  tone(SPEAKER_PIN, 523, 200); // C
  delay(250);
  tone(SPEAKER_PIN, 659, 200); // E
  delay(250);
  tone(SPEAKER_PIN, 784, 200); // G
  delay(250);
  tone(SPEAKER_PIN, 1047, 400); // C (high)
  delay(500);
  
  Serial.println();
  Serial.println("All tests complete!");
  Serial.println("Did you hear all the different tones?");
}

void loop() {
  // Continuous test - plays a pattern every 3 seconds
  Serial.println("Playing test pattern...");
  
  // Quick double beep
  tone(SPEAKER_PIN, 800, 100);
  delay(150);
  tone(SPEAKER_PIN, 800, 100);
  delay(2850);
}

