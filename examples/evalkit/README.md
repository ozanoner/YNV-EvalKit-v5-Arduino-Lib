# YNV-EvalKit-v5-Arduino-Lib: `evalkit` Example

This example demonstrates the core features of the YNV-EvalKit-v5-Arduino-Lib, showcasing how to control and animate Ynvisible displays using the EvalKit-v5 board.

## Features

- Initializes the EvalKit display and configuration.
- Demonstrates display selection and dynamic switching.
- Runs a variety of built-in display animations.
- Handles user input (e.g., button presses) to control animations and display state.
- Shows how to use the library's singleton managers for displays and animations.

## File Structure

- `evalkit.ino` – Main Arduino sketch for the EvalKit example.
- `app_config_defs.h` – Application configuration and settings.

## Usage

1. **Connect your Ynvisible EvalKit to your PC.**
2. **Open `evalkit.ino` in the Arduino IDE.**
3. **Upload the sketch to your Arduino board.**
4. **Use the EvalKit buttons to cycle through displays and animations.**
5. **Observe the display responding to user input and running animations.**

## Key Concepts

- **Display Management:**  
  Use `ynv::ecd::EvalkitDisplays::getInstance()` to access and control the current display.

- **Animation Management:**  
  Use `ynv::anim::EvalkitAnims::getInstance()` to select and run animations on the display.

- **Configuration:**  
  All settings are centralized in `app_config_defs.h` for easy modification.

## Extending

- Add new display types or animations by extending the relevant classes.
- Modify `app_config_defs.h` to change default settings or enable/disable features.
- Integrate with other hardware or sensors by adding logic to `evalkit.ino`.

## License
See the root project for license.