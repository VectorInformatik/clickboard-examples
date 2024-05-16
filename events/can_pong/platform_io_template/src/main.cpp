#include <CANSAME5x.h>
#include <Arduino.h>

#define PLAYER_1

#define CANID_SERVER 0x01

#ifdef PLAYER_1
    #define CANID_PLAYER 0x02
#else
    #define CANID_PLAYER 0x03
#endif

CANSAME5x CANDriver;


bool setupCan(long baudRate)
{
    pinMode(PIN_CAN_STANDBY, OUTPUT);
    digitalWrite(PIN_CAN_STANDBY, false);
    pinMode(PIN_CAN_BOOSTEN, OUTPUT);
    digitalWrite(PIN_CAN_BOOSTEN, true);
    bool success = true;
    if (!CANDriver.begin(baudRate)) {
        success = false;
    }
    return success;
}

uint8_t data[3];
uint8_t ballPositionX = 0;
uint8_t ballPositionY = 0;
uint8_t gameState = 0;


void onReceive(int packetSize)
{
    if (CANDriver.packetId() != CANID_SERVER) return;

    // Read CANDriver frame
    CANDriver.readBytes(data, packetSize);

    // Extract data
    ballPositionX = data[0];
    ballPositionY = data[1];
    gameState = data[2];

    Serial.printf("Received message: ballX: %d, ballY: %d, gameState: %d\n", ballPositionX, ballPositionY, gameState);

    //****************************
    // Your algorithm goes in here


    // Your algorithm should compute this
    int8_t myComputedPaddleUpdate = -1;

    // Send update of paddle
    if (myComputedPaddleUpdate != 0) { // Avoid sending update of 0 because it does nothing
        CANDriver.beginPacket(CANID_PLAYER);
        CANDriver.write(myComputedPaddleUpdate);
        CANDriver.endPacket();
    }



    //****************************
}

void setup() {
    // Start serial communication
    Serial.begin(9600);

    // Start CANDriver
    if (!setupCan(250000)) {
        Serial.println("CANDriver setup failed!");
        while (true) delay(10);
    }

    // Register receive callback
    CANDriver.onReceive(onReceive);

    Serial.println("Setup done!");
}

void loop() {
    
}