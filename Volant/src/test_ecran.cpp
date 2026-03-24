/*
#include <U8g2lib.h>

 //SW SPI: (rotation, clock, data, cs, dc, reset)
U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(
  U8G2_R0,
  51,   //clock
  52,   //data 
  255,   //cs
  11,   //dc
  10   //reset
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
    int w = u8g2.getStrWidth(buf);
    int x_speed = (128 - w) / 2;

    int x_right = x_speed + w;
    int x_unit = x_right + 5;

 
    u8g2.drawStr(x_speed, 60, buf);

    
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(x_unit, 50, "KM/H");
    
    u8g2.sendBuffer();

    i++;
    if (i > 119) i = 0;
  }
}

*/