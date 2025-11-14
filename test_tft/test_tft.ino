/*
 * TFT Display Test
 * Tests the 3.2" TFT SPI display to identify driver and verify wiring
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
  Serial.println("TFT Display Test");
  Serial.println("Initializing display...");
  
  // Initialize display
  tft.begin();
  
  Serial.println("Display initialized!");
  Serial.print("Display width: ");
  Serial.println(tft.width());
  Serial.print("Display height: ");
  Serial.println(tft.height());
  
  // Clear screen with black
  tft.fillScreen(ILI9341_BLACK);
  delay(500);
  
  // Test 1: Color bars
  Serial.println("\nTest 1: Color bars");
  testColorBars();
  delay(2000);
  
  // Test 2: Text display
  Serial.println("Test 2: Text display");
  testText();
  delay(2000);
  
  // Test 3: Shapes
  Serial.println("Test 3: Shapes");
  testShapes();
  delay(2000);
  
  // Test 4: Large text (for countdown)
  Serial.println("Test 4: Large text");
  testLargeText();
  
  Serial.println("\nAll tests complete!");
  Serial.println("If you see colorful graphics on screen, the TFT is working!");
}

void loop() {
  // Show success message
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(40, 100);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.println("TFT TEST");
  tft.setCursor(40, 140);
  tft.println("SUCCESS!");
  
  delay(1000);
  
  // Flash colors
  tft.fillScreen(ILI9341_RED);
  delay(200);
  tft.fillScreen(ILI9341_GREEN);
  delay(200);
  tft.fillScreen(ILI9341_BLUE);
  delay(200);
}

void testColorBars() {
  tft.fillScreen(ILI9341_BLACK);
  
  int barHeight = tft.height() / 6;
  tft.fillRect(0, 0, tft.width(), barHeight, ILI9341_RED);
  tft.fillRect(0, barHeight, tft.width(), barHeight, ILI9341_GREEN);
  tft.fillRect(0, barHeight*2, tft.width(), barHeight, ILI9341_BLUE);
  tft.fillRect(0, barHeight*3, tft.width(), barHeight, ILI9341_YELLOW);
  tft.fillRect(0, barHeight*4, tft.width(), barHeight, ILI9341_CYAN);
  tft.fillRect(0, barHeight*5, tft.width(), barHeight, ILI9341_MAGENTA);
}

void testText() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("Escape Room Timer");
  tft.println();
  tft.setTextColor(ILI9341_YELLOW);
  tft.println("TFT Display Test");
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(1);
  tft.println("Resolution: 240x320");
  tft.println("Driver: ILI9341");
  tft.println();
  tft.setTextColor(ILI9341_CYAN);
  tft.println("If you can read this,");
  tft.println("the display is working!");
}

void testShapes() {
  tft.fillScreen(ILI9341_BLACK);
  
  // Draw some shapes
  tft.drawRect(20, 20, 100, 80, ILI9341_RED);
  tft.fillRect(30, 30, 80, 60, ILI9341_BLUE);
  
  tft.drawCircle(180, 60, 40, ILI9341_GREEN);
  tft.fillCircle(180, 60, 30, ILI9341_YELLOW);
  
  tft.drawLine(0, 120, 240, 120, ILI9341_WHITE);
  tft.drawLine(120, 0, 120, 320, ILI9341_WHITE);
  
  // Draw some text
  tft.setCursor(40, 140);
  tft.setTextColor(ILI9341_MAGENTA);
  tft.setTextSize(2);
  tft.println("SHAPES TEST");
}

void testLargeText() {
  tft.fillScreen(ILI9341_BLACK);
  
  // Simulate countdown display
  tft.setCursor(10, 60);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("SOLVE THE PUZZLE!");
  
  // Large countdown
  tft.setCursor(30, 120);
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(5);
  tft.println("15:00");
  
  // Code prompt
  tft.setCursor(20, 200);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.println("Enter Code:");
  tft.setCursor(20, 230);
  tft.setTextSize(3);
  tft.println("****");
}

