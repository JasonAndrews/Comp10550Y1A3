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

// include standard header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// include custom header files
#include "game_definitions.h"
#include "game_functions.h"


// main function
int main(void) {

	size_t 
		i; // used in loops
		
	unsigned int 
		boardSize, // the number of slots in the game, entered by the user
		numPlayers; // the number of players in the game, entered by the user
	
	struct PLAYER 
			*gamePlayers; // an array of struct PLAYER 
			
	struct SLOT
			*upLeft, // a pointer to the top left corner struct SLOT object on the board. Slot (0, 0).
			*upRight, // a pointer to the top left corner struct SLOT object on the board. Slot (0, boardSize - 1).
			*downLeft, // a pointer to the top left corner struct SLOT object on the board. Slot (boardSize - 1, 0).
			*downRight, // a pointer to the top left corner struct SLOT object on the board. Slot (boardSize - 1, boardSize - 1).
			*gameSlots; // a pointer to a struct SLOT object (the first one in the array)
	
	// set the current time as the seed for the rand() function
	srand(time(NULL));
	
	boardSize = numPlayers = 0;
	
	/*
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
	*/
	// keep looping until a valid board size is entered
	do {
		// prompt for, and capture the board size for the game
		printf("\nPlease enter the size of the board (min. %d and max. %d).\n-> ", MIN_BOARD_SIZE, MAX_BOARD_SIZE);
		fflush(stdin); // flush the stdin buffer
		scanf("%d", &boardSize);
		
		if (boardSize < MIN_BOARD_SIZE || boardSize > MAX_BOARD_SIZE)
			printf("\nERROR - Please enter a valid value for the number of slots!\n");
		
	} while (boardSize < MIN_BOARD_SIZE || boardSize > MAX_BOARD_SIZE);
	// allocate the required amount of memory for a boardSize sized array of type struct SLOT
	
	//gameSlots = (struct SLOT * const) malloc(sizeof(struct SLOT) * (boardSize * boardSize));
	createBoard(boardSize, &upLeft, &upRight, &downLeft, &downRight);
	
	gameSlots = upLeft; // so gameSlots points to the first element of the array
	
	printf("gameSlots = %p, upLeft = %p, upRight = %p, downLeft = %p, downRight = %p\n", gameSlots,upLeft,upRight,downLeft,upRight);
	
	// set up the players (getting their names, player type and capabilities)
	//sortPlayers(gamePlayers, numPlayers);
	
	// set up the slots
	//setupSlots(boardSize, gameSlots);
	
	// randomly position players around the map (slots)	
	//setPlayerPositions(boardSize, gameSlots, numPlayers, gamePlayers);

	// start the game - Player1 -> PlayerN will have a turn
	for (i = 0; i < numPlayers; i++) {		
		//nextTurn(boardSize, gameSlots, numPlayers, gamePlayers, &gamePlayers[i]);
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

