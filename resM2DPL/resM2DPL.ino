#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ST7735.h> // hardware-specific library
#include <Adafruit_GFX.h>
#include "Fonts/muMatrix8ptRegular.h"
#include "Fonts/Dialog_italic_8.h"

#include "back.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 160  // OLED display height, in pixels

#define sclk D5
#define mosi D7
#define cs D2
#define dc D1
#define rst D8 
#define TFT_BACKLIGHT D3 // Display backlight pin

// Option 1: use any pins but a little slower
Adafruit_ST7735 OLEDA = Adafruit_ST7735 (cs, dc, rst);

#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 OLEDA(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//Adafruit_SSD1306 OLEDA(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
long int rewrite = 0;       //this will hold our last rewritten time from millis() function
const short firstRow = 12;  //some constants that define where the rows will be
const short secondRow = 27;
const short thirdRow = 42;
const short fourthRow = 57;
const short Row5 = 72;
const short Row6 = 87;
const short Row7 = 99;
const short Row8 = 110;
const short Colinit = 1;

const short width = 160;  //also constant variable containing width of the screen, if you are using different display type you will have to tinker with those values
String btPass = "2222";
String serialReceive;  //some Strings, that will contain values got from Serial buffer. First one will contain the entire data string, others will contain only substrings that belongs to them
String CPUstat;
String RAMstat;
String HDDspace;
String SSDspace;
String CPUcores;
String RAMtotal;
String DD1t;
String DD2t;
String osinf;
String cputmp;

void setup(void) {
  //OLEDA.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Default OLED address, usually
  //OLEDA.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // Default OLED address, usually
   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  Serial.begin(9600);                       //open serial interface with baud of 9600 (have to be the same as in python script)
  OLEDA.initR (INITR_144GREENTAB); // initialize a ST7735S chip, black tab
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on
  OLEDA.fillScreen(0x0000);
  OLEDA.setRotation(1);
}
void loop(void) {
  
    if (Serial.available() > 0) {           //if any data is available in serial buffer
    serialReceive = Serial.readString();  //read it as string and put into serialReceive variable
    CPUstat = serialReceive.substring(0, 5);  //split the long ass received string to substrings. Values i used are those that i defined (5 characters/information) if not stated else
    CPUstat.replace("|"," ");
    RAMstat = serialReceive.substring(5, 10);
    RAMstat.replace("|"," ");
    HDDspace = serialReceive.substring(10, 15);
    HDDspace.replace("|"," ");
    SSDspace = serialReceive.substring(15, 20);
    SSDspace.replace("|"," ");
    CPUcores = serialReceive.substring(20, 25);
    CPUcores.replace("|"," ");
    RAMtotal = serialReceive.substring(25, 30);
    RAMtotal.replace("|"," ");
    DD1t = serialReceive.substring(30, 36);
    DD1t.replace("|"," ");
    DD2t = serialReceive.substring(36, 42);
    DD2t.replace("|"," ");  
    osinf = serialReceive.substring(42, 52);
    cputmp = serialReceive.substring(52, 56);
    }else{
    CPUstat="";RAMstat="";HDDspace="";SSDspace="";CPUcores="";RAMtotal="";DD1t="";DD2t="";osinf="";cputmp="";
    OLEDA.setFont(&muMatrix8ptRegular);
    OLEDA.setTextColor(0xFC00);  // Draw white text
    OLEDA.setCursor(80, 90);       //set printing position to edge of screen, first row
    OLEDA.println("En espera..."); 
    delay(1000);
    OLEDA.fillScreen(ST77XX_BLACK);
    OLEDA.setTextSize(0);
    }
  drawOLEDA();  //our function that draws OLEDA display
  delay(500);  //wait for 10ms, as OLEDA needs some time to get refreshed

}

void drawOLEDA(void) {
  backg();
  OLEDA.setTextWrap(false);
  OLEDA.setFont(&muMatrix8ptRegular);
  //OLEDA.setTextSize(2);
  OLEDA.setTextColor(0xff3f);  // Draw white text
  OLEDA.setCursor(Colinit, firstRow);       //set printing position to edge of screen, first row
    OLEDA.fillRoundRect(30, 2 , 30, 11, 0, 0xc018);
  OLEDA.println("CPU1:");               //print legend text
  OLEDA.setCursor(35, firstRow);      //set printing position to a bit further
  OLEDA.println(CPUstat);               //print the value received and split from the Serial
  OLEDA.setCursor(70, firstRow);      //set printing position to a bit further
  OLEDA.println(" %");                  //print percent sign
    OLEDA.fillRoundRect(85, 2 , (CPUstat.toInt()*80)/100, 11, 0, 0x05e0);
  OLEDA.setCursor(90, firstRow);      //set printing position to a bit further
  OLEDA.println(CPUcores);              //print additional information

  OLEDA.drawLine(0, firstRow + 2, width, firstRow + 2, 0x05a0);  //draw vertical line between each row, so it´s more clear to read

  OLEDA.setTextColor(0xff3f);  // Draw white text
  OLEDA.setCursor(Colinit, secondRow);  //and basically the same for everything repeats..
    OLEDA.fillRoundRect(30, 17, 30, 11, 0, 0x9813);
  OLEDA.print("RAM:");
  OLEDA.setCursor(35, secondRow);
  OLEDA.print(RAMstat);
  OLEDA.setCursor(70, secondRow);
  OLEDA.print(" %");
    OLEDA.fillRoundRect(85, 17, (RAMstat.toInt()*80)/100, 11, 0, 0x04e0);
  OLEDA.setCursor(90, secondRow);
  OLEDA.setTextColor(0xfc40);
  OLEDA.print(RAMtotal);

  OLEDA.drawLine(0, secondRow + 2, width, secondRow + 2, 0x05a0);
    OLEDA.fillRoundRect(30, 32, 30, 11, 0, 0x780f);
  OLEDA.setTextColor(0xff3f);  // Draw white text
  OLEDA.setCursor(Colinit, thirdRow);
  OLEDA.print("DD1:");
  OLEDA.setCursor(35, thirdRow);
  OLEDA.print(SSDspace);
  OLEDA.setCursor(70, thirdRow);
  OLEDA.print(" %");
  OLEDA.setCursor(90, thirdRow);
  OLEDA.setTextColor(0xfc40);
    OLEDA.fillRoundRect(85, 32, (SSDspace.toInt()*80)/100, 11, 0, 0x0400);
  OLEDA.print(DD1t);

  OLEDA.drawLine(0, thirdRow + 2, width, thirdRow + 2, 0x05a0);

  OLEDA.setTextColor(0xff3f);  // Draw white text
      OLEDA.fillRoundRect(30, 47, 30, 11, 0, 0x580b);
  OLEDA.setCursor(Colinit, fourthRow);
  OLEDA.print("DD2:");
  OLEDA.setCursor(35, fourthRow);
  OLEDA.print(HDDspace);
  OLEDA.setCursor(70, fourthRow);
  OLEDA.print(" %");
  OLEDA.setCursor(90, fourthRow);
  OLEDA.setTextColor(0xfc40);
      OLEDA.fillRoundRect(85, 47, (HDDspace.toInt()*80)/100, 11, 0, 0x0300);
  OLEDA.print(DD2t);
  OLEDA.drawLine(0, fourthRow + 2, width, fourthRow + 2, 0x05a0);

  OLEDA.setFont(&Dialog_italic_8);
  OLEDA.setTextColor(0xc819);  // Draw white text
  OLEDA.drawLine(0, Row5 + 2, width, Row5 + 2, 0x0380);  //draw vertical line between each row, so it´s more clear to read
  OLEDA.setCursor(Colinit, Row5);       //set printing position to edge of screen, first row
  OLEDA.print("OS Ver: "+ osinf);               //print legend text
  OLEDA.setFont(&muMatrix8ptRegular);
  OLEDA.setTextColor(0x9af3);  // Draw white text
  OLEDA.setCursor(Colinit, Row6);      //set printing position to a bit further
  OLEDA.print("HDD's: ");               //print the value received and split from the Serial
  OLEDA.setCursor(40, Row6);  
  OLEDA.print(DD1t);
  OLEDA.print(" , ");
  OLEDA.setCursor(85, Row6);  
  OLEDA.print(DD2t);
  OLEDA.setCursor(Colinit, Row7);      //set printing position to a bit further
  OLEDA.print("RAM: ");                  //print percent sign
  OLEDA.setCursor(35, Row7);  
  OLEDA.print(RAMtotal);
  OLEDA.setCursor(Colinit, Row8);      //set printing position to a bit further
  OLEDA.print("Cores: ");              //print additional information
  OLEDA.setCursor(35, Row8); 
  OLEDA.print(CPUcores);              //print additional information
  OLEDA.setCursor(55, Row8); 
  OLEDA.print("  Temp: "+cputmp); 
  OLEDA.drawLine(0, Row8 + 2, width, Row8 + 2, 0x0380);
 }

void backg(){
  int h = 128,w = 128, row, col, buffidx=0;
  for (row=0; row<h; row++) { // For each scanline...
    for (col=0; col<w; col++) { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      OLEDA.drawPixel(col, row, pgm_read_word(back + buffidx));
      buffidx++;
    } // end pixel
  }
}