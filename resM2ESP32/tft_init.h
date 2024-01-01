#include <Adafruit_ST7735.h> 
#include <Adafruit_GFX.h>

#include "Fonts/muMatrix8ptRegular.h"
#include "Fonts/Dialog_italic_8.h"

#include "iot_iconset_16x16.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 160  // OLED display height, in pixels
#define sclk 21 //D5
#define mosi 19 //D7
#define cs 22 //D2 
#define dc 23 //D1
#define rst 18 //D8 
#define TFT_BACKLIGHT 5 //D3 

Adafruit_ST7735 OLEDA = Adafruit_ST7735 (cs, dc, mosi, sclk, rst);
#define OLED_RESET -1 

const short width = 160;  