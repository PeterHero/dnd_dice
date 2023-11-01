#include "dice.h"
#include "display.h"
#include "helper.h"
#include <funshield.h>

Button *buttons[] = {new Button(button1_pin), new Button(button2_pin), new Button(button3_pin)};
constexpr int buttonsCount = sizeof(buttons)/sizeof(buttons[0]);

Dice *dndDice = new Dice();
Display *display = new Display();
Music *music = new Music(beep_pin);

void setup() {
  for (int i = 0; i < buttonsCount; i++)
    buttons[i]->setup();

  display->setup();
  display->setValue(dndDice->getThrows(), dndDice->getDiceType());
}

void loop() {
  for (int i = 0; i < buttonsCount; i++)
    buttons[i]->update();

  dndDice->update();

  if (buttons[0]->isActive()){
    dndDice->startGenerating();
    display->setValue();
  }
  
  if (buttons[0]->wasReleased()){
    int rolled = dndDice->generatedNumber();
    display->setValue(rolled);
    if (rolled ==  dndDice->getThrows()){
      display->clear();
      music->failMelody();
    } 
    else if (rolled == dndDice->getThrows() * dndDice->getDiceType()){
      display->clear();
      music->successMelody();
    }
      
  }

  if (buttons[1]->isActive()){
    dndDice->increaseNumOfThrows();
    display->setValue(dndDice->getThrows(), dndDice->getDiceType());
  }

  if (buttons[2]->isActive()){
    dndDice->changeDiceType();
    display->setValue(dndDice->getThrows(), dndDice->getDiceType());
  }

  display->display();
}




