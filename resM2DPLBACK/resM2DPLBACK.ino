#include <SPI.h>
#include <Wire.h>

#include "vars.h"
#include "tft_init.h"


void setup(void) {
  Serial.begin(9600); //ingress data                      
  init_tft();
  cont_act=0;
  clear_screen=0;
}

void loop(void) {
    Serial.println(Serial.available());
    if (Serial.available() > 0) { 
      if (clear_screen==0){
        OLEDA.fillScreen(ST77XX_BLACK); 
        clear_screen=1;
      }
      serial_res();
      drawOLEDA();
      cont_act=0;
    }else if (cont_act==0 and Serial.available() == 0){
      //drawOLEDA();
      w_time();
    }
      delay(500); 
}

void drawOLEDA(void) {

/*CPU SEC*/
  OLEDA.setTextWrap(false);
  OLEDA.setFont(&muMatrix8ptRegular);
  OLEDA.setTextColor(0xff3f); 
  //Icon CPU
    int porcent=CPUstat.toInt();
    if (porcent<=40){setc_CPU=0x17e0; OLEDA.drawBitmap(60,-2,procx24,24,24,setc_CPU);}
    if (porcent>=41 and porcent <=80){setc_CPU=0xa37f; OLEDA.drawBitmap(60,-2,procx24,24,24,setc_CPU);}
    if (porcent>=81){setc_CPU=0xf800; OLEDA.drawBitmap(60,-2,procx24,24,24,setc_CPU);}
  //
  //linea1
    OLEDA.drawLine(1, firstRow-10, 40, firstRow-10, setc_CPU);  
    OLEDA.drawLine(40, firstRow-10, 50, firstRow, setc_CPU);
    OLEDA.drawLine(50, firstRow, 60, firstRow, setc_CPU);
  //
  //CPUStats
    OLEDA.fillRoundRect(5, 3 , 32, 15, 0, 0xc018);
  OLEDA.setCursor(10, firstRow+2); 
  OLEDA.println(CPUstat);               
  //
  //Lineab
    OLEDA.drawLine(85, firstRow, 95, firstRow, setc_CPU); 
    OLEDA.drawLine(95, firstRow, 105, firstRow-10, setc_CPU);
    OLEDA.drawLine(105, firstRow-10, width, firstRow-10, setc_CPU);
  //
  //CPU Cores
    OLEDA.fillRoundRect(108, 3 , (CPUstat.toInt()*52)/100, 15, 0, 0xc018);
  OLEDA.setCursor(110, firstRow+2);      
  OLEDA.println(CPUcores);    
  //
//END CPU

/*RAM SEC*/
  OLEDA.setTextWrap(false);
  OLEDA.setFont(&muMatrix8ptRegular);
  OLEDA.setTextColor(0xff3f); 
  //Icon RAM
    porcent=RAMstat.toInt();
    if (porcent<=40){setc_RAM=0x17e0; OLEDA.drawBitmap(60,22,Ramv2_24,24,24,setc_RAM);}
    if (porcent>=41 and porcent <=80){setc_RAM=0xa37f; OLEDA.drawBitmap(60,22,Ramv2_24,24,24,setc_RAM);}
    if (porcent>=81){setc_RAM=0xf800; OLEDA.drawBitmap(60,22,Ramv2_24,24,24,setc_RAM);}
  //
  //linea1
    OLEDA.drawLine(1, secondRow-10, 40, secondRow-10, setc_RAM);  
    OLEDA.drawLine(40, secondRow-10, 50, secondRow, setc_RAM);
    OLEDA.drawLine(50, secondRow, 60, secondRow, setc_RAM);
  //
  //RAMStats
    OLEDA.fillRoundRect(5, secondRow-8 , 32, 15, 0, 0x9813);
  OLEDA.setCursor(10, secondRow+2); 
  OLEDA.println(RAMstat);               
  //
  //Lineab
    OLEDA.drawLine(85, secondRow, 95, secondRow, setc_RAM); 
    OLEDA.drawLine(95, secondRow, 105, secondRow-10, setc_RAM);
    OLEDA.drawLine(105, secondRow-10, width, secondRow-10, setc_RAM);
  //
  //RAM
    OLEDA.fillRoundRect(108, secondRow-8 , (RAMstat.toInt()*52)/100, 15, 0, 0x9813);
  OLEDA.setCursor(110, secondRow+2);      
  OLEDA.println(RAMtotal);    
  //
//END RAM

/*SSD-HDD SEC*/
  OLEDA.setTextWrap(false);
  OLEDA.setFont(&muMatrix8ptRegular);
  OLEDA.setTextColor(0xff3f); 
  //Icon HDD-SSD
    porcent=SSDspace.toInt();
    if (porcent<=40){setc_HD=0x17e0; OLEDA.drawBitmap(60,50,hdd24,24,24,setc_HD);}
    if (porcent>=41 and porcent <=80){setc_HD=0xa37f; OLEDA.drawBitmap(60,50,hdd24,24,24,setc_HD);}
    if (porcent>=81){setc_HD=0xf800; OLEDA.drawBitmap(60,50,hdd24,24,24,setc_HD);}
    porcent=HDDspace.toInt();
    if (porcent<=40){setc_HD2=0x17e0;}
    if (porcent>=41 and porcent <=80){setc_HD2=0xa37f;}
    if (porcent>=81){setc_HD2=0xf800;}
  //
  //linea1
    OLEDA.drawLine(1, thirdRow-10, 40, thirdRow-10, setc_HD);  
    OLEDA.drawLine(40, thirdRow-10, 50, thirdRow, setc_HD);
    OLEDA.drawLine(50, thirdRow, 60, thirdRow, setc_HD);
  //Lineac
    OLEDA.drawLine(1, thirdRow+25, 40, thirdRow+25, setc_HD2);  
    OLEDA.drawLine(40, thirdRow+25, 50, thirdRow+10, setc_HD2);
    OLEDA.drawLine(50, thirdRow+10, 60, thirdRow+10, setc_HD2);
  //
  //SSD
    OLEDA.fillRoundRect(5, thirdRow-8 , 32, 15, 0, 0x780f);
  OLEDA.setCursor(10, thirdRow+2); 
  OLEDA.println(SSDspace);               
  //
  //Lineab
    OLEDA.drawLine(85, thirdRow, 95, thirdRow, setc_HD); 
    OLEDA.drawLine(95, thirdRow, 105, thirdRow-10, setc_HD);
    OLEDA.drawLine(105, thirdRow-10, width, thirdRow-10, setc_HD);
  // Lineac
    OLEDA.drawLine(85, thirdRow+10, 95, thirdRow+10, setc_HD2); 
    OLEDA.drawLine(95, thirdRow+10, 105, thirdRow+25, setc_HD2);
    OLEDA.drawLine(105, thirdRow+25, width, thirdRow+25, setc_HD2);
  //
  //SSD
    OLEDA.fillRoundRect(108, thirdRow-8 , (SSDspace.toInt()*52)/100, 15, 0, 0x780f);
  OLEDA.setCursor(110, thirdRow+2);      
  OLEDA.println(DD1t);    
  //
  //SSD2
      OLEDA.fillRoundRect(5, thirdRow+8 , 32, 15, 0, 0x580b);
  OLEDA.setCursor(10, thirdRow+18); 
  OLEDA.println(HDDspace);  
      OLEDA.fillRoundRect(108, thirdRow+8 , (HDDspace.toInt()*52)/100, 15, 0, 0x580b);
  OLEDA.setCursor(110, thirdRow+18);      
  OLEDA.println(DD2t);  
  //

/*Other SEC*/
  setc_oth=0xff3f;
  OLEDA.setFont(&Dialog_italic_8);
  OLEDA.setTextColor(setc_oth);
  OLEDA.setCursor(Colinit, Row5); 
  OLEDA.print("OS info: "); 
  OLEDA.setCursor(Colinit, Row5+15); 
  OLEDA.print(osinf); 
  //Logos
    if (osinf.indexOf("mac")!=-1){OLEDA.drawBitmap(55,80,applev232,32,32,0xff3f);}
    if (osinf.indexOf("win")!=-1 or osinf.indexOf("Win")!=-1){OLEDA.drawBitmap(55,80,win323,32,32,0xff3f);}
  //linea1
    OLEDA.drawLine(1, Row5+5, 40, Row5+5, setc_oth);  
    OLEDA.drawLine(40, Row5+5, 50, Row5-5, setc_oth);
    OLEDA.drawLine(50, Row5-5, 60, Row5-5, setc_oth);
    //
  //temperature
  OLEDA.setTextWrap(false);
  OLEDA.setFont(&muMatrix8ptRegular);
  porcent=cputmp.toInt();
    if (porcent<=40){setc_temp=0x17e0; OLEDA.drawBitmap(100,90,temp16,16,16,setc_temp);}
    if (porcent>=41 and porcent <=80){setc_temp=0xa37f; OLEDA.drawBitmap(100,90,temp16,16,16,setc_temp);}
    if (porcent>=81){setc_temp=0xf800; OLEDA.drawBitmap(100,90,temp16,16,16,setc_temp);}
  OLEDA.setTextColor(setc_temp); 
  OLEDA.setCursor(120,102);
  OLEDA.print(cputmp); 

  porcent=cputmp.toInt();
    if (porcent<=40){setc_tmpg=0x17e0; OLEDA.drawBitmap(100,110,temp16,16,16,setc_tmpg);}
    if (porcent>=41 and porcent <=80){setc_tmpg=0xa37f; OLEDA.drawBitmap(100,110,temp16,16,16,setc_tmpg);}
    if (porcent>=81){setc_tmpg=0xf800; OLEDA.drawBitmap(100,110,temp16,16,16,setc_tmpg);}
  OLEDA.setTextColor(setc_tmpg); 
  OLEDA.setCursor(120,122); 
  OLEDA.print(cputmp); 
  //
//END Other
}
void init_tft(){
  OLEDA.initR (INITR_BLACKTAB);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);
  OLEDA.fillScreen(ST77XX_BLACK);
  OLEDA.setRotation(1);
}

void serial_res(){
    serialReceive = Serial.readString(); 
    CPUstat = serialReceive.substring(0, 5);  
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
}
void w_time(){
      cont_act=1;
      clear_screen=0;
      OLEDA.fillScreen(ST77XX_BLACK);
      OLEDA.drawBitmap(50,20,wait64,64,64,0xa37f);
      OLEDA.setFont(&muMatrix8ptRegular);
      OLEDA.setTextColor(0xFC00);  
      OLEDA.setCursor(55, 100);       
      OLEDA.println("En espera");
      OLEDA.setTextColor(0x3546);  
      OLEDA.setCursor(105, 100);       
      OLEDA.println("|||");  
      OLEDA.setTextSize(0);
}
