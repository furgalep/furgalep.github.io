# **Escape Room Tablet Puzzle: Requirements Document**

## **1\. Overview**

The project is to create a "bomb defusal" style puzzle application for a Samsung Galaxy Tab. The application will function as a self-contained escape room element, locking the tablet to a single interface. Players must input a 4-digit code to "disarm" the device before a countdown timer reaches zero.

## **2\. Functional Requirements**

### **F1: Timer Module**

* **F1.1:** The application shall display a prominent countdown timer.  
* **F1.2:** The timer's font must emulate a 7-segment digital display.  
* **F1.3:** The timer shall emit an audible "beep" (e.g., 880Hz) once per second.  
* **F1.4 (Time-Out Penalty Sequence):** The application shall track the number of times the timer reaches 00:00 and apply escalating penalties.  
  * **F1.4.1 (First Timeout):** On the *first* instance of reaching 00:00:  
    * Play YouTube Video \#1 (fullscreen).  
    * After the video finishes, reset the timer to 50% of the *original* start time.  
  * **F1.4.2 (Second Timeout):** On the *second* instance of reaching 00:00:  
    * Play YouTube Video \#2 (fullscreen).  
    * After the video finishes, reset the timer to 25% of the *original* start time.  
  * **F1.4.3 (Third Timeout):** On the *third* instance of reaching 00:00:  
    * Play YouTube Video \#3 (fullscreen).  
    * After the video finishes, reset the timer to 12.5% of the *original* start time.  
  * **F1.4.4 (Final Timeout):** On the *fourth* instance of reaching 00:00:  
    * Trigger a "Game Over" state (e.g., loud, continuous alarm, "FAILED" message). The timer stops.

### **F2: Keypad Module**

* **F2.1:** A 12-button numeric keypad (0-9, \*, \#) shall be displayed for code entry.  
* **F2.2:** The system must accept a 4-digit code.  
* **F2.3:** Visual feedback (e.g., displaying "\*" for each digit) shall be provided as the code is entered.

### **F3: Code Validation Module**

* **F3.1:** Upon entry of the 4th digit, the code shall be automatically validated.  
* **F3.2 (Success):** If the code is correct:  
  * The timer shall stop.  
  * All sounds (beeps) shall cease.  
  * A "Success" or "Disarmed" message shall be displayed.  
* **F3.3 (Failure):** If the code is incorrect:  
  * A loud, unpleasant "buzz" sound shall play.  
  * A pre-programmed "threatening message" (e.g., "Incorrect. Try again, if you dare.") shall be spoken using Text-to-Speech.  
  * The 4-digit entry shall be cleared, allowing the- user to try again.

### **F4: Visual Feedback & Atmosphere**

* **F4.1 (Dynamic Color):** The application's background color shall transition smoothly based on the percentage of time remaining. The color will interpolate continuously from green (at 100%) to yellow (at 50%) and down to bright red (at 0%).  
* **F4.2 (Dynamic Effects):** Visual effects shall gradually intensify as the timer decreases.  
  * **F4.2.1 (Sparks/Static):** A visual "spark" or "static" overlay shall be present. Its opacity and frequency shall be minimal at 100% time and increase continuously, becoming highly active and obtrusive as the timer approaches 0%.  
  * **F4.2.2 (Flashing):** A subtle, slow red flashing/pulsing effect shall begin around 25% time remaining, increasing in speed and intensity as the timer approaches 0%.

### **F5: Admin Module**

* **F5.1 (Access):** An admin console shall be accessible via a hidden gesture (pressing and holding the on-screen "\*" button for 5 seconds).  
* **F5.2 (Interface):** The admin console shall provide simple inputs for:  
  * Setting the initial countdown time (e.g., 60 minutes, 0 seconds).  
  * Setting the 4-digit success code.  
  * Setting the three YouTube Video IDs for the penalty sequence.  
  * Title text (displayed above the timer).  
  * Idle/instructions text (shown while waiting for code entry).  
  * Success message text (shown on correct code).  
  * Failure TTS message text (spoken on incorrect code).  
  * Game Over message text (shown on final timeout).  
  * **F5.2.1 (Persistence):** When opened, the admin console's input fields shall be pre-populated with the most recently saved values (initial time, success code, video IDs, and all message fields).  
* **F5.3 (Control):** The console shall have a button to "Save, Reset, and Start" the puzzle with the new settings.

### **F6: Editable Messages**

* **F6.1 (Message Set):** The following texts shall be configurable via the admin console and persisted:  
  * **F6.1.1:** Title text displayed above the timer.  
  * **F6.1.2:** Idle/instructions text shown while waiting for code entry.  
  * **F6.1.3:** Success message shown on correct code (timer stopped, sounds cease).  
  * **F6.1.4:** Failure TTS message spoken on incorrect code.  
  * **F6.1.5:** Game Over message shown on final timeout.  
* **F6.2 (Defaults):** If unset, defaults shall be:  
  * Title: "Bomb Defusal"  
  * Idle: "Enter 4-digit code"  
  * Success: "Disarmed"  
  * Failure TTS: "Incorrect. Try again."  
  * Game Over: "FAILED"  
* **F6.3 (Validation):**  
  * Title max 64 chars; other messages max 140 chars.  
  * Failure TTS must be non-empty; other messages may be empty (UI hides empty lines).  
* **F6.4 (Rendering & Usage):**  
  * Title and Idle appear on the main screen; Success replaces Idle upon correct code.  
  * Failure TTS is spoken via system Text-to-Speech; no on-screen alert is required.  
  * Game Over replaces the primary UI on final timeout.  
* **F6.5 (Persistence):** Values shall persist across reloads using `localStorage`.  

## **3\. Non-Functional Requirements**

* **NF1 (Connectivity):** The application requires an active internet connection during gameplay to load and stream the YouTube videos for the penalty sequence.  
* **NF2 (Kiosk Mode):** The application must run full-screen, hiding all tablet navigation (home button, back button) and system UI (status bar, notifications). This will be achieved through a combination of application-level full-screen requests and Android OS-level "App Pinning."  
* **NF3 (Platform):** The solution must run on a standard Samsung Galaxy Tab (Android OS).