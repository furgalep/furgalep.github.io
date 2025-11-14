/*
 * Detailed TFT Diagnostic
 * Tests different configurations to find the issue
 */

#include <SPI.h>

#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("=================================");
  Serial.println("Detailed TFT Diagnostic");
  Serial.println("=================================");
  Serial.println();
  
  // Setup pins
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_RST, OUTPUT);
  
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(TFT_DC, HIGH);
  digitalWrite(TFT_RST, HIGH);
  
  Serial.println("Pin Setup:");
  Serial.println("  CS  = Pin 10");
  Serial.println("  DC  = Pin 8");
  Serial.println("  RST = Pin 9");
  Serial.println("  MOSI = Pin 11");
  Serial.println("  MISO = Pin 12");
  Serial.println("  SCK  = Pin 13");
  Serial.println();
  
  // Initialize SPI
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  
  Serial.println("SPI initialized");
  Serial.println();
  
  // Hardware reset
  Serial.println("Performing hardware reset...");
  digitalWrite(TFT_RST, LOW);
  delay(100);
  digitalWrite(TFT_RST, HIGH);
  delay(200);
  
  Serial.println("Attempting to read display ID...");
  Serial.println();
  
  // Try reading ID with different methods
  uint16_t id1 = readRegister(0x00, 0);
  Serial.print("Method 1 (Reg 0x00): 0x");
  Serial.println(id1, HEX);
  
  uint16_t id2 = readRegister(0xD3, 1);
  Serial.print("Method 2 (Reg 0xD3): 0x");
  Serial.println(id2, HEX);
  
  uint32_t id3 = readRegister32(0xD3);
  Serial.print("Method 3 (32-bit): 0x");
  Serial.println(id3, HEX);
  
  uint16_t id4 = readRegister(0x04, 1);
  Serial.print("Method 4 (Reg 0x04): 0x");
  Serial.println(id4, HEX);
  
  Serial.println();
  Serial.println("=================================");
  Serial.println("WIRING VERIFICATION:");
  Serial.println("=================================");
  Serial.println();
  Serial.println("Please verify these connections:");
  Serial.println();
  Serial.println("Display Pin    ->  Arduino Pin");
  Serial.println("--------------------------------");
  Serial.println("VCC            ->  5V");
  Serial.println("GND            ->  GND");
  Serial.println("CS             ->  10");
  Serial.println("RESET          ->  9");
  Serial.println("DC             ->  8");
  Serial.println("SDI(MOSI)      ->  11");
  Serial.println("SCK            ->  13");
  Serial.println("SDO(MISO)      ->  12");
  Serial.println("LED            ->  5V");
  Serial.println();
  Serial.println("IMPORTANT:");
  Serial.println("- Use CS pin (NOT T_CS)");
  Serial.println("- Use SCK pin (NOT T_CLK)");
  Serial.println("- Use SDI pin (NOT T_DIN)");
  Serial.println();
  Serial.println("If all IDs show 0xFFFF:");
  Serial.println("  -> Check MISO (Pin 12) connection");
  Serial.println("  -> Try different jumper wires");
  Serial.println();
  Serial.println("If all IDs show 0xD3D3 or similar:");
  Serial.println("  -> Check SCK (Pin 13) connection");
  Serial.println("  -> Check MOSI (Pin 11) connection");
  Serial.println("  -> Try pressing display firmly");
  Serial.println("     into breadboard");
  Serial.println();
}

void loop() {
  // Do nothing
}

uint16_t readRegister(uint8_t reg, uint8_t dummy) {
  digitalWrite(TFT_CS, LOW);
  digitalWrite(TFT_DC, LOW);  // Command
  
  SPI.transfer(reg);
  
  digitalWrite(TFT_DC, HIGH); // Data
  
  // Dummy reads
  for (uint8_t i = 0; i < dummy; i++) {
    SPI.transfer(0x00);
  }
  
  uint16_t value = 0;
  value = SPI.transfer(0x00) << 8;
  value |= SPI.transfer(0x00);
  
  digitalWrite(TFT_CS, HIGH);
  
  return value;
}

uint32_t readRegister32(uint8_t reg) {
  digitalWrite(TFT_CS, LOW);
  digitalWrite(TFT_DC, LOW);  // Command
  
  SPI.transfer(reg);
  
  digitalWrite(TFT_DC, HIGH); // Data
  
  // Dummy read
  SPI.transfer(0x00);
  
  uint32_t value = 0;
  value = (uint32_t)SPI.transfer(0x00) << 16;
  value |= (uint32_t)SPI.transfer(0x00) << 8;
  value |= SPI.transfer(0x00);
  
  digitalWrite(TFT_CS, HIGH);
  
  return value;
}

