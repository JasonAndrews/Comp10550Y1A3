/*
 ============================================================================
 Name        : 	SoftwareEngProject.c
 Module		 : 	COMP10550
 Group		 : 	4
 Authors     :
				Jason Andrews
				Jeremiah Wangaruro

 Description : 	This file contains the code necessary for Assignment Three.
				Assignment two tasks us with developing the later stages of the game.
				This includes:
					Updating the structs.
					Updating the move functionality.
					Updating the attack functionality.
					Adding / Updating other areas of the code, such as adding in a board (of 7 x 7 slots).
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
			**gameSlots; // a pointer of pointer to SLOTs

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

	printf("\nCreating board");
	
	// The board is represented as a pointer of pointer to SLOTs
	// This allocates in memory the space for the pointers to each row of the board
	gameSlots = malloc(boardSize * (sizeof(struct SLOT *)));
	createBoard(boardSize, gameSlots, &upLeft, &upRight, &downLeft, &downRight);
					
	// set the slot type for each slot
	setSlotTypes(boardSize, gameSlots);
	
	// set up the players (getting their names, player type and capabilities)
	sortPlayers(gamePlayers, numPlayers);

	// randomly position players around the map (slots)
	setPlayerPositions(boardSize, gameSlots, numPlayers, gamePlayers);

	i = 0;
	// while there are still more than 1 player alive, keep going
	while (getTotalAlivePlayers(numPlayers, gamePlayers) > 1) {

		// reset the counter (A.K.A, a new round has started)
		if (i >= numPlayers)
			i = 0;

		// only players that are alive and have not quit can have a turn 
		if ((gamePlayers[i].alive) && !(gamePlayers[i].quit)){
			
			//Finds the slot
			/*If the the required slot is closer to the down-right
			 * corner of the board the search starts from downRight,
			 * which points to slot at position (boardSize-1, boarSize -1)*/
			if(gamePlayers[i].row >= boardSize/2){
				if(gamePlayers[i].column >= boardSize/2)
					currSlot = reachDesiredElement(gamePlayers[i].row, gamePlayers[i].column, downRight);
				else
				/*If the the required slot is closer to the down-left
				* corner of the board the search starts from downLeft,
				* which points to slot at position (boardSize-1, 0)*/
					currSlot = reachDesiredElement(gamePlayers[i].row, gamePlayers[i].column, downLeft);
			} else {
				/*If the the required slot is closer to the up-right
				* corner of the board the search starts from upRight,
				* which points to slot at position (0, boarSize -1)*/
				if(gamePlayers[i].column >= boardSize/2)
					currSlot = reachDesiredElement(gamePlayers[i].row, gamePlayers[i].column, upRight);
				/*If the the required slot is closer to the up-left
				* corner of the board the search starts from upLeft,
				* which points to slot at position (0, 0)*/
				else currSlot = reachDesiredElement(gamePlayers[i].row, gamePlayers[i].column, upLeft);
			}
			
			nextTurn(boardSize, gameSlots, numPlayers, gamePlayers, &gamePlayers[i], currSlot);
			//nextTurn(unsigned int numSlots, struct SLOT **gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers, struct PLAYER *player, struct SLOT *currSlot)
		}



		i++;
	}

	printf("\n\n** Game Over! **\nHere are the end-game stats for every player!");
	//prints out <player name> (<player Type>, <life_pts>) or "quit the game"
	for(i = 0; i < numPlayers; i++)
	{
		// TO-DO
		// check if alive == 1 and if hp > 0, then that player is the winner
		// if alive == 0 and if hp > 0, then that player manually exited the game
		if(gamePlayers[i].quit == 1){
			printf("\n%s quit the game", gamePlayers[i].name);
		}else{
			printf("\n%s (%s, %d)", gamePlayers[i].name, getPtypeString(gamePlayers[i].playerType), gamePlayers[i].life_pts);
		}
	}

	printf("\n\n");

	return EXIT_SUCCESS;
}

