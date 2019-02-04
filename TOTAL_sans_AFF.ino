#include <SoftwareSerial.h>
#define startFrame 0x02
#define endFrame 0x03
SoftwareSerial* cptSerial;

#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 53; // Pin 10 on Arduino Uno

int i=0;

void setup()
{
  cptSerial = new SoftwareSerial(8, 9);
  cptSerial->begin(9600);
  pinMode(3, OUTPUT);

//  if (SD.begin())
//  {
//    digitalWrite(3,HIGH);
//  } else
//  {
//    digitalWrite(3,LOW);
//    return;
//  }
  
}


void loop() {
  char charIn = 0;
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
   myFile = SD.open("test_serena.txt", FILE_WRITE);
   if (myFile) {
    myFile.println(test);
    myFile.close(); // close the file
    digitalWrite(3,LOW);
    delay(500);
    digitalWrite(3,HIGH);
   }
  i++;
}
