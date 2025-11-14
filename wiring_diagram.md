# Wiring Diagram - Escape Room Timer

## Pin Assignments

### TFT Display (3.2" SPI 240x320 - ILI9341)

The TFT uses SPI communication. Connect as follows:

| TFT Pin | Arduino Pin | Notes |
|---------|-------------|-------|
| VCC     | 5V          | Power |
| GND     | GND         | Ground |
| CS      | Pin 10      | Chip Select |
| RESET   | Pin 9       | Reset |
| DC/RS   | Pin 8       | Data/Command |
| MOSI    | Pin 11      | SPI Data (fixed for Uno) |
| SCK     | Pin 13      | SPI Clock (fixed for Uno) |
| LED     | 5V          | Backlight (can add resistor if too bright) |
| MISO    | Pin 12      | SPI Data (fixed for Uno) - may not be used by all displays |

**Note**: If your TFT has an SD card slot, you may need to connect additional pins or disable it in software.

### 3x4 Matrix Keypad

The keypad has 7 pins: 4 rows and 3 columns.

| Keypad Pin | Arduino Pin | Description |
|------------|-------------|-------------|
| Row 1      | Pin 7       | Keys: 1, 2, 3 |
| Row 2      | Pin 6       | Keys: 4, 5, 6 |
| Row 3      | Pin 5       | Keys: 7, 8, 9 |
| Row 4      | Pin 4       | Keys: *, 0, # |
| Col 1      | Pin A0      | Left column |
| Col 2      | Pin A1      | Middle column |
| Col 3      | Pin A2      | Right column |

**Note**: Your keypad ribbon cable pins should be labeled or you may need to test to determine which is which.

### Speaker/Buzzer

| Speaker Pin | Arduino Pin | Notes |
|-------------|-------------|-------|
| Positive (+)| Pin 3       | PWM pin for tone generation |
| Negative (-)| GND         | Ground |

**Note**: Pin 3 is a PWM-capable pin needed for tone() function.

### Green LED (Success Indicator)

```
Arduino Pin 2 ---[220Ω Resistor]---[LED Anode(+)]---[LED Cathode(-)]--- GND
                                    (long leg)       (short leg)
```

| Component | Connection |
|-----------|------------|
| Anode (+) | Pin 2 → Resistor → LED long leg |
| Cathode (-)| LED short leg → GND |

### Red LED (Error Indicator)

```
Arduino Pin A3 ---[220Ω Resistor]---[LED Anode(+)]---[LED Cathode(-)]--- GND
                                     (long leg)       (short leg)
```

| Component | Connection |
|-----------|------------|
| Anode (+) | Pin A3 → Resistor → LED long leg |
| Cathode (-)| LED short leg → GND |

## Complete Pin Summary

| Arduino Pin | Component | Function |
|-------------|-----------|----------|
| Pin 2       | Green LED | Success indicator (via resistor) |
| Pin 3       | Speaker   | Audio feedback (PWM) |
| Pin 4       | Keypad    | Row 4 (*, 0, #) |
| Pin 5       | Keypad    | Row 3 (7, 8, 9) |
| Pin 6       | Keypad    | Row 2 (4, 5, 6) |
| Pin 7       | Keypad    | Row 1 (1, 2, 3) |
| Pin 8       | TFT       | DC/RS (Data/Command) |
| Pin 9       | TFT       | RESET |
| Pin 10      | TFT       | CS (Chip Select) |
| Pin 11      | TFT       | MOSI (SPI - fixed) |
| Pin 12      | TFT       | MISO (SPI - fixed) |
| Pin 13      | TFT       | SCK (SPI - fixed) |
| Pin A0      | Keypad    | Column 1 |
| Pin A1      | Keypad    | Column 2 |
| Pin A2      | Keypad    | Column 3 |
| Pin A3      | Red LED   | Error indicator (via resistor) |

## Breadboard Layout Tips

1. **Power Rails**: Use breadboard power rails for 5V and GND distribution
2. **TFT Display**: May need to be positioned off-breadboard due to size
3. **Keypad**: Can be connected via ribbon cable to breadboard
4. **LEDs**: Place on breadboard with resistors in series
5. **Speaker**: Place on breadboard or connect with jumper wires

## Wiring Steps

### Step 1: Power Distribution
1. Connect Arduino 5V to breadboard positive rail
2. Connect Arduino GND to breadboard negative rail

### Step 2: TFT Display
1. Connect all TFT pins according to table above
2. Double-check SPI pins (11, 12, 13) - these are fixed on Arduino Uno
3. Ensure CS, RESET, and DC are on the correct pins (10, 9, 8)

### Step 3: Keypad
1. Connect 7 keypad wires to pins 7, 6, 5, 4, A0, A1, A2
2. You may need to test to determine which wire is which row/column
3. Use the test_keypad sketch to verify

### Step 4: LEDs
1. Insert Red LED on breadboard (long leg = anode = positive)
2. Connect 220Ω resistor from A3 to LED anode
3. Connect LED cathode to GND rail
4. Repeat for Green LED with pin 2

### Step 5: Speaker
1. Connect speaker positive to pin 3
2. Connect speaker negative to GND rail

## Testing Sequence

Before running the main program, test each component:

1. Upload `test_leds` - verify both LEDs work
2. Upload `test_speaker` - verify buzzer makes sound
3. Upload `test_keypad` - verify all keys register (open Serial Monitor)
4. Upload `test_tft` - verify display works and shows graphics

If any component doesn't work, check wiring and pin assignments.

## Troubleshooting Wiring

### TFT Not Working
- Verify CS=10, DC=8, RST=9
- Check that MOSI=11, SCK=13 (fixed SPI pins)
- Ensure 5V and GND are connected
- Try different TFT library (MCUFRIEND_kbv)

### Keypad Keys Wrong
- Row/column assignments may be reversed
- Test with test sketch and adjust pin arrays in code

### LEDs Backwards
- Flip LED orientation (anode/cathode)
- Check resistor is in series, not parallel

### No Speaker Sound
- Verify pin 3 connection
- Check speaker polarity (try reversing)
- Increase tone duration in test code

## Power Considerations

- Arduino Uno can supply up to 200mA from 5V pin
- TFT typically draws 100-150mA
- LEDs draw ~20mA each
- Keypad and speaker draw minimal current
- **Total**: Should be within Arduino limits when powered via USB

If you experience brownouts or resets:
- Use external 5V power supply (7-12V to Arduino Vin pin)
- Add decoupling capacitors near TFT (100µF)

