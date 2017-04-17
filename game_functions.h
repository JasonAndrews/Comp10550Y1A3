/*
 ============================================================================
 Name        : game_functions.h
 Authors     :
				Jason Andrews
				Jeremiah Wangaruro

 Version     : 0.1
 Description : 	This header file contains all the necessary function prototypes
				for implementing the functionality of the game.
 ============================================================================
*/

//definitions
#ifndef 	GAME_FUNCTIONS_H_
#define 	GAME_FUNCTIONS_H_

#include <stdbool.h>
#include <stddef.h>
#include "game_definitions.h"

#define 	MAX_PTS				100

#define 	MIN_PLAYERS			2
#define 	MAX_PLAYERS			6

#define 	TOTAL_SLOT_TYPES	3

#define		NEAR_ATTACK			1
#define		DISTANT_ATTACK		5


// function prototypes
void setSlotTypes(unsigned int boardSize, struct SLOT **gameSlots);
char *getSlotString(enum SLOT_TYPES slotType);
void setPlayerPositions(unsigned int numSlots, struct SLOT **gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers);
void sortCap(struct PLAYER *gamePlayers, int i);
void sortPlayers(struct PLAYER *gamePlayers, unsigned int numPlayers);
int getCapabilitySum(struct PLAYER *player);
void nextTurn(unsigned int numSlots, struct SLOT **gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers, struct PLAYER *player, struct SLOT *currSlot);
int move(unsigned int numSlots, struct SLOT **gameSlots, struct PLAYER *player);
int attack(struct PLAYER *gamePlayers, struct PLAYER *player, unsigned int numPlayers, struct SLOT *currSlot, unsigned int boardSize);
void updateCapabilities(struct SLOT **gameSlots, struct PLAYER *player, size_t nextSlotRow, size_t nextSlotCol);
char *getPtypeString(enum PLAYER_TYPES playerType);

int getTotalAlivePlayers(unsigned int numStartPlayers, struct PLAYER *gameSlots);

void createBoard(int boardSize, struct SLOT **gameSlots, struct SLOT **upLeft, struct SLOT **upRight, struct SLOT **downLeft, struct SLOT **downRight);
struct SLOT *  reachDesiredElement(int row, int column, struct SLOT * initialSlot);
void findSlots(int reqDist, int currDist,  struct SLOT * currSlot, struct SLOT * foundSlots, int * count,  bool explored[7][7]);


#endif
