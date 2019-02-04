/*
Usage :
  + This is a simple Teleinfo Test program
  + It's just to test the TeleInfo board and its connexion to the EDF counter
  + It just displays the received teleInfo data on the Serial Monitor
  + No Internet connexion, no data transfered

Hardware needed :
  + 1 x Arduino UNO r3
  + 1 x Ethernet shield (used in the final project)
  + 1 x Opto Coupler : SFH620A
  + 1 x LED
  + 1 x 1 kΩ resistor
  + 1 x 4,7 kΩ resistor
  
PIN USED :
  PIN 8  : Software Serial RX
  PIN 10 : ETH, SS
  PIN 11 : ETH, SPI bus MOSI
  PIN 12 : ETH, SPI bus MISO
  PIN 13 : ETH, SPI bus SCK
  
Sample data displayed on the Serial Monitor :
                (this is a Tempo contract)
    ADCO 081524142549 :
    OPTARIF BBR( S
    ISOUSC 45 ?
    BBRHCJB 000512828 7
    BBRHPJB 000586895 S
    BBRHCJW 000130504 ?
    BBRHPJW 000125314 O
    BBRHCJR 000018132 <
    BBRHPJR 000042111 C
    PTEC HPJW %
    DEMAIN ---- "
    IINST 002 Y
    IMAX 042 E
    PAPP 00570 -
    HHPHC Y D
    MOTDETAT 000000 B
*/
#include <SoftwareSerial.h>
#define startFrame 0x02
#define endFrame 0x03

SoftwareSerial* cptSerial;
String test;

void setup()
{
  Serial.begin(115200);
  cptSerial = new SoftwareSerial(8, 9);
  cptSerial->begin(1200);
  Serial.println(F("setup complete"));
}

void loop()
{
  char charIn = 0;
  test = "#";
  while (charIn != startFrame)
  {
    charIn = cptSerial->read() & 0x7F;
  }
  while (charIn != endFrame)
  {
    if (cptSerial->available())
    {
      charIn = cptSerial->read()& 0x7F;
      //Serial.print(charIn);
      test.concat(charIn);
    }
  }
  Serial.println("");
  //Serial.print(test);
  Serial.print("La valeur de ISOUSC est de : "+test.substring(test.indexOf("ISOUSC")+7,test.indexOf(" ?"))+"\n");
  Serial.print("La valeur de HCHC est de : "+test.substring(test.indexOf("HCHC")+5,test.indexOf("HCHP")-2)+"\n");
  Serial.print("La valeur de HCHP est de : "+test.substring(test.indexOf("HCHP")+5,test.indexOf("PTEC")-4)+"\n");
  test="#";
}
