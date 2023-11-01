#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>
#include <funshield.h>

class Button;
class Timer;
class Random;
class Music;

class Button {
public:
	Button(int pin);
	void setup();
	void update();
	bool isActive();
  bool wasReleased();
private:
	int pin;
	bool wasPressed;
	bool active;
	bool released;
};

class Timer{
public:
	Timer(int period); // zmenit pokud neni treba period
	void setPeriod(int period);
	void update();
	void update(int deltaTime);
	bool isUp();
	void reset();
	unsigned long getTime();

private:
	int period;
	unsigned long timer = 0;
	unsigned long currentTime;
	unsigned long lastTime = millis();;
	unsigned long deltaTime;
};

class Random{
public:
	void setSeed(int seed);
	int getRandom(int max);
	int getRandom(int min, int max);
};

class Music{
public:
  Music(int pin);
  void failMelody();
  void successMelody();
private:
  Timer *longTimer = new Timer(0);
  Timer *shortTimer = new Timer(0);
  int pin;
};

#endif