#include "display.h"

void Display::setup(){
	pinMode(data_pin, OUTPUT);
	pinMode(clock_pin, OUTPUT);
	pinMode(latch_pin, OUTPUT);	
}

void Display::clear(){
  shiftOut(data_pin, clock_pin, MSBFIRST, EMPTY_GLYPH);
	shiftOut(data_pin, clock_pin, MSBFIRST, digit_muxpos[0]);
  digitalWrite(latch_pin, LOW);
  digitalWrite(latch_pin, HIGH);
}

void Display::setValue(){
  mode = generating;
  currentDigit = 0;
  timer->reset();
}

void Display::setValue(int number){
  mode = normal;
  savedNumber1 = number;
}

void Display::setValue(int first, int second){
  mode = configuration;
  savedNumber1 = first;
  savedNumber2 = second;
}

void Display::display(){
  switch (mode){
    case normal:
      if (savedNumber1 >= pow(10, currentDigit)){
		    int numberToDisplay = (int)(savedNumber1 / pow(10, currentDigit)) % 10;
		    displayDigit(numberToDisplay, numberOfDigits - currentDigit - 1);
	    }
	    currentDigit = (currentDigit + 1) % numberOfDigits;
      break;
    
    case configuration:
      digitsForDice = min(maxDigitsForDice, log10(savedNumber2) + 1);

      if (currentDigit < digitsForDice){
        int numberToDisplay = (int)(savedNumber2 / pow(10, currentDigit)) % 10;
		    displayDigit(numberToDisplay, numberOfDigits - currentDigit - 1);
      }
      else if (currentDigit == digitsForDice){
        displayD(numberOfDigits - currentDigit - 1);
      }
      else if (currentDigit == digitsForDice + 1) {
        displayDigit(savedNumber1, numberOfDigits - currentDigit - 1);
      }
      
      currentDigit = (currentDigit + 1) % numberOfDigits;
      break;

    case generating:
      timer->update();
      if (timer->isUp()){
        currentDigit = (currentDigit + 1) % numberOfDigits;
        timer->reset();
      }
      displayDigit(generatingDigit, numberOfDigits - currentDigit - 1);
      break;
  }
}

void Display::displayD(int position){
  shiftOut(data_pin, clock_pin, MSBFIRST, LETTER_D);
	shiftOut(data_pin, clock_pin, MSBFIRST, digit_muxpos[position]);
  digitalWrite(latch_pin, LOW);
  digitalWrite(latch_pin, HIGH);
}

void Display::displayDigit(int digit, int position){
	shiftOut(data_pin, clock_pin, MSBFIRST, digits[digit]);
	shiftOut(data_pin, clock_pin, MSBFIRST, digit_muxpos[position]);
  digitalWrite(latch_pin, LOW);
  digitalWrite(latch_pin, HIGH);
}
