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

#include "game_definitions.h"

// function prototypes
void setSlotTypes(unsigned int boardSize, struct SLOT *gameSlots);
char *getSlotString(enum SLOT_TYPES slotType);
void setPlayerPositions(unsigned int numSlots, struct SLOT *gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers);
void sortCap(struct PLAYER *gamePlayers, int i);
void sortPlayers(struct PLAYER *gamePlayers, unsigned int numPlayers);
int getCapabilitySum(struct PLAYER *player);
void nextTurn(unsigned int numSlots, struct SLOT *gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers, struct PLAYER *player);
int move(unsigned int numSlots, struct SLOT *gameSlots, struct PLAYER *player);
int attack(struct PLAYER gamePlayers[], struct PLAYER *player, unsigned int numPlayers);
void updateCapabilities(struct SLOT *gameSlots, struct PLAYER *player, size_t nextSlotType);
char *getPtypeString(enum PLAYER_TYPES playerType);

void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);
struct slot *  reachDesiredElement(int row, int column, struct slot * initialSlot);
void findSlots(int reqDist, int currDist,  struct slot * currSlot, struct slot * foundSlots, int * count,  bool explored[7][7]);
