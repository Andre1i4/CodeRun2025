# CodeRun 2025 - Competition Portfolio

**Repository Maintainers:** Andre1i4, TopoCezar123

**Event:** CodeRun 2025, Cluj-Napoca

## 📂 Overview

All these projects were developed specifically for the **CodeRun 2025** competition. This repository serves as a centralized portfolio demonstrating multidisciplinary engineering skills, ranging from **Embedded Systems & Robotics** to **Game Engine Development** and **Full-Stack Web Applications**.

## 🛠️ Projects

### 1. Arduino Safe Cracker (VALO-MK1 Bypass)

**Path:** `/Arduino-Safe-Cracker`

**Stack:** C++ (Embedded), Arduino Uno, I2C, PWM

An autonomous robotic tool designed to bypass the **VALO-MK1 Electronic Vault Door** security module. The system interfaces with the lock mechanism using sensor fusion and precise servo actuation.

**Key Features:**

* **Haptic Feedback Analysis:** Utilizes an **MPU6050 6-Axis Accelerometer/Gyroscope** to detect subtle internal vibrations (tumbler clicks) via the I2C bus.

* **Algorithmic Solving:** Implements a 10-step alternating search algorithm (CW/CCW) to deduce the mechanical combination in under 20 seconds.

* **Optical Challenge-Response:** (Optional) Decodes the "PulsedLight™ Unlock Protocol" using a CdS photoresistor, distinguishing between short (1-15ms) and long (38-60ms) optical pulses to calculate the correct unlocking zone.

### 2. Breakout - 2D Game Engine

**Path:** `/Breakout-2D-Game-SDL3`

**Stack:** C++17, SDL3 (Simple DirectMedia Layer)

A high-performance 2D game implementation built from scratch to demonstrate low-level memory management and hardware-accelerated rendering.

**Technical Highlights:**

* **Custom Physics Loop:** Implements real-time AABB (Axis-Aligned Bounding Box) collision detection for ball-and-paddle mechanics.

* **SDL3 Integration:** Leverages the latest SDL3 API for efficient window management, event polling, and GPU-accelerated texture rendering.

* **Resource Management:** Manual handling of textures and surfaces to ensure zero memory leaks during runtime.

### 3. Django Treasure Hunt Platform

**Path:** `/Django-Treasure-Hunt`

**Stack:** Python 3.x, Django Framework, SQLite/PostgreSQL, Bootstrap

A server-side web application designed to host a multi-stage digital treasure hunt. The platform manages user progression, riddle validation, and state persistence.

**Functionality:**

* **MVC Architecture:** Utilizes Django's Model-View-Template (MVT) pattern to serve dynamic puzzle content based on user authentication status.

* **Progression Logic:** Implements stateful user tracking, ensuring players must solve cryptographic or logic puzzles sequentially to unlock subsequent URLs.

* **Admin Dashboard:** leverages the Django Admin interface for real-time monitoring of user progress and rapid content management during the competition.

### 4. RLE Compression Utility

**Path:** `/RLE-compressed-text-utility-HEITS`

**Stack:** JavaScript, React.js, Node.js

A web-based algorithmic utility designed to demonstrate lossless data compression principles.

**Functionality:**

* **Run-Length Encoding (RLE):** Implements a custom algorithm to compress repetitive data streams by storing sequences of data as a single data value and count.

* **Real-time Visualization:** React-based frontend providing immediate feedback on compression ratios and text stream processing.

## 🚀 Usage & Deployment

### Cloning the Repository

```bash
git clone [https://github.com/Andre1i4/CodeRun2025.git](https://github.com/Andre1i4/CodeRun2025.git)
cd CodeRun2025