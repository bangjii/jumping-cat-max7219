#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN D7
#define CLK_PIN  D5
#define CS_PIN   D8

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const uint64_t IMAGES[] = {
  0x9c787ce060101000,
  0x8e7c3e30f0101000,
  0x077e1f1878081000,
  0x8e7c3e30f0080800,
  0x9c787ce060100800
};
const int IMAGES_LEN = sizeof(IMAGES)/8;

void drawImageNoFlicker(uint64_t img) {
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);  // matikan refresh sementara

  for (int col = 0; col < 8; col++) {
    uint8_t colData = (img >> (col * 8)) & 0xFF;
    mx.setColumn(0, col, colData);
  }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);   // hidupkan refresh (langsung tampil)
}

void setup() {
  mx.begin();
  mx.clear();
  mx.control(MD_MAX72XX::INTENSITY, 10);
}

void loop() {
  for (int i = 0; i < IMAGES_LEN; i++) {
    drawImageNoFlicker(IMAGES[i]);
    delay(200);
  }
  //delay(3000);
}
