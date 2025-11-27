4.bin - Advanced RLE Compression Utility
This is the official submission by Team 4.bin for the Heits Technical Challenge. The application is a high-performance web utility built with ReactJS that compresses and decompresses text files using a custom-engineered algorithm, strictly adhering to the "no external logic libraries" constraint.

👨‍💻 The Team
4.bin

⚙️ Technical Solution
To achieve maximum compression efficiency and meet the < 0.5 compression ratio requirement, we implemented a custom Adaptive Run-Length Encoding (RLE) algorithm augmented with Base36 optimization.

1. Adaptive RLE (Smart Compression)
Standard RLE can paradoxically increase file size for short sequences (e.g., aa becoming 2a offers no gain).

Our Solution: The algorithm dynamically decides when to compress. It leaves short sequences intact and only triggers compression when there is a net gain in space.
2. Base36 Optimization (The "Secret Sauce")
To significantly reduce the character count for the repetition headers, we convert the repetition count from Base 10 to Base 36 (0-9, a-z).

Why? A repetition of 15 characters typically requires 2 digits (15). In Base36, it requires only 1 character (f).
Impact: This drastic reduction allows us to consistently drop below the 0.5 compression ratio threshold.
3. Robust Data Handling
Unicode Support: We use Array.from() to correctly split and process surrogate pairs, ensuring full support for Emojis (🚀) and special characters without breaking the string parsing logic.
Drag & Drop: Implemented using the native FileReader API for seamless .txt processing.
🚀 How to Run
In the project directory, you can run:

# 1. Install dependencies
npm install

# 2. Start the development server
npm start
