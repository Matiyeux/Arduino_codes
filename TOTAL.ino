#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#include <SoftwareSerial.h>
#define startFrame 0x02
#define endFrame 0x03
SoftwareSerial* cptSerial;

#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 53; // Pin 10 on Arduino Uno

int i=0;

Adafruit_SSD1306 display(OLED_RESET);
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

/*Branchements :
 * Ecran OLED : A5 : SCL ; A4 : SDA ; VCC = 3,3 V
 * 
 * 
 */


void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32);
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("ECRAN OLED OK !");
  display.display();
  delay(1000);
  display.clearDisplay();

  cptSerial = new SoftwareSerial(8, 9);
  cptSerial->begin(1200);

  pinMode(pinCS, OUTPUT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  if (SD.begin())
  {
    display.println("SD card is ready to use.");
  } else
  {
    display.println("SD card initialization failed");
    return;
  }
  
}


void loop() {
  char charIn = 0;
  String HCHC = "";
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
  HCHC=test.substring(56,65);
  i++;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(HCHC);
  display.setCursor(0,20);
  display.println(i);
  display.display();
  delay(1000);
}
