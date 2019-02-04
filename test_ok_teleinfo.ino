#include <SoftwareSerial.h>
#define startFrame 0x02
#define endFrame 0x03
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
SoftwareSerial* cptSerial;
String test;
String HCHC="";
String HCHP;
int i=0;
long iHCHC=0;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  Serial.begin(115200);
  cptSerial = new SoftwareSerial(8, 9);
  cptSerial->begin(1200);
  Serial.println(F("setup complete"));

  display.display();
  delay(500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("C'est parti pour le TIC");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop()
{
  char charIn = 0;
  String HCHC = "";
  String HCHP = "";
  String test = "";
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
//  //Serial.println("");
//  //Serial.print(test);
//  //Serial.print("La valeur de ISOUSC est de : "+test.substring(test.indexOf("ISOUSC")+7,test.indexOf(" ?"))+"\n");
//  HCHC=test.substring(10,20);
//Serial.print(test.substring(test.indexOf("HCHP")+5,test.indexOf("PTEC")-4+"\n\n"));
Serial.print(test+"\n\n");
HCHC=test.substring(56,65);
Serial.print(HCHC+"\n\n");
HCHC.replace("0","1");
iHCHC=atof(HCHC,c_str())
Serial.print(iHCHC+"\n");
//  Serial.print("La valeur de HCHC est de : "+HCHC+"\n");
//  //Serial.print("La valeur de HCHP est de : "+HCHP+"\n");

//
//  i++;
//  display.clearDisplay();
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  display.println(HCHC);
//  display.setCursor(0,20);
//  display.println(i);
//  display.display();
//  delay(1000);
//  test.remove(0); 
//  HCHC.remove(0);
//  HCHP.remove(0);
}
