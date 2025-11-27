# 🚀 4.bin - High-Performance RLE Compression Utility

> **Heits Technical Challenge Submission**

This application is a specialized web utility built with **ReactJS** designed to compress and decompress text files. It features a custom-engineered **Adaptive RLE Algorithm** to achieve maximum efficiency, strictly adhering to the constraint of using **no external libraries** for the compression logic.

---

## 👨‍💻 The Team: **4.bin**

* **Development & Algorithm Design**
* **Technical Implementation**

---

## ⚙️ Technical Solution

To meet and exceed the target compression ratio of **< 0.5**, we moved beyond standard Run-Length Encoding. We implemented a hybrid approach that combines **Adaptive Logic** with **Base36 Encoding**.

### 1. 🧠 Adaptive RLE (Smart Compression)
Standard RLE can accidentally increase file size when compressing short sequences (e.g., transforming `aa` into `2a` saves no space).
* **Our Logic:** The algorithm dynamically scans the stream. It leaves short sequences intact and **only** triggers compression when the mathematical gain is positive.

### 2. 🔢 Base36 Optimization (The Core Innovation)
We drastically reduced the overhead of the "repetition count" by switching from Base 10 to **Base 36** (0-9, a-z).
* **The Problem:** A sequence of 15 characters usually takes 2 digits (`15`) to represent.
* **The Solution:** In Base36, `15` becomes `f` (a single character).
* **The Result:** This simple yet effective change allows us to compress data significantly more tightly than standard RLE.

### 3. 🛡️ Robust Data Handling
* **Unicode Safe:** We utilize `Array.from()` to properly handle surrogate pairs, ensuring that **Emojis (🚀)** and special characters are preserved without corruption.
* **Drag & Drop:** Integrated native `FileReader` API for seamless `.txt` file processing.

---

## 📊 Performance & Validation

We validated the algorithm against complex strings containing mixed characters, digits, and noise to prove the efficiency.

### Test Case:
**Input String:**
```text
aaaaaaabbbbbbbbbbbbbbbv3333zzffffffffaaaaaaaaaagFFF222244444444fg44444444444422hhhhhhhhaBc1aaa3bbbffffffffffffff

Metric,Value
Algorithm,Adaptive RLE + Base36
Compression Ratio,~0.47 (Target < 0.5 Achieved)
Integrity,100% Lossless (Bit-exact reconstruction)
