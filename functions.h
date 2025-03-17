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

enum ROUND_OUTCOME {
	P1_WINS_MAGE_V_MAGE = -1,
	P2_WINS_MAGE_V_MAGE = 1,
	P1_WINS_FIGHTER_V_FIGHTER = -3,
	P2_WINS_FIGHTER_V_FIGHTER = 3,
	P1_WINS_TANK_V_TANK = -7,
	P2_WINS_TANK_V_TANK = 7,
	P1_WINS_MAGE_V_FIGHTER = -2,
	P2_WINS_MAGE_V_FIGHTER = 2,
	P1_WINS_MAGE_V_TANK = -4,
	P2_WINS_MAGE_V_TANK = 4,
	P1_WINS_FIGHTER_V_TANK = -5,
	P2_WINS_FIGHTER_V_TANK = 5,
	TIE_MvM_OR_MvF = 8,
};

int getRandomNumber(int, int);

enum CHAMPION createChampion();

int getChampionPoints(enum CHAMPION);

void printChampion(enum CHAMPION);

void playRound(int*, int*, enum CHAMPION, int, enum CHAMPION, int);


#endif //FUNCTIONS_H