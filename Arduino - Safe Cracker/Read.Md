# Light Pattern Servo Controller (Turbo Mode)

This Arduino project controls a Servo motor based on light patterns detected by a photoresistor (LDR). It interprets sequences of "Short" and "Long" light flashes to trigger specific movements, functioning like a high-speed optical lock or decoder.

## 🚀 Features

- **High Precision Detection:** Uses `micros()` for sub-millisecond accuracy in timing light flashes.
- **Pattern Decoding:** Distinguishes between short (1-28ms) and long (30ms+) signals.
- **Matrix Logic:** Uses a 5x5 lookup table (`codes`) to map signal counts to 4 distinct zones (A, B, C, D).
- **Servo Control:** Moves the servo to specific angles based on the decoded zone.

## 🛠️ Hardware Required

1. **Arduino Board** (Uno, Nano, or compatible)
2. **Servo Motor** (e.g., SG90)
3. **Light Sensor** (LDR / Photoresistor)
4. **Resistor** (10kΩ for the voltage divider with the LDR)
5. **Jumper Wires**



## 🔌 Pin Configuration

| Component | Pin | Variable Name |
| :--- | :--- | :--- |
| **Light Sensor** | A0 | `pinSensor` |
| **Servo Signal** | D9 | `pinServo` |

## ⚙️ Configuration

You can tune the sensitivity and timing in the code variables:

- `THRESHOLD`: Adjusts light sensitivity (Standard: 300).
- `SHORT_LIMIT`: Max duration for a short signal (28ms).
- `LONG_MIN`: Min duration for a long signal (30ms).
- `TIMEOUT`: Time to wait before processing the sequence (150ms).

## 📊 Logic Matrix

The system counts the number of **Shorts** (rows) and **Longs** (columns) to determine the output Zone:

| S \ L | 1 Long | 2 Longs | 3 Longs | 4 Longs | 5 Longs |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **1 Short** | A | A | B | A | C |
| **2 Shorts** | C | B | C | C | B |
| **3 Shorts** | D | A | C | D | C |
| **4 Shorts** | B | D | B | B | A |
| **5 Shorts** | D | C | A | B | C |

## 📦 How to Run

1. Open `ProjectName.ino` in Arduino IDE.
2. Connect your hardware as listed above.
3. Set the **Baud Rate** in Serial Monitor to **115200**.
4. Flash the light at the sensor to trigger the servo.
