/*
#include <U8g2lib.h>


U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(
  U8G2_R0,
  47,   // CS
  48,   // DC
  49    // RESET
);

int i = 0;

unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 100; 

int y_speed = 60;

const char* str = "0";
char buf[8];

void setup() {
  u8g2.begin();
  u8g2.clearBuffer();
  Serial.begin(9600);
}





void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // <-- this was missing

    itoa(i, buf, 10);

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso32_tn);
    int w1 = u8g2.getStrWidth(buf);
    int x_speed = (128 - w1) / 2;
    u8g2.drawStr(x_speed, 50, buf);

    u8g2.setFont(u8g2_font_6x12_tr);        // ← changer la font D'ABORD
    int w2 = u8g2.getStrWidth("KM/H");      // ← mesurer APRÈS
    int x_text = (128 - w2) / 2;
    u8g2.drawStr(x_text, 60, "KM/H");
    u8g2.sendBuffer();

    i++;
    if (i > 119) i = 0;
  }
}

*/