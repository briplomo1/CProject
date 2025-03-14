//
// Created by b1n4r33 on 3/12/25.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H


enum CHAMPION {
  MAGE=0,
  FIGHTER=1,
  TANK=3
 };

int getRandomNumber(int, int);

enum CHAMPION createChampion();

int getChampionPoints(enum CHAMPION);

void printChampion(enum CHAMPION);

void playRound(int, int, enum CHAMPION, int, enum CHAMPION, int);


#endif //FUNCTIONS_H