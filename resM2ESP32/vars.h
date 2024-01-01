
const short firstRow = 12;  //some constants that define where the rows will be
const short secondRow = 35;
const short thirdRow = 57;
const short fourthRow = 57;
const short Row5 = 100;
const short Row6 = 87;
const short Row7 = 99;
const short Row8 = 110;
const short Colinit = 1;
const float comp_therm=2.00;
const float BETA = 3950;

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
float cputmp;
float gputmp;

int cont_act,cont_ser,clear_screen,line_draw,diagnl;

int16_t setc_CPU,setc_RAM,setc_HD, setc_HD2,setc_oth,setc_temp,setc_tmpg;