#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN D7
#define CLK_PIN  D5
#define CS_PIN   D8

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// ----- FRAME ANIMASI -----
const uint64_t IMAGES[] = {
  0x8e7c3e30f0101000,
  0x077e1f1878081000,
  0x8e7c3e30f0080800,
  0x9c787ce060100800,
  0x9c787ce060101000,
  0x9c787ce060201000
};
const int IMAGES_LEN = sizeof(IMAGES)/8;

// ----- DRAW TANPA FLICKER -----
void drawImageNoFlicker(uint8_t device, uint64_t img) {
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  for (int col = 0; col < 8; col++) {
    uint8_t colData = (img >> (col * 8)) & 0xFF;
    mx.setColumn(device, col, colData);
  }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

// ----- FUNGSI ANIMASI -----
void catJump(uint8_t device, uint16_t frameDelay) {
  for (int i = 0; i < IMAGES_LEN; i++) {
    drawImageNoFlicker(device, IMAGES[i]);
    delay(frameDelay);
  }
}

void setup() {
  mx.begin();
  mx.clear();
  mx.control(MD_MAX72XX::INTENSITY, 10);
}

void loop() {
  catJump(2, 200);
}
