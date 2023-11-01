#include "dice.h"

constexpr int diceTypes[] = {4, 6, 8, 10, 12, 20, 100};
constexpr int numOfDiceTypes = sizeof(diceTypes)/sizeof(diceTypes[0]);

void Dice::update(){
  timer->update();
}

void Dice::startGenerating(){
  generating = true;
  timer->reset();
}

int Dice::generatedNumber(){
  generating = false;
  rnd->setSeed(timer->getTime());
  int sum = 0;
  for (int i = 0; i < throws; i++)
    sum += rnd->getRandom(1, diceTypes[diceType] + 1);

  return sum;
}

int Dice::getThrows(){
  return throws;
}

int Dice::getDiceType(){
  return diceTypes[diceType];
}

void Dice::increaseNumOfThrows(){
  if (generating)
    return;

  throws++;
  if (throws > maxThrows)
    throws = 1;
}

void Dice::changeDiceType(){
  if (generating)
    return;

  diceType = (diceType + 1) % numOfDiceTypes;
}