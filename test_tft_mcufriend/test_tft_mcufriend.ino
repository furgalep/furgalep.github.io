/*
 * TFT Display Auto-Detection using MCUFRIEND_kbv
 * This will identify the actual controller chip in your display
 */

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

void setup() {
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("TFT Display Auto-Detection");
  Serial.println("=================================");
  Serial.println();
  
  Serial.println("Reading display ID...");
  
  uint16_t identifier = tft.readID();
  
  Serial.print("Display ID: 0x");
  Serial.println(identifier, HEX);
  Serial.println();
  
  // Identify the controller
  Serial.println("Controller identification:");
  switch (identifier) {
    case 0x9341:
      Serial.println("  -> ILI9341");
      break;
    case 0x9486:
      Serial.println("  -> ILI9486");
      break;
    case 0x9481:
      Serial.println("  -> ILI9481");
      break;
    case 0x7575:
      Serial.println("  -> HX8347-G");
      break;
    case 0x7783:
      Serial.println("  -> ST7781");
      break;
    case 0x8357:
      Serial.println("  -> HX8357D");
      break;
    case 0x9595:
      Serial.println("  -> HX8347-A");
      break;
    case 0x9488:
      Serial.println("  -> ILI9488");
      break;
    default:
      Serial.print("  -> Unknown (0x");
      Serial.print(identifier, HEX);
      Serial.println(")");
      Serial.println("  -> MCUFRIEND will try anyway");
      break;
  }
  
  Serial.println();
  Serial.println("Initializing display with detected ID...");
  
  tft.begin(identifier);
  
  Serial.println("Display initialized!");
  Serial.print("Width: ");
  Serial.println(tft.width());
  Serial.print("Height: ");
  Serial.println(tft.height());
  Serial.println();
  
  Serial.println("Testing color fills...");
  Serial.println("Watch your screen!");
  Serial.println();
  
  // Test colors
  Serial.println("RED");
  tft.fillScreen(0xF800);  // Red
  delay(1000);
  
  Serial.println("GREEN");
  tft.fillScreen(0x07E0);  // Green
  delay(1000);
  
  Serial.println("BLUE");
  tft.fillScreen(0x001F);  // Blue
  delay(1000);
  
  Serial.println("WHITE");
  tft.fillScreen(0xFFFF);  // White
  delay(1000);
  
  Serial.println("BLACK");
  tft.fillScreen(0x0000);  // Black
  delay(1000);
  
  // Draw text
  Serial.println("Drawing text...");
  tft.fillScreen(0x0000);
  tft.setTextColor(0x07E0);  // Green text
  tft.setTextSize(3);
  tft.setCursor(20, 100);
  tft.println("SUCCESS!");
  tft.setTextSize(2);
  tft.setCursor(20, 150);
  tft.println("Display works!");
  
  Serial.println();
  Serial.println("=================================");
  Serial.println("TEST COMPLETE!");
  Serial.println("=================================");
  Serial.println();
  Serial.println("If you see colors and text:");
  Serial.println("  Your display is working!");
  Serial.println("  Note the Display ID above.");
  Serial.println();
  Serial.println("If nothing appears:");
  Serial.println("  Double-check wiring:");
  Serial.println("  - Pin 11 (MOSI)");
  Serial.println("  - Pin 13 (SCK)");
  Serial.println("  - Pin 10 (CS)");
  Serial.println("  - Pin 8 (DC/RS)");
  Serial.println("  - Pin 9 (RST)");
}

void loop() {
  // Cycle through colors
  tft.fillScreen(0xF800);  // Red
  delay(500);
  tft.fillScreen(0x07E0);  // Green
  delay(500);
  tft.fillScreen(0x001F);  // Blue
  delay(500);
}

