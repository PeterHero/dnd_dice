#include "helper.h"

// Button class
Button::Button(int pin) : pin(pin) {
	wasPressed = false;
	active = false;
  released = false;
}

void Button::setup(){
	pinMode(pin, INPUT);
}

void Button::update(){
	bool input = !digitalRead(pin);
	
	active = input && !wasPressed;
  released = !input && wasPressed;
	wasPressed = input;
}

bool Button::isActive(){
	return active;
}

bool Button::wasReleased(){
  return released;
}

// Timer class
Timer::Timer(int period) : period(period) {}

void Timer::setPeriod(int period){
  Timer::period = period;
}

void Timer::update(){
	currentTime = millis();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	timer += deltaTime;
}

void Timer::update(int deltaTime){
	timer += deltaTime;
}

bool Timer::isUp(){
	return timer >= (unsigned long) period;
}

void Timer::reset(){
	timer = 0;
}

unsigned long Timer::getTime(){
  return timer;
}

// Random class
void Random::setSeed(int seed){
  randomSeed(seed);
}

int Random::getRandom(int max){
  return random(max);
}

int Random::getRandom(int min, int max){
  return random(min, max);
}

// Music class
Music::Music(int pin) : pin(pin) {}

void Music::failMelody(){
  int toneLength = 15;
  for (int i = 0; i < toneLength; i++){
    pinMode(pin, OUTPUT);
    delay(3);
    pinMode(pin, INPUT);
    delay(6);
  }

  int pause = 200;
  delay(pause);

  toneLength = 15;
  for (int i = 0; i < toneLength; i++){
    pinMode(pin, OUTPUT);
    delay(3);
    pinMode(pin, INPUT);
    delay(7);
  }

  pause = 200;
  delay(pause);

  toneLength = 50;
  for (int i = 0; i < toneLength; i++){
    pinMode(pin, OUTPUT);
    delay(3);
    pinMode(pin, INPUT);
    delay(8);
  }
}

void Music::successMelody(){
  int toneLength = 50;
  for (int i = 0; i < toneLength; i++){
    pinMode(pin, OUTPUT);
    delay(3);
    pinMode(pin, INPUT);
    if (i % 1 == 0)
      delay(1);
  }

  toneLength = 100;
  for (int i = 0; i < toneLength; i++){
    pinMode(pin, OUTPUT);
    delay(1);
    pinMode(pin, INPUT);
    if (i % 2 == 0)
      delay(1);
  }

  toneLength = 100;
  for (int i = 0; i < toneLength; i++){
    pinMode(pin, OUTPUT);
    delay(1);
    pinMode(pin, INPUT);
    delay(1);
  }
}
