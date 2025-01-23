// *************************************************************************************************
// Template for TEAM 1. Only change code in the marked sections!
// *************************************************************************************************


#include <Arduino.h>
#include "CANSAME5x.h"

// Uncomment your team here ************************************************************************
#define TEAM_1
// #define TEAM_2
// #define TEAM_3
// #define TEAM_4
// #define TEAM_5
// *************************************************************************************************

#define BAUDRATE 500000

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


CANSAME5x CAN;

struct Pdu {
    int const id;
    uint8_t* data;
    int const length;

    Pdu(int _id, int _length) : id(_id), length(_length) {
        data = new uint8_t[length];
    };
};

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

volatile bool newDataReceived = false;


// Put your imports/defines here *******************************************************************

// *************************************************************************************************



// Communicate with other teams to set these defines ***********************************************
// Important: the values must be in the range (1, 8)

#define YOUR_TEAM_CAN_FRAME_BYTE_COUNT 8
#define PREVIOUS_TEAM_CAN_FRAME_BYTE_COUNT 8

// *************************************************************************************************



Pdu previousTeamPdu(PREVIOUS_TEAM_CAN_ID, PREVIOUS_TEAM_CAN_FRAME_BYTE_COUNT);
Pdu yourTeamPdu(YOUR_TEAM_CAN_ID, YOUR_TEAM_CAN_FRAME_BYTE_COUNT);
void onReceivedDataFromOtherTeam(int packetSize);



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
    // Put your setup code below *******************************************************************
    

    // *********************************************************************************************
}



void loop() {
    if (newDataReceived) {    
        newDataReceived = false;
        // Your code goes below ************************************************************************

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


        // *********************************************************************************************

        delay(10);
        sendCAN(&yourTeamPdu);
    }
}



void onReceivedDataFromOtherTeam(int packetSize) {
    if (CAN.packetId() != PREVIOUS_TEAM_CAN_ID) {
        return;
    }

    receiveCAN(&previousTeamPdu);
    newDataReceived = true;
}
