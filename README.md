# Escape Room Countdown Timer

An Arduino-based countdown timer for escape rooms with keypad input, TFT display, LED indicators, and audio feedback.

## Features

- Configurable countdown time
- Configurable secret code
- Configurable penalty time (when timer expires)
- Visual countdown display with custom message
- Audio beeps each minute (different tones)
- Wrong code: red LED flash, buzz, screen flash
- Correct code: green LED flash, success message
- Timer expiration: "Transmission error" message + penalty time added
- Reset/configuration mode: Hold * and # for 5 seconds

## Hardware Requirements

- Arduino Uno
- 3x4 Matrix Keypad (1-9, *, 0, #)
- 3.2" TFT SPI Display 240x320 (ILI9341 or compatible)
- Passive Speaker/Buzzer
- 1x Green LED + 220-330Ω resistor
- 1x Red LED + 220-330Ω resistor
- Breadboard and jumper wires

## Required Libraries

Install these libraries via Arduino IDE Library Manager:

1. **Adafruit GFX Library** by Adafruit
2. **Adafruit ILI9341** by Adafruit (or MCUFRIEND_kbv if ILI9341 doesn't work)
3. **Keypad** by Mark Stanley, Alexander Brevig

### Installing Libraries

1. Open Arduino IDE
2. Go to Sketch → Include Library → Manage Libraries
3. Search for each library and click "Install"

## Wiring

See `wiring_diagram.md` for complete wiring instructions.

## Setup Instructions

1. Install the required libraries (see above)
2. Open `escape_room_timer/escape_room_timer.ino` in Arduino IDE
3. Connect your Arduino Uno to your computer
4. Select the correct board: Tools → Board → Arduino Uno
5. Select the correct port: Tools → Port → (your Arduino port)
6. Upload the sketch

## Testing

The project includes test sketches in subdirectories:
- `test_tft/` - Test TFT display
- `test_keypad/` - Test keypad input
- `test_speaker/` - Test speaker tones
- `test_leds/` - Test LED indicators

Run each test sketch individually to verify your wiring before running the main program.

## Usage

### First Time Setup / Reset

1. Hold down * and # keys simultaneously for 5 seconds
2. Screen will prompt: "Enter countdown time (minutes) and press #"
   - Example: Press 1, 5, # for 15 minutes
3. Screen will prompt: "Enter secret code and press #"
   - Example: Press 1, 2, 3, 4, # for code "1234"
4. Screen will prompt: "Enter penalty time (minutes) and press #"
   - Example: Press 5, # for 5 minutes penalty
5. Device enters WAITING mode with custom message

### During Game

- Press any key to start the countdown
- Timer counts down in MM:SS format
- Beeps each minute with different tones
- Enter code and watch for success or error feedback

### What Happens

- **Correct Code**: Green LED flashes, success message displayed
- **Wrong Code**: Red LED flashes, loud buzz, screen flashes, error message, timer continues
- **Timer Expires**: "Transmission error" message, penalty time added, timer continues

## Troubleshooting

### TFT Screen Not Working
- Check if you need MCUFRIEND_kbv library instead of ILI9341
- Verify SPI connections (MOSI, MISO, SCK, CS, DC, RST)
- Try different CS/DC/RST pin assignments

### Keypad Not Responding
- Verify row/column pin assignments match your keypad
- Test with the test_keypad sketch
- Check for loose connections

### No Sound from Speaker
- Ensure speaker is connected to a PWM-capable pin
- Try increasing volume in code
- Verify speaker polarity (though passive buzzers work either way)

### LEDs Not Working
- Check LED polarity (long leg = anode = positive)
- Verify resistor values (220-330Ω)
- Test with the test_leds sketch

## Customization

Edit these variables in the main sketch:
- `INITIAL_MESSAGE` - Message displayed during countdown
- `SUCCESS_MESSAGE` - Message when correct code entered
- `ERROR_MESSAGE` - Message when wrong code entered
- Beep frequencies and durations
- LED flash patterns

## Serial Monitor

Open Serial Monitor (Tools → Serial Monitor) at 9600 baud to see debug information during operation.

