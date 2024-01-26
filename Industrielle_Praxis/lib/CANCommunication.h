#pragma once

#include <inttypes.h>
#include <CANSAME5x.h>

#define CAN_RX_ID 0x0010
#define CAN_TX_ID CAN_RX_ID + 0x0010

#define CAN_MSG_INTERVAL_MILLIS 10

struct coordinate_t {
  uint8_t x;
  uint8_t y;
  uint8_t z;
};

CANSAME5x CAN;
long nextMsgSendMillis = 0;
bool packetWaiting = false;

coordinate_t r_c1 = {0, 0, 0};
coordinate_t r_c2 = {0, 0, 0};
coordinate_t w_c1 = {0, 0, 0};
coordinate_t w_c2 = {0, 0, 0};

bool loopCANCommunication(long currentMillis) {
  if (nextMsgSendMillis && nextMsgSendMillis - currentMillis <= 0) {
    Serial.printf("Sending  coordinates: c1 = [%d, %d, %d], c2 = [%d, %d, %d].\n",
        w_c1.x, w_c1.y, w_c1.z, w_c2.x, w_c2.y, w_c2.z);
    CAN.beginPacket(CAN_TX_ID);
    CAN.write(w_c1.x);
    CAN.write(w_c1.y);
    CAN.write(w_c1.z);
    CAN.write(0);
    CAN.write(w_c2.x);
    CAN.write(w_c2.y);
    CAN.write(w_c2.z);
    CAN.write(0);
    CAN.endPacket();
    nextMsgSendMillis = 0;
    return true;
  }
  return false;
}

void onReceive(int packetSize) {
  // received a packet
  if ((CAN.packetId() & 0x07FF) == CAN_RX_ID) {
    r_c1.x = CAN.read();
    r_c1.y = CAN.read();
    r_c1.z = CAN.read();
    CAN.read();
    r_c2.x = CAN.read();
    r_c2.y = CAN.read();
    r_c2.z = CAN.read();
    CAN.read();
    Serial.printf("Received coordinates: c1 = [%d, %d, %d], c2 = [%d, %d, %d].\n",
        r_c1.x, r_c1.y, r_c1.z, r_c2.x, r_c2.y, r_c2.z);
    nextMsgSendMillis = millis() + CAN_MSG_INTERVAL_MILLIS;
    packetWaiting = true;
  }
}

void setupCANCommunication() {
  Serial.println("CAN Sender");

  pinMode(PIN_CAN_STANDBY, OUTPUT);
  digitalWrite(PIN_CAN_STANDBY, false); // turn off STANDBY
  pinMode(PIN_CAN_BOOSTEN, OUTPUT);
  digitalWrite(PIN_CAN_BOOSTEN, true); // turn on booster

  // start the CAN bus at 250 kbps
  if (!CAN.begin(250000)) {
    Serial.println("Starting CAN failed!");
    while (1) delay(10);
  }
  Serial.println("Starting CAN with 250 kbps!");
  
  // register the receive callback
  CAN.onReceive(onReceive);
}
