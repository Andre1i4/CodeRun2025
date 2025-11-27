# 🤖 Safe Cracker Robot - Vibration Detection Mode

This Arduino project controls a robot designed to crack a mechanical combination lock. Unlike brute-force algorithms that try every number, this robot mimics a human safecracker: it turns the dial and "listens" for the mechanical click of the tumblers aligning using an **MPU6050 accelerometer**.

## 🧠 How It Works

The robot uses a "Manual Mechanical Input" strategy:

1.  **Initialization:** The servo resets to the leftmost position (-90° / Logical 0).
2.  **Scan Right (CW):** It moves step-by-step towards the right, checking for vibrations at specific angles (-90, -75, -60, etc.).
3.  **Detection:** If the MPU6050 detects a vibration spike above the `THRESHOLD`, it registers that angle as a valid number.
4.  **Switch Direction (CCW):** Once a number is found, the robot reverses direction and scans towards the left to find the next number.
5.  **Completion:** The process repeats until all 10 numbers of the combination are found.

## 🛠️ Hardware Requirements

- **Arduino Board** (Uno, Nano, or compatible)
- **Servo Motor** (Standard SG90 or MG996R)
- **MPU6050** (Accelerometer & Gyroscope Module)
- **Jumper Wires**
- **Mechanical Safe/Lock Mechanism** (or a simulation thereof)

## 🔌 Pin Configuration

| Component | Pin Label | Arduino Pin |
| :--- | :--- | :--- |
| **Servo** | Signal | **D9** |
| | VCC | 5V |
| | GND | GND |
| **MPU6050** | SDA | **A4** (Uno) / D2 (Leonardo) |
| | SCL | **A5** (Uno) / D3 (Leonardo) |
| | VCC | 3.3V or 5V |
| | GND | GND |

## ⚙️ Configuration & Tuning

The most critical part of this project is tuning the sensitivity to distinguish between motor noise and the actual "click" of the lock.

### Key Variables in Code:

1.  **`VIBRATION_THRESHOLD` (Default: 20000)**
    * Adjust this based on your physical setup.
    * **Too Low:** The robot stops at every step (false positives).
    * **Too High:** The robot misses the correct numbers.
    * *Tip:* Use the Serial Monitor to watch the "Vib" values while testing.

2.  **`SEARCH_ANGLES`**
    * The array defines the specific positions the lock can stop at. Currently set to 15-degree increments from -90 to 90.

3.  **`MOVE_DELAY` & `SETTLE_DELAY`**
    * `MOVE_DELAY`: Time allowed for the servo to travel.
    * `SETTLE_DELAY`: Critical pause to let the mechanism stop shaking before taking a reading.

## 🚀 How to Run

1.  Open `SafeCracker.ino` in the Arduino IDE.
2.  Install the required libraries (if not already present):
    * `Servo.h` (Built-in)
    * `Wire.h` (Built-in)
3.  Connect your Arduino to the PC.
4.  Select the correct Board and Port.
5.  Upload the code.
6.  Open **Serial Monitor** at **115200 baud** to view the progress.

## 📊 Logic Flow

```text
[ START ] -> Move to -90°
    |
    v
[ LOOP ] -> Is current step Even or Odd?
    |
    +-- EVEN (0, 2, 4...) -> Scan RIGHT (Angle++).
    |                        Reading sensor...
    |                        > Click detected? -> Save & BREAK loop.
    |
    +-- ODD (1, 3, 5...)  -> Scan LEFT (Angle--).
                             Reading sensor...
                             > Click detected? -> Save & BREAK loop.
    |
    v
[ REPEAT ] until 10 numbers found.
