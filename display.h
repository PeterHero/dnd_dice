#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <funshield.h>
#include "helper.h"

class Display;

class Display{
public:
	void setup();
	void display();
  void clear();
  void setValue();
  void setValue(int number);
  void setValue(int first, int second);
private:
  static constexpr int period = 100;
  Timer *timer = new Timer(period);
  static constexpr int generatingDigit = 8;

	int currentDigit = 0;
	static constexpr int numberOfDigits = 4;
	static constexpr int dotNumber = - 0x80;
  static constexpr byte LETTER_D = 0b10100001;
  static constexpr byte EMPTY_GLYPH = 0b11111111;
  int savedNumber1 = 0;
  int savedNumber2;

  static constexpr int normal = 0;
  static constexpr int configuration = 1;
  static constexpr int generating = 2;
  int mode = normal;

  static constexpr int throwsAndD = 2;
  static constexpr int maxDigitsForDice = numberOfDigits - throwsAndD;
  int digitsForDice;

  void displayD(int position);
	void displayDigit(int digit, int position);
};

#endif