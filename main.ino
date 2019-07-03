#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>

#define PIN 9
#define DIGITS 6

#define S1_START 0

#define S2_START 7

#define P1_START 14

#define S3_START 16

#define S4_START 23

#define P2_START 30

#define S5_START 32

#define S6_START 39


Adafruit_NeoPixel strip = Adafruit_NeoPixel( 7 * DIGITS + 4, PIN, NEO_GRB + NEO_KHZ800);

byte segments[10] = {
  0b1110111, //0
  0b0010001, //1
  0b1101011, //2
  0b0111011, //3
  0b0011101, //4
  0b0111110, //5
  0b1111110, //6
  0b0010011, //7
  0b1111111, //8
  0b0111111, //9
};



void setup() {
  strip.begin();
  setSyncProvider(RTC.get);

  colorWipe(strip.Color(255, 0, 0), 50);
  colorWipe(strip.Color(0, 255, 0), 50);
  colorWipe(strip.Color(0, 0, 255), 50);

  rainbowCycle(2);
}

void loop() {
  clearDisplay();


  printSeconds();
  printMinute();
  printHour();

  strip.show();

  dotOn();
  delay(500);
  dotOff();
  delay(500);

}


void writeDigit(int segStart, int value) {
  byte seg = segments[value];
  for (int i = 6; i >= 0; i--) {
    int offset = segStart + i;
    uint32_t color = seg & 0x01 != 0 ? strip.Color(200, 0, 0) : strip.Color(0, 30, 30);
    strip.setPixelColor(offset , color);
    seg = seg >> 1;
  }
}

void clearDisplay() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}
void dotOn()
{
  strip.setPixelColor(14, strip.Color(0, 255, 0));
  strip.setPixelColor(15, strip.Color(0, 255, 0));
  strip.setPixelColor(30, strip.Color(0, 255, 0));
  strip.setPixelColor(31, strip.Color(0, 255, 0));
  strip.show();

}

void dotOff()
{

  strip.setPixelColor(14, strip.Color(0, 0, 0));
  strip.setPixelColor(15, strip.Color(0, 0, 0));
  strip.setPixelColor(30, strip.Color(0, 0, 0));
  strip.setPixelColor(31, strip.Color(0, 0, 0));
  strip.show();
}


void printSeconds()
{
  int secondT = second();
  int  secondTF = secondT / 10 ;
  writeDigit(S5_START, secondTF);
  int secondTS = secondT % 10;
  writeDigit(S6_START, secondTS);

}

void printMinute()
{
  int minuteT = minute();
  int  minuteTF = minuteT / 10 ;
  writeDigit(S3_START, minuteTF);
  int minuteTS = minuteT % 10;
  writeDigit(S4_START, minuteTS);

}

void printHour()
{
  int hourT = hourFormat12();
  int  hourTF = hourT / 10 ;
  writeDigit(S1_START, hourTF);
  int hourTS = hourT % 10;
  writeDigit(S2_START, hourTS);

}


void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
