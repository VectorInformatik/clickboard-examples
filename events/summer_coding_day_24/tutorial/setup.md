# Arduino IDE/Platform IO Setup for  Adafruit Feather M4 CAN

## Contents
1. [Arduino IDE setup](##arduino-ide-setup)
2. [PlatformIO setup](##platformio-setup)
3. [Board setup](##board-setup)

## Arduino IDE setup

1. Install the Arduino IDE: [Arduin IDE](https://www.arduino.cc/en/software)
2. Got to `File > Preferences` and enter `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json` into the **Additional Boards Manager URLs**.
3. Click `OK`.
4. Install `Adafruit SAMD Boards` in the **Boards Manager**.
5. Click `Tools > Board > Adafruit SAMD Boards` and selecte the `Adafruit Feather M4 CAN`.
6. Open the Library Manager and install the `Adafruit CAN` library.

See https://learn.adafruit.com/adafruit-feather-m4-can-express/arduino-ide-setup for more information.

## PlatformIO setup

1. Install the PlatformIO IDE extension in Visual Studio Code
2. Open the provided template. If you're not using the template, simply select the `Adafruit Feather M4 CAN` board when you create a new project and add the `Adafruit CAN` library to the project.

## Board setup

1. Place your `Adafruit feather M4 CAN` in the center of the `Feather click shield`.
2. Place your `Click Boards` into the `mikroBUS` sockets.
3. Connect a USB-C cable into to your computer and directly to the `Feather M4 CAN` (the **upper** USB-C port).
