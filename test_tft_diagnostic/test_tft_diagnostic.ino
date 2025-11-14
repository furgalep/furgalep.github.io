/*
 * TFT Display Diagnostic
 * This will help identify if it's a wiring or driver issue
 */

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

// TFT Pin definitions for Arduino Uno
#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9

// Create TFT object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("TFT Display Diagnostic");
  Serial.println("=================================");
  Serial.println();
  
  // Check pin states before initialization
  Serial.println("Pin Configuration:");
  Serial.print("TFT_CS (Pin 10): ");
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  Serial.println("OUTPUT");
  
  Serial.print("TFT_DC (Pin 8): ");
  pinMode(TFT_DC, OUTPUT);
  Serial.println("OUTPUT");
  
  Serial.print("TFT_RST (Pin 9): ");
  pinMode(TFT_RST, OUTPUT);
  Serial.println("OUTPUT");
  
  Serial.println();
  Serial.println("Attempting to initialize display...");
  
  // Try to initialize
  tft.begin();
  
  Serial.println("Display initialized (no errors)");
  Serial.print("Display width: ");
  Serial.println(tft.width());
  Serial.print("Display height: ");
  Serial.println(tft.height());
  Serial.println();
  
  Serial.println("Testing display output...");
  Serial.println("Watch your screen for color changes:");
  Serial.println();
  
  // Test 1: Simple color fills
  Serial.println("1. Filling RED...");
  tft.fillScreen(ILI9341_RED);
  delay(2000);
  
  Serial.println("2. Filling GREEN...");
  tft.fillScreen(ILI9341_GREEN);
  delay(2000);
  
  Serial.println("3. Filling BLUE...");
  tft.fillScreen(ILI9341_BLUE);
  delay(2000);
  
  Serial.println("4. Filling WHITE...");
  tft.fillScreen(ILI9341_WHITE);
  delay(2000);
  
  Serial.println("5. Filling BLACK...");
  tft.fillScreen(ILI9341_BLACK);
  delay(2000);
  
  Serial.println();
  Serial.println("=================================");
  Serial.println("DIAGNOSTIC RESULTS:");
  Serial.println("=================================");
  Serial.println();
  Serial.println("If you saw NO color changes:");
  Serial.println("  - Check MOSI (Pin 11) connection");
  Serial.println("  - Check SCK (Pin 13) connection");
  Serial.println("  - Try connecting MISO (Pin 12)");
  Serial.println("  - Display might not be ILI9341");
  Serial.println();
  Serial.println("If screen stayed one color:");
  Serial.println("  - Display might be ILI9341 but");
  Serial.println("    needs different initialization");
  Serial.println();
  Serial.println("Next steps:");
  Serial.println("  1. Check all SPI wiring");
  Serial.println("  2. Try MCUFRIEND_kbv library");
  Serial.println();
}

void loop() {
  // Cycle through colors slowly
  tft.fillScreen(ILI9341_RED);
  delay(1000);
  tft.fillScreen(ILI9341_GREEN);
  delay(1000);
  tft.fillScreen(ILI9341_BLUE);
  delay(1000);
}

