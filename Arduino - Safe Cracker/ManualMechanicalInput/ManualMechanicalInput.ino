/*
 * Safe Cracker Robot - "Manual Mechanical Input" Mode
 * How it works:
 * 1. Start: Moves to the leftmost position (-90) and waits.
 * 2. Going Right (CW): Scans from current position towards the right.
 * 3. Going Left (CCW): Scans from current position towards the left.
 * 4. Rule: If vibration > threshold, record position and switch direction.
 */

#include <Servo.h>
#include <Wire.h>

const int SERVO_PIN = 9;
const int MPU_ADDR = 0x68;

// List of all positions to verify
// NOTE: We map these logical angles (-90 to 90) to Servo angles (0 to 180)
const int SEARCH_ANGLES[] = {-90, -75, -60, -45, -30, -15, 0, 15, 30, 45, 60, 75, 90};
const int NUM_ANGLES = 13;
const int MAX_STEPS = 10;

// SENSITIVITY THRESHOLD
// If sensor sum > this value, we assume a "click" happened.
// You may need to tune this (e.g., 18000 to 25000) depending on gravity/mounting.
const long VIBRATION_THRESHOLD = 20000; 

// TIMING CONSTANTS (Milliseconds)
// Critical to keep these low to finish 10 steps in < 20 seconds!
const int MOVE_DELAY = 100;   // Time for servo to move 15 degrees
const int SETTLE_DELAY = 20;  // Time to wait before reading vibration
const int FOUND_DELAY = 200;  // Short pause when number is found

Servo lockServo;
int currentLockStep = 0;
int crackedCombination[MAX_STEPS];
int currentAngleIndex = 0; // Tracks where the servo currently is in the array (0 to 12)

// Function to read vibration intensity from MPU6050
long readVibration() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  if (Wire.available() < 6) return 0;

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();

  // Sum of absolute values implies total force (Gravity + Vibration)
  return abs(AcX) + abs(AcY) + abs(AcZ);
}

void setup() {
  Serial.begin(115200); // Faster serial is better for debugging
  Wire.begin();
  
  // Initialize MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  lockServo.attach(SERVO_PIN);
  
  Serial.println("*** ROBOT START ***");

  // Reset to Start Position (Leftmost / -90 degrees)
  // According to manual: "Initiated by turning knob all the way to leftmost"
  Serial.println(">>> Moving to Start Position (-90)...");
  
  currentAngleIndex = 0; // Index 0 is -90
  int startServoAngle = map(SEARCH_ANGLES[currentAngleIndex], -90, 90, 0, 180);
  lockServo.write(startServoAngle); 
  
  delay(1000); // Wait for initialization
  Serial.println(">>> READY. Starting scan! <<<");
}

void loop() {
  // Check if we found all numbers
  if (currentLockStep >= MAX_STEPS) {
    Serial.println(">>> DONE! Safe cracked. <<<");
    Serial.print("Combination found: ");
    for(int k=0; k<MAX_STEPS; k++) {
      Serial.print(crackedCombination[k]);
      Serial.print(" ");
    }
    Serial.println();
    
    // Stop forever (or until reset)
    while(true) { delay(1000); }
  }

  Serial.print("\n Searching for Step "); Serial.print(currentLockStep + 1);

  // Determine direction: Even steps = CW (Right), Odd steps = CCW (Left)
  bool goingRight = (currentLockStep % 2 == 0); 

  if (goingRight) {
    Serial.println(" [ Direction: RIGHT >>> ]");
    
    // Scan from current position UPWARDS to the end
    // We start from currentAngleIndex + 1 so we don't re-check the spot we are sitting on
    for (int i = currentAngleIndex + 1; i < NUM_ANGLES; i++) {
       if (checkAngle(i)) {
          currentAngleIndex = i; // Update our known position
          break; // Stop scanning, go to next step (which will reverse direction)
       }
       currentAngleIndex = i; // Update position even if we didn't find it
    }
    
  } else {
    Serial.println(" [ Direction: LEFT <<< ]");
    
    // Scan from current position DOWNWARDS to the start
    for (int i = currentAngleIndex - 1; i >= 0; i--) {
       if (checkAngle(i)) {
          currentAngleIndex = i;
          break;
       }
       currentAngleIndex = i;
    }
  }
}

// Moves servo, listens for vibration, returns TRUE if found
bool checkAngle(int index) {
    int testAngle = SEARCH_ANGLES[index];

    // Map logical angle (-90 to 90) to Servo angle (0 to 180)
    int servoAngle = map(testAngle, -90, 90, 0, 180);
    lockServo.write(servoAngle);
    
    delay(MOVE_DELAY); // Wait for servo to reach position

    // Small delay to let mechanical vibrations settle before reading
    delay(SETTLE_DELAY); 
    
    long vibration = readVibration();
    
    // Debug print (comment out if it slows down too much)
    // Serial.print("Ang: "); Serial.print(testAngle); Serial.print(" Vib: "); Serial.println(vibration);

    if (vibration > VIBRATION_THRESHOLD) {
      Serial.print(" -> CLICK! Found at "); Serial.print(testAngle); 
      Serial.print(" (Vib: "); Serial.print(vibration); Serial.println(")");
      
      // Save the number
      crackedCombination[currentLockStep] = testAngle;
      currentLockStep++; 
      
      delay(FOUND_DELAY); // Brief pause to visualize success
      return true; // Found it
    }
    
    return false; // Nothing here
}