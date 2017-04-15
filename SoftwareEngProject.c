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

	struct SLOT *currSlot = NULL; // a pointer to current player location

	struct SLOT
			*upLeft, // a pointer to the top left corner struct SLOT object on the board. Slot (0, 0).
			*upRight, // a pointer to the top left corner struct SLOT object on the board. Slot (0, boardSize - 1).
			*downLeft, // a pointer to the top left corner struct SLOT object on the board. Slot (boardSize - 1, 0).
			*downRight, // a pointer to the top left corner struct SLOT object on the board. Slot (boardSize - 1, boardSize - 1).
			*gameSlots; // a pointer to a struct SLOT object (the first one in the array)

	// set the current time as the seed for the rand() function
	srand(time(NULL));

	boardSize = numPlayers = 0;


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


	// gameSlots points to the first element of the array (which is upLeft)
	// i do this because I feel like gameSlots is a better name to represent the array of slots
	gameSlots = upLeft;

	printf("\ngameSlots = %p, upLeft = %p, upRight = %p, downLeft = %p, downRight = %p\n", gameSlots,upLeft,upRight,downLeft,upRight);

	// set the slot type for each slot
	setSlotTypes(boardSize, gameSlots);

	// set up the players (getting their names, player type and capabilities)
	sortPlayers(gamePlayers, numPlayers);

	// set up the slots
	//setupSlots(boardSize, gameSlots);

	// randomly position players around the map (slots)
	setPlayerPositions(boardSize, gameSlots, numPlayers, gamePlayers);


	i = 0;
	// while there are still more than 1 player alive, keep going
	while (getTotalAlivePlayers(numPlayers, gamePlayers) > 1) {

		// reset the counter (A.K.A, a new round has started)
		if (i >= numPlayers)
			i = 0;

		// only players that are alive can have a turn
		if (gamePlayers[i].alive){

			//Finds the slot
			/*If the the required slot is closer to the down-right
			 * corner of the board the search starts from downRight,
			 * which points to slot at position (boardSize-1, boarSize -1)*/
			if(gamePlayers[i].row >= boardSize/2){
				if(gamePlayers[i].column >= boardSize/2)
					currSlot = reachDesiredElement(gamePlayers[i].row,gamePlayers[i].column,downRight);
				else
				/*If the the required slot is closer to the down-left
				* corner of the board the search starts from downLeft,
				* which points to slot at position (boardSize-1, 0)*/
					currSlot = reachDesiredElement(gamePlayers[i].row,gamePlayers[i].column,downLeft);
			} else {
				/*If the the required slot is closer to the up-right
				* corner of the board the search starts from upRight,
				* which points to slot at position (0, boarSize -1)*/
				if(gamePlayers[i].column >= boardSize/2)
					currSlot = reachDesiredElement(gamePlayers[i].row,gamePlayers[i].column, upRight);
				/*If the the required slot is closer to the up-left
				* corner of the board the search starts from upLeft,
				* which points to slot at position (0, 0)*/
				else currSlot = reachDesiredElement(gamePlayers[i].row,gamePlayers[i].column,upLeft);
			}

			nextTurn(boardSize, gameSlots, numPlayers, gamePlayers, &gamePlayers[i], currSlot);
		}



		i++;
	}

	printf("\n\n** Game Over! **\nHere are the end-game stats for every player!");
	//prints out <player name> (<player Type>, <life_pts>)
	for(i = 0; i < numPlayers; i++)
	{
		// TO-DO
		// check if alive == 1 and if hp > 0, then that player is the winner
		// if alive == 0 and if hp > 0, then that player manually exited the game
		printf("\n%s (%s, %d)", gamePlayers[i].name, getPtypeString(gamePlayers[i].playerType), gamePlayers[i].life_pts);
	}

	printf("\n\n");

	return EXIT_SUCCESS;
}

