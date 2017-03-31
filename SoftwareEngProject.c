/*
 ============================================================================
 Name        : 	SoftwareEngProject.c
 Module		 : 	COMP10550
 Group		 : 	4	
 Authors     : 
				Jason Andrews
				Jeremiah Wangaruro
				
 Description : 	This file contains the code necessary for Assignment Two.
				Assignment two tasks us with developing the early stages of the game.
				This includes:
					Setting up the necessary structs.
					Setting up the necessary enums.
					Populating the structs.
					Implementing some auto character creation.
 ============================================================================
 */

 //include header file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "game_functions.h"
#include "game_functions.c"


// main function
int main(void) {

	size_t 
		i; // used in loops
		
	unsigned int 
		numSlots, // the number of slots in the game, entered by the user
		numPlayers; // the number of players in the game, entered by the user
	
	struct PLAYER 
			*gamePlayers; // an array of struct PLAYER 
			
	struct SLOT
			*gameSlots; // a pointer to a struct SLOT object (the first one in the array)
	
	// set the current time as the seed for the rand() function
	srand(time(NULL));
	
	numSlots = numPlayers = 0;
	
	// keep looping until a valid number of players is entered
	do {
		
		printf("\nPlease enter the number of players (min. 2 and max. 6 players)\n-> ");
		fflush(stdin); // flush the stdin buffer
		scanf("%d", &numPlayers);
		
		if (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS)
			printf("\nERROR INVALID ENTRY: \nPlease enter a number between %d and %d!\n", MIN_PLAYERS, MAX_PLAYERS);
		
	} while (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS);
	// allocate the required amount of memory for a numPlayers sized array of type struct PLAYER
	gamePlayers = (struct PLAYER * const) malloc(sizeof(struct PLAYER) * numPlayers);
	
	// keep looping until a valid number of slots is entered
	do {
		// prompt for, and capture the number of slots for the game
		printf("\nPlease enter the number of slots for the game (min. %d and max. %d).\n-> ", numPlayers, MAX_NUM_OF_SLOTS);
		fflush(stdin); // flush the stdin buffer
		scanf("%d", &numSlots);
		
		if (numSlots < numPlayers || numSlots > MAX_NUM_OF_SLOTS)
			printf("\nERROR - Please enter a valid value for the number of slots!\n");
		
	} while (numSlots < numPlayers || numSlots > MAX_NUM_OF_SLOTS);
	// allocate the required amount of memory for a numSlots sized array of type struct SLOT
	gameSlots = (struct SLOT * const) malloc(sizeof(struct SLOT) * numSlots);
	
	// set up the players (getting their names, player type and capabilities)
	sortPlayers(gamePlayers, numPlayers);
	
	// set up the slots
	setupSlots(numPlayers, numSlots, gameSlots);
	
	// randomly position players around the map (slots)	
	setPlayerPositions(numSlots, gameSlots, numPlayers, gamePlayers);

	// start the game - Player1 -> PlayerN will have a turn
	for (i = 0; i < numPlayers; i++) {		
		nextTurn(numSlots, gameSlots, numPlayers, gamePlayers, &gamePlayers[i]);
	}
	
	printf("\n\n** Game Over! **\nHere are the end-game stats for every player!");
	//prints out <player name> (<player Type>, <life_pts>)
	for(i = 0; i < numPlayers; i++)
	{
		printf("\n%s (%s, %d)", gamePlayers[i].name, getPtypeString(gamePlayers[i].playerType), gamePlayers[i].life_pts);
	}
	
	printf("\n\n");
	
	return EXIT_SUCCESS;
}

