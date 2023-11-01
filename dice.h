#ifndef DICE_H
#define DICE_H

#include <Arduino.h>
#include <funshield.h>
#include "helper.h"

class Dice;

class Dice{
public:
    void update();
    void startGenerating();
    int  generatedNumber();
    int  getThrows();
    int  getDiceType();
    void increaseNumOfThrows();
    void changeDiceType();
private:
    Timer* timer = new Timer(0); // zmenit pokud neni potreba period
    Random* rnd = new Random();
    static constexpr int maxThrows = 9;
    int throws = 1;
    int diceType = 0;
    bool generating = false;
};

#endif