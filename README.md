**This file provides useful information on how to use the feather click shield**

# Contents
1. [Arduino IDE setup](#arduino-ide-setup)
2. [Board setup](#board-setup)
3. [References](#references)
    * [Feather Click Shield](#feather-click-shield)
    * [Adafruit Feather M4 CAN](#adafruit-feather-m4-can)
    * [TOUCHPAD 4 CLICK](#touchpad-4-click)
    * [OLED C CLICK](#oled-c-click)
    * [SMART MIC CLICK](#smart-mic-click)
    * [THUMBSTICK CLICK](#thumbstick-click)
    * [8800 RETRO CLICK](#8800-retro-click)
    * [MPU 9DOF CLICK](#mpu-9dof-click)
    * [PROXIMITY 18 CLICK](#proximity-18-click)
    * [RADAR CLICK](#radar-click)
    * [MikroSDK](#mikrosdk)
    * [I2C Scanner](#i2c-scanner)

# Arduino IDE setup

1. Got to `File > Preferences` and enter `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json` into the **Additional Boards Manager URLs**.
2. Click `OK`.
3. Install `Adafruit SAMD Boards` in the **Boards Manager**.
4. Click `Tools > Board > Adafruit SAMD Boards` and selecte the `Adafruit Feather M4 CAN`.

See https://learn.adafruit.com/adafruit-feather-m4-can-express/arduino-ide-setup for more information.

# Board setup

1. Place your `Adafruit feather M4 CAN` in the center of the `Feather click shield`.
2. Place your `Click Boards` into the `mikroBUS` sockets.
3. Connect a USB-C cable into to your computer and directly to the `Feather M4 CAN` (the **upper** USB-C port).

# References

**This section provides useful links, images and code snippets for every component and click board.**

## Feather Click Shield

**Pinout of the feather click shield:**

![grafik](https://www.mikroe.com/img/images/feather-inner-2.png)

## Adafruit Feather M4 CAN 

**Pinout of the adafruit feather m4 can:**

![grafik](https://github.com/VectorInformatik/clickboard-examples/assets/136338757/4107adeb-8cf2-4803-934a-0be1f3d37a52)

## TOUCHPAD 4 CLICK

Component description: https://www.mikroe.com/touchpad-4-click

Controller datasheet: https://www.azoteq.com/images/stories/pdf/iqs7211a_datasheet.pdf

## OLED C CLICK

Component description: https://www.mikroe.com/oled-c-click

Graphics driver datasheet: https://newhavendisplay.com/content/app_notes/SSD1351.pdf

Library: https://github.com/adafruit/Adafruit-SSD1351-library (Can be found in Library Manager. Search: Adafruit SSD1351)

**NOTE: This library doesn't support the 96x96 OLED display. Everything will be offset. No better library was found.**

Code example (draw different shapes):

```c++
// Screen dimensions. True dimensions are 96x96. This is a workaround
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128

// Using Microbus 2
#define SCLK_PIN 25
#define MOSI_PIN 24
#define DC_PIN   13
#define CS_PIN   10
#define RST_PIN  12
#define EN_PIN   11

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

//Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

//Adafruit_SSD1351 tft = Adafruit_SSD1351(CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

void testOLED()
{
  // Single pixel
  tft.drawPixel(tft.width()/2, tft.height()/2, GREEN);
  delay(3000);

  tft.fillScreen(BLACK);

  // lines
  for (uint16_t x=0; x < tft.width()-1; x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, WHITE);
  }
  delay(3000);

  tft.fillScreen(BLACK);

  // fast lines
  for (uint16_t y=0; y < tft.height()-1; y+=5) {
    tft.drawFastHLine(0, y, tft.width()-1, WHITE);
  }
  delay(3000);

  tft.fillScreen(BLACK);

  // text
  tft.setCursor(0,0);
  tft.setTextColor(WHITE);
  tft.print("Hi my name is max");
  delay(3000);

  tft.fillScreen(BLACK);

  // rectangles
  for (uint16_t x=0; x < tft.height()-1; x+=6) {
    tft.drawRect((tft.width()-1)/2 -x/2, (tft.height()-1)/2 -x/2 , x, x, WHITE);
  }
  delay(3000);

  tft.fillScreen(BLACK);

  // fill rectangles
  for (uint16_t x=tft.height()-1; x > 6; x-=6) {
    tft.fillRect((tft.width()-1)/2 -x/2, (tft.height()-1)/2 -x/2 , x, x, WHITE);
    tft.drawRect((tft.width()-1)/2 -x/2, (tft.height()-1)/2 -x/2 , x, x, GREEN);
  }
  delay(3000);

  tft.fillScreen(BLACK);

  uint8_t radius = 4;

  // circles
  for (uint8_t x=0; x < tft.width()-1+radius; x+=radius*2) {
    for (uint8_t y=0; y < tft.height()-1+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, WHITE);
    }
  }
  delay(3000);

  // fill circles
  tft.fillScreen(BLACK);

  for (uint8_t x=radius; x < tft.width()-1; x+=radius*2) {
    for (uint8_t y=radius; y < tft.height()-1; y+=radius*2) {
      tft.fillCircle(x, y, radius, WHITE);
    }
  }  
  delay(3000);
}


void setup(void) {
  Serial.begin(9600);

  // Set enable pin to high
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);

  tft.begin();
}

void loop() {
  testOLED();
}
```

## SMART MIC CLICK

Component description: https://www.mikroe.com/smart-mic-click

Acoustic processor datasheet: http://download.mikroe.com/documents/datasheets/IA611_datasheet.pdf

## THUMBSTICK CLICK

Component description: https://www.mikroe.com/thumbstick-click

Datasheet zum A/D-Converter: http://ww1.microchip.com/downloads/en/devicedoc/21298e.pdf

![grafik](https://github.com/VectorInformatik/clickboard-examples/assets/136338757/0f322c96-dc77-45bc-84b7-314389b9e4e5)
![grafik](https://github.com/VectorInformatik/clickboard-examples/assets/136338757/a62aaf96-48f6-445b-9fe0-92962d6ceb10)

Thumbstick Layout:
![grafik](https://github.com/VectorInformatik/clickboard-examples/assets/136338757/7353b62a-c660-4fb1-bcbb-728389c9526b)


Code example (read thumbstick input):

```c++
#include <SPI.h>

#define CS_PIN 10

int read_thumbstick(int channel) {
  int value = 0;
  
  // Select the MCP3204
  digitalWrite(CS_PIN, LOW);
  
  // Send the start bit, single-ended mode, and channel selection bits
  byte command = B11000000 | (channel << 3);
  SPI.transfer(command);
  
  // Read the 12-bit result (MSB first)
  value = SPI.transfer(0) & B00001111;
  value = (value << 8) + SPI.transfer(0);
  
  // Deselect the MCP3204
  digitalWrite(CS_PIN, HIGH);
  
  return value;
}

void get_user_input()
{
  int dir = 0;

  // Read value for both axes
  int value_0 = read_thumbstick(0);
  int value_1 = read_thumbstick(1);

  int vert = 0;
  int hor = 0;

  // Use thresholds to convert input into (binary) directions
  // This is not required but was used to counter noisy input.
  if (value_0 > 3500) vert = -1;
  else if (value_0 < 500) vert = 1;
  else vert = 0;

  if (value_1 > 3500) hor = 1;
  else if (value_1 < 500) hor = -1;
  else hor = 0;

  Serial.print("User input: vert: ");
  Serial.print(vert);
  Serial.print("  hor: ");
  Serial.print(hor);
  Serial.println();
}

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  pinMode(CS_PIN, OUTPUT);
}

void loop()
{
  get_user_input();
  delay(100);
}
```

## 8800 RETRO CLICK

Component description: https://www.mikroe.com/8800-retro-click

LED driver datasheet: https://ams.com/documents/20143/36005/AS1115_DS000206_1-00.pdf

Code example (flash the character '!' on and off):

```c++
#include <Wire.h>

byte characterOne[] = {0,0,0,1,1,0,0,0,
                       0,0,0,1,1,0,0,0,
                       0,0,0,1,1,0,0,0,
                       0,0,0,1,1,0,0,0,
                       0,0,0,1,1,0,0,0,
                       0,0,0,0,0,0,0,0,
                       0,0,0,1,1,0,0,0,
                       0,0,0,1,1,0,0,0};

 byte characterTwo[] = {0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0};

byte i2c_addr = 0x00;

// Write to 8x8 LED matrix
void show(byte data[]) {
  for (int x=0; x < 8; x++) {
    byte line = 0;
    for (int y=0;y < 8; y++) {
        line = line << 1;
        line = line | data[x*8+y];
    }
    Wire.beginTransmission(i2c_addr);
    Wire.write(x+1);  // select segment
    Wire.write(line); // select digit
    Wire.endTransmission();  
  }
}


void setup()
{
  Serial.begin(9600);

  // LED matrix
  Wire.begin(); // join i2c bus (address optional for master)

  // Wakeup from shutdown mode
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x0c); 
  Wire.write(0x81); 
  Wire.endTransmission();
  delay(1);

  // This device can change slave address dynamically.
  // see p.15 more detail

  // Change device address (p.15)
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x2d); // register
  Wire.write(0x01); // user-defined (0x03 if not connected any pins)
  Wire.endTransmission();  
  delay(1);

  i2c_addr = 0x03; // address changed from here

  // Intensity control (0x0A)
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x0a); // register
  //Wire.write(0x0f); // 15/16 (max)
  Wire.write(0x07); // 8/16 (median)
  //Wire.write(0x00); // 1/16 (min)
  Wire.endTransmission();  
  delay(1);

  // Scan-Limit Register (0x0B)
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x0b); 
  Wire.write(0x07); // display all digits 0:7
  Wire.endTransmission();  
  delay(1);

  // Non-decode mode (0x09) for 8x8 dot matrix
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x09); 
  Wire.write(0x00); // non-decode mode
  Wire.endTransmission();  
  delay(1);
}

void loop()
{
  show(characterOne);
  delay(400);
  show(characterTwo);
  delay(400);
}
```


## MPU 9DOF CLICK

Component description: https://www.mikroe.com/mpu-9dof-click

Datasheet: https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf

Library and examples: https://github.com/hideakitai/MPU9250

Code example (get roll, pitch and yaw):

```c++
#include "MPU9250.h"

MPU9250 mpu;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    mpu.setup(0x68);
}

void loop() {
  if (mpu.update()) {
    print_roll_pitch_yaw();
  }
}

void print_roll_pitch_yaw() {
    Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.println(mpu.getRoll(), 2);
}
```

## PROXIMITY 18 CLICK

Component description: https://www.mikroe.com/proximity-18-click

Datasheet: https://download.mikroe.com/documents/datasheets/VCNL3036X01_datasheet.pdf

Install library: https://github.com/JenertsA/VCNL3040_Proximity_Sensor_Library (Available in Library Manager of Arduino Ide. Search: VCNL3040)
**NOTE: Go to VCNL3040.h and change VCNL3040_DEV_ADDRESS from 0x60 to 0x41.**

Code example (read proximity value):

```c++
#include <VCNL3040.h>
#include <Wire.h>

VCNL3040 sens;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  sens.begin();
  sens.startReading();
}

void loop()
{
  unsigned int dist_raw = sens.readPSData();
  Serial.println(dist_raw);
  delay(100);
}
```

## RADAR CLICK

Component description: https://www.mikroe.com/radar-click

Datasheet: https://download.mikroe.com/documents/datasheets/MM5D91-00_datasheet.pdf

## MikroSDK

Libraries for click boards by MIKROE (**NOT compatible with our board but can be useful**): https://github.com/MikroElektronika/mikrosdk_click_v2

## I2C scanner

Run this code snipped to get the i2c addresses of the connected devices:

```c++
#include <Wire.h>
 
 
void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}
```
