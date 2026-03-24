#include <U8g2lib.h>

 //SW SPI: (rotation, clock, data, cs, dc, reset)
U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(
  U8G2_R0,
  13,   //clock
  11,   //data 
  10,   //cs
  9,   //dc
  8   //reset
); 

