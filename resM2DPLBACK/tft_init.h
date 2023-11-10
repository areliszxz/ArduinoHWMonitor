#include <Adafruit_ST7735.h> 
#include <Adafruit_GFX.h>

#include "Fonts/muMatrix8ptRegular.h"
#include "Fonts/Dialog_italic_8.h"

#include "iot_iconset_16x16.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 160  // OLED display height, in pixels
#define sclk D5
#define mosi D7
#define cs D2
#define dc D1
#define rst D8 
#define TFT_BACKLIGHT D3 

Adafruit_ST7735 OLEDA = Adafruit_ST7735 (cs, dc, rst);
#define OLED_RESET -1 

const short width = 160;  