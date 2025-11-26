#include <Servo.h>

Servo myServo;

const int pinSensor = A0; // Previously p_senzor
const int pinServo = 9;   // Previously p_servo

// THRESHOLD (Keep it as you tuned it, e.g., 300 or 400)
// Dark = High Value, Light = Low Value
int THRESHOLD = 300; // Previously PRAG

// === NEW TIMES FROM TABLE (milliseconds) ===
// Short: 1 - 15ms
// Long: 38 - 60ms
// We decide the separation threshold at 25ms (between 15 and 38)

const int SHORT_LIMIT = 28; // Below 28ms is SHORT (Previously LIMITA_SCURT)
const int LONG_MIN = 30;    // Above 30ms is LONG  (Previously MINIM_LUNG)
const int TIMEOUT = 150;    // If quiet for 150ms, sequence ended

// Angles
int angles[] = {20, 65, 115, 160}; // Previously unghiuri

// The Table
char codes[5][5] = { // Previously coduri
  {'A', 'A', 'B', 'A', 'C'}, 
  {'C', 'B', 'C', 'C', 'B'}, 
  {'D', 'A', 'C', 'D', 'C'}, 
  {'B', 'D', 'B', 'B', 'A'}, 
  {'D', 'C', 'A', 'B', 'C'}  
};

void setup() {
  // ATTENTION: Change Serial Monitor baud rate to 115200 below!
  Serial.begin(115200); 
  
  myServo.attach(pinServo);
  myServo.write(90); 
  Serial.println("TURBO Mode activated. Waiting for rapid signal...");
}

void loop() {
  int val = analogRead(pinSensor);
  
  // If light is detected (low value)
  if (val < THRESHOLD) { 
    decideSequence(); // Previously decideSecventa
  }
}

void decideSequence() {
  int shorts = 0; // Previously scurte
  int longs = 0;  // Previously lungi
  bool active = true; // Previously activ
  
  // Block interrupts (optional, but helps with speed)
  // noInterrupts(); 

  while (active) {
    unsigned long startTime = micros(); // Use micros() for higher precision
    
    // 1. While it is LIGHT
    while (analogRead(pinSensor) < THRESHOLD) {
      // Loop waits for the flash to finish
      // If sensor gets stuck on light, force exit
      if (micros() - startTime > 200000) break; // 200ms safety
    }
    
    // Calculate duration in milliseconds
    unsigned long duration = (micros() - startTime) / 1000;

    // Minimal filter (ignore noise under 1ms)
    if (duration >= 1) { 
        if (duration <= SHORT_LIMIT) {
           shorts++;
        } else if (duration >= LONG_MIN) {
           longs++;
        }
    }

    // 2. Pause (DARK)
    unsigned long pauseStart = millis();
    while (analogRead(pinSensor) > THRESHOLD) {
      // If pause is longer than max T0 + margin -> DONE
      if (millis() - pauseStart > TIMEOUT) {
        active = false; 
        break;
      }
    }
  }
  
  // interrupts(); // Reactivate interrupts

  // Motor Actuation
  if (shorts > 0 && longs > 0) {
    if (shorts > 5) shorts = 5;
    if (longs > 5) longs = 5;

    char zone = codes[shorts - 1][longs - 1]; // Previously zona
    
    // Show result ONLY at the end so we don't slow down reading
    Serial.print("Result: "); 
    Serial.print(shorts); Serial.print(" S, ");
    Serial.print(longs); Serial.print(" L -> "); 
    Serial.println(zone);
    
    moveServo(zone); // Previously mutaMotor
  }
}

void moveServo(char zone) {
    int angle = 90; // Previously unghi
    if (zone == 'A') angle = angles[0];
    if (zone == 'B') angle = angles[1];
    if (zone == 'C') angle = angles[2];
    if (zone == 'D') angle = angles[3];
    
    myServo.write(angle);
    delay(2000); 
    myServo.write(90); 
}