# pixelDrift

> [!Warning]
> Currently switching to modular file structure
> Code may have a lot of bug

**A simple, pixel-based driving game/simulation focused on realistic drift physics.**

`pixelDrift` is a C++ project that uses the **SFML** library. The goal is to create a fun, technical drift experience by using a dynamic friction model. The model checks the angle between the car's speed and its direction to create realistic drifting.

## Features (v0.5.0 - Core Mechanics Beta)

This beta version focuses on the main driving parts of the game.

* **Dynamic Drift Physics:** The friction changes based on how much the car is turning. This gives a realistic and satisfying drift feeling.
* **Advanced Gear System:**
    * 7 Forward gears and Reverse (R).
    * Automatic gear (Auto) mode is available.
    * The game suggests the best gear and warns you if you are in the wrong one (by changing the gear text color).
* **User Interface (UI):**
    * Speedometer and RPM gauges.
    * A Mini-Map to show your position.
    * FPS (Frames Per Second) counter.
* **Game Controls:**
    * Functional handbrake.
    * Boundary control to keep the car on the track.
    * A basic menu to start and exit the game.
* **Tire Marks (Skid Marks):** Basic tire marks appear when you use the handbrake.

## Setup and Build (C++)

The project is written in C++ and needs the **SFML** library for graphics and input.

### Requirements

To compile and run this project, you need:

* A C++ Compiler (like GCC, Clang, or MSVC)
* The **SFML Library** (especially the Graphics module)

### How to Compile

Assuming you have SFML installed, here are the general steps:

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/superroket169/pixelDrift.git](https://github.com/superroket169/pixelDrift.git)
    cd pixelDrift
    ```
2.  **Compile:**
    ```bash
    # Example GCC command (adjust paths and libs as needed for your system)
    g++ main.cpp -o pixelDrift src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system
    ```
3.  **Run the Game:**
    ```bash
    ./cd build
    ./run.bat
    ```

## 🎮 Controls

| Action | Key (Keyboard) |
| :--- | :--- |
| **Accelerate** | $\uparrow$ / <kbd>W</kbd> |
| **Brake/Reverse** | $\downarrow$ / <kbd>S</kbd> |
| **Steer Right** | $\rightarrow$ / <kbd>D</kbd> |
| **Steer Left** | $\leftarrow$ / <kbd>A</kbd> |
| **Handbrake** | <kbd>E</kbd> |
| **Shift Up** | <kbd>LShift</kbd> |
| **Shift Down** | <kbd>LControl</kbd> |
| **Toggle Auto Gear** | <kbd>Q</kbd> |
| **Go to Menu** | <kbd>Esc</kbd> |

## Future Plans

We plan to improve these areas next:

* **Improve Graphics:** Greatly improve the tire marks and add smoke effects.
* **Content:** Add a car selection and track selection screen to the main menu (like S15, AE86, Supra MK4, etc.).
* **Customization:** Create an Advanced Settings Panel so players can change friction, brake force, and other physics values.
