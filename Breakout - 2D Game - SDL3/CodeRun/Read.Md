# CodeRun Breakout (SDL3 Edition)

A classic Breakout arcade game clone built using C++ and the modern **SDL3** library. The game features physics-based collision detection, multi-hit destructible bricks, and win/loss states.



## 🎮 Features

- **Engine:** Built on the new SDL3 framework for hardware-accelerated 2D rendering.
- **Physics:** Circle-Rectangle collision detection with angle reflection based on paddle hit position.
- **Difficulty System:**
  - 🟩 **Green Bricks:** 3 hits to destroy.
  - 🟨 **Yellow Bricks:** 2 hits to destroy.
  - 🟥 **Red Bricks:** 1 hit to destroy.
- **Game Loops:** Start screen, gameplay, victory, and game over states.

## 🕹️ Controls

| Key | Action |
| :--- | :--- |
| **Left Arrow** `←` | Move Paddle Left |
| **Right Arrow** `→` | Move Paddle Right |
| **Spacebar** | Launch Ball |
| **R** | Restart Game (after Win/Loss) |
| **ESC** | Quit Game |

## 🛠️ Technical Details

- **Window Resolution:** 800x800
- **Frame Rate:** Capped at ~60 FPS
- **Dependencies:**
  - [SDL3 Library](https://github.com/libsdl-org/SDL) (Linked dynamically)

## 📦 How to Build

1. Ensure you have Visual Studio (or your preferred C++ IDE) installed.
2. Setup the **SDL3** dependencies (Include directories and Library directories).
3. Copy `SDL3.dll` into the output folder (where the `.exe` is generated).
4. Run the project.
