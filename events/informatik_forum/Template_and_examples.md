# Informatik forum

Copy the following code into your project to get started:

```c++
// *************************************************************************************************
// Template for your team. Only change code in the marked sections!
// *************************************************************************************************


#include <Arduino.h>
#include "CANSAME5x.h"

#define BAUDRATE 500000
#define SEND_DELAY_MS 10

// Uncomment your team here ************************************************************************
// #define TEAM_1
// #define TEAM_2
// #define TEAM_3
// #define TEAM_4
// #define TEAM_5


// Communicate with other teams to set these defines
// Important: the values must be in the range (1, 8)
#define YOUR_TEAM_CAN_FRAME_BYTE_COUNT 8
#define PREVIOUS_TEAM_CAN_FRAME_BYTE_COUNT 8

// *************************************************************************************************


#if defined(TEAM_1)
    #define YOUR_TEAM_CAN_ID 0x20
    #define PREVIOUS_TEAM_CAN_ID 0x10
#elif defined(TEAM_2)
    #define YOUR_TEAM_CAN_ID 0x30
    #define PREVIOUS_TEAM_CAN_ID 0x20
#elif defined(TEAM_3)
    #define YOUR_TEAM_CAN_ID 0x40
    #define PREVIOUS_TEAM_CAN_ID 0x30

#elif defined(TEAM_4)
    #define YOUR_TEAM_CAN_ID 0x50
    #define PREVIOUS_TEAM_CAN_ID 0x40

#elif defined(TEAM_5)
    #define YOUR_TEAM_CAN_ID 0x60
    #define PREVIOUS_TEAM_CAN_ID 0x50
#endif


struct Pdu {
    int const id;
    uint8_t* data;
    int const length;

    Pdu(int _id, int _length) : id(_id), length(_length) {
        data = new uint8_t[length];
    };
};

CANSAME5x CAN;
volatile bool newDataReceived = false;
bool sendEnabled = false;
unsigned long nextSendTimestamp;
Pdu previousTeamPdu(PREVIOUS_TEAM_CAN_ID, PREVIOUS_TEAM_CAN_FRAME_BYTE_COUNT);
Pdu yourTeamPdu(YOUR_TEAM_CAN_ID, YOUR_TEAM_CAN_FRAME_BYTE_COUNT);


bool beginCAN() {
    pinMode(PIN_CAN_STANDBY, OUTPUT);
    digitalWrite(PIN_CAN_STANDBY, false);
    pinMode(PIN_CAN_BOOSTEN, OUTPUT);
    digitalWrite(PIN_CAN_BOOSTEN, true);
    if (!CAN.begin(BAUDRATE)) {
        return false;
    }
    return true;
}

void sendCAN(Pdu* pdu) {
    CAN.beginPacket(pdu->id);
    CAN.write(pdu->data, pdu->length);
    CAN.endPacket();
}

void receiveCAN(Pdu* pdu) {
    CAN.readBytes(pdu->data, pdu->length);
}

void onReceivedDataFromOtherTeam(int packetSize) {
    if (CAN.packetId() != PREVIOUS_TEAM_CAN_ID) {
        return;
    }

    receiveCAN(&previousTeamPdu);
    newDataReceived = true;
}




void setup() {
    Serial.begin(9600);
    if (!beginCAN()) {
        Serial.println("CAN driver initialization failed!");
        while (true) {
            ;
        }
    }
    CAN.onReceive(onReceivedDataFromOtherTeam);
    newDataReceived = false;
    sendEnabled = false;
    nextSendTimestamp = millis();

    // Put your setup code below *******************************************************************
    

    // *********************************************************************************************
}



void loop() {
    if (newDataReceived) {
        // Don't change the next 3 lines
        newDataReceived = false;
        sendEnabled = true;
        nextSendTimestamp = millis() + SEND_DELAY_MS;
        
        // Example code below **********************************************************************
        // Feel free to do whatever you want here

        // Example: Extract previous team data
        int8_t byte0 = previousTeamPdu.data[0];
        int8_t byte1 = previousTeamPdu.data[1];


        // Example: Display previous team data
        Serial.println(byte0);
        Serial.println(byte1);

        // Example: Measure data
        int8_t myData0 = 4;
        int8_t myData1 = 45;


        // Example: Package data
        yourTeamPdu.data[0] = myData0;
        yourTeamPdu.data[1] = myData1;
    }

    // Do whatever you want here





    // Sending CAN frame. Don't change this!
    if (sendEnabled) {
        if (millis() > nextSendTimestamp) {
            sendEnabled = false;
            sendCAN(&yourTeamPdu);
        }
    }
}

```



# Clickboard examples

## Contents
1. [Feather Click Shield](#feather-click-shield)
2. [Adafruit Feather M4 CAN](#adafruit-feather-m4-can)
3. [10x10 RGB CLICK](#10x10-rgb-click)
4. [THUMBSTICK CLICK](#thumbstick-click)
5. [MPU 9DOF CLICK](#mpu-9dof-click)
6. [PROXIMITY 18 CLICK](#proximity-18-click)
7. [THERMO 22 CLICK](#thermo-22-click)
8. [2x2 KEY CLICK](#2x2-key-click)
9. [I2C Scanner](#i2c-scanner)


## Examples

**This section provides useful links, images and code snippets for every component and click board.**


### Feather Click Shield

**Pinout of the feather click shield:**

![grafik](https://www.mikroe.com/img/images/feather-inner-2.png)


### Adafruit Feather M4 CAN 

**Pinout of the adafruit feather m4 can:**

![grafik](https://github.com/VectorInformatik/clickboard-examples/assets/136338757/4107adeb-8cf2-4803-934a-0be1f3d37a52)


### 10x10 RGB CLICK

Product website: https://www.mikroe.com/10x10-rgb-click
Library: Adafruit NeoPixel (by Adafruit)

Code example:

```c++
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 17 // For microBUS 1
// #define PIN 13 // For microBUS 2
#define NUM_PIXELS 100

Adafruit_NeoPixel LEDs(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Start LEDs
  LEDs.begin();

  // Clear all LEDs
  LEDs.clear();

  // Set brightness of all LEDs. [0, 255]
  LEDs.setBrightness(40);
}

void loop() {
  for(int i=0; i<NUM_PIXELS; i++) {
    // Set color of individual LED
    LEDs.setPixelColor(i, LEDs.Color(255-(2*i), 150, i*2));
    // Write to hardware, else nothing would show
    LEDs.show();
    delay(20);
  }
  for(int i=0; i<NUM_PIXELS; i++) {
    // Set color of individual LED
    LEDs.setPixelColor(i, LEDs.Color(0, 0, 0));
    // Write to hardware, else nothing would show
    LEDs.show();
    delay(20);
  }
}
```


### THUMBSTICK CLICK

Product website: https://www.mikroe.com/thumbstick-click
Library: Mcp320x (by Patrick Rogalla)

Code example:

```c++
#include <Arduino.h>
#include <SPI.h>
#include <Mcp320x.h>

#define SPI_CS_PIN 10
#define ADC_VREF 3300
#define ADC_CLK 1600000
#define THUMBSTICK_BUTTON_PIN 11
#define DEBOUNCE_TIME_MS 10

volatile unsigned long lastButtonPress = 0;

MCP3208 adc(ADC_VREF, SPI_CS_PIN);

void onThumbstickPressed()
{
  // Debouncing
  unsigned long now = millis();
  if ((now - lastButtonPress) < DEBOUNCE_TIME_MS) return;

  Serial.println("Pressed thumbstick");
  
  lastButtonPress = now;
}

void setup() {
  pinMode(SPI_CS_PIN, OUTPUT);
  pinMode(THUMBSTICK_BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(THUMBSTICK_BUTTON_PIN), onThumbstickPressed, FALLING);

  digitalWrite(SPI_CS_PIN, HIGH);

  Serial.begin(9600);

  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(settings);
}

void loop() {
  uint16_t vertical = adc.read(MCP3208::Channel::SINGLE_0);
  uint16_t horizontal = adc.read(MCP3208::Channel::SINGLE_1);

  Serial.print("vertical: ");
  Serial.print(vertical);
  Serial.print("  horizontal: ");
  Serial.print(horizontal);
  Serial.println();

  delay(100);
}
```


### MPU 9DOF CLICK

Product website: https://www.mikroe.com/mpu-9dof-click
Library: MPU9250 (by Hideaki Tai)

Code example:

```c++
#include <Arduino.h>
#include "SPI.h"
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


### PROXIMITY 18 CLICK

Product website: https://www.mikroe.com/proximity-18-click
Library:  VCNL3040 (by Andris Jenerts)
IMPORTANT!!! in VCNL3040.h set VCNL3040_DEV_ADDRESS to 0x41

Code example:

```c++
#include <Arduino.h>
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


### THERMO 22 CLICK

Product website: https://www.mikroe.com/thermo-22-click
Library: LM75 (by Jeremy Cole)

Code example:

```c++
#include <Arduino.h>
#include <Temperature_LM75_Derived.h>

Generic_LM75 temperature(0x4F);

void setup() {
    Serial.begin(9600);

    Wire.begin();
}

void loop() {
    Serial.print("Temperature = ");
    Serial.print(temperature.readTemperatureC());
    Serial.println(" C");

    delay(250);
}
```


### 2x2 KEY CLICK

Product website: https://www.mikroe.com/2x2-key-click

Code example:

```c++
#include <Arduino.h>

#define INT_PIN 11
#define BUTTON1_PIN 15
#define BUTTON2_PIN 12
#define BUTTON3_PIN 10
#define BUTTON4_PIN 13

volatile bool buttonPressed = false;
void handleButtonPress();

void setup() {
    pinMode(INT_PIN, INPUT);
    pinMode(BUTTON1_PIN, INPUT);
    pinMode(BUTTON2_PIN, INPUT);
    pinMode(BUTTON3_PIN, INPUT);
    pinMode(BUTTON4_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INT_PIN), handleButtonPress, RISING);
    Serial.begin(9600);
}

void loop() {
    if (buttonPressed) {
        Serial.println("***************************");
        Serial.println(digitalRead(BUTTON1_PIN));
        Serial.println(digitalRead(BUTTON2_PIN));
        Serial.println(digitalRead(BUTTON3_PIN));
        Serial.println(digitalRead(BUTTON4_PIN));
        Serial.println("***************************");
        buttonPressed = false;
    }
}

// Optional Interrupt Service Routine (ISR)
void handleButtonPress() {
    buttonPressed = true;
}
```


### I2C scanner

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