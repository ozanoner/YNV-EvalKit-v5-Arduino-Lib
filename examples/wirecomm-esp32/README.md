# wirecomm-esp32 Companion App

This is the companion application for the **examples/wirecomm** example, designed to run on an ESP32 DevKit using [ESP-IDF 5.4](https://docs.espressif.com/projects/esp-idf/en/v5.4/).  
It demonstrates I2C master communication with the Ynvisible EvalKit running the **wirecomm** Arduino example.

## Features

- I2C master communication with the EvalKit (Arduino as I2C slave)
- Example for sending commands and data to the EvalKit
- Singleton pattern for I2C connection management
- Ready to build and flash with ESP-IDF 5.4

## Requirements

- ESP32 DevKit board
- [ESP-IDF 5.4](https://docs.espressif.com/projects/esp-idf/en/v5.4/)
- Ynvisible EvalKit running the `wirecomm.ino` Arduino example

## Building and Flashing

1. **Set up ESP-IDF 5.4**  
   Follow the [official ESP-IDF setup guide](https://docs.espressif.com/projects/esp-idf/en/v5.4/get-started/index.html).

2. **Clone this repository** (if not already done).

3. **Navigate to the companion app directory:**
   ```sh
   cd examples/wirecomm-esp32

4. **Flash the application on the ESP32 devkit:**
    ```sh
    idf.py flash monitor

5. **Make the I2C connection between the devkits** 
6. Observe the results on the Ynvisible display you have connected.

## Usage
1. Connect the ESP32 I2C pins to the EvalKit's I2C interface. (defaults: SCL=22 SDA=21)
2. Power both devices.
3. The ESP32 will send commands to the EvalKit. Observe the behaviour.
4. You can plug the power off and see how long the ECD display retains the latest view.

## Customization
Update both *examples/wirecomm* and *examples/wirecomm-esp32* to complement each other


## License

See the root project for license details.