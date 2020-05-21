#include "include/Max7219.h"
#include "include/String5x7Buffer.h"

#define ARDUINO

#define MATRIX_SIZE 12
#define WAIT 50

Max7219_8x8 *max7219_8x8;
String5x7Buffer *string5x7Buffer;


String5x7Buffer *buildBuffer() {
  String buff = Serial.readString();
  for (size_t i = 0; i < buff.length(); ++i) {
    if (buff[i] == '\n') {
      buff[i] = '\0';
      break;
    }
  }
  
  return new String5x7Buffer(MATRIX_SIZE, buff.c_str());
}

void setup(){
  Serial.begin(9600);
  
  max7219_8x8 = new Max7219_8x8(MATRIX_SIZE, 11, 10, 13);
  max7219_8x8->init();
  max7219_8x8->test();
  
  string5x7Buffer = new String5x7Buffer(MATRIX_SIZE, "Hello LEDMatrix!");
}

void loop(){
  while (string5x7Buffer->distToLeftSet() > 0) {
    max7219_8x8->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(WAIT);
  }
  delay(500);

  while (string5x7Buffer->distToRightSet() > 0) {
    max7219_8x8->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(WAIT);
  }
  delay(500);

  while (string5x7Buffer->distToAfter() > 0) {
    max7219_8x8->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(WAIT);
  }
  delay(500);
  
  string5x7Buffer->reset();
//  string5x7Buffer->fill(false);

  if (Serial.available()) {
      delete string5x7Buffer;
      string5x7Buffer = NULL;
      string5x7Buffer = buildBuffer();
  }
}
