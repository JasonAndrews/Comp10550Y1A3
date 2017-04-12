/*
 ============================================================================
 Name        : game_functions.c
 Authors     : 
				Jason Andrews
				Jeremiah Wangaruro
				
 Description : 	This C file contains all implementation of the necessary functions for the game.
 ============================================================================
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "game_functions.h"

/* Function: 	setSlotTypes
 * Description:
 * 				Randomise the slot type for every slot.
 *	Parameters:
 *		boardSize : uint - The size of the array.
 *		gameSlots : struct SLOT pointer - Pointer to the start of the array of slots. 
 *
 *	Returns:
 *		gameSlots : pointer to struct SLOT - The array of slots (the memory of the first element of the array)
 */
void setSlotTypes(unsigned int boardSize, struct SLOT *gameSlots) {
	
	size_t
		i, // used in loops
		j;
	
	//printf("\nStarting slot type assignment! [gameSlots = %p]\n", *gameSlots);
	// assign a slot a random SLOT_TYPES
	for (i = 0; i < boardSize; i++) {		
		for (j = 0; j < boardSize; j++) {		
			// assign a different slot type
			gameSlots[i*j].slotType = (rand() % TOTAL_SLOT_TYPES) + 1;			
			//printf("Slot[%d][%d] (%p) is of type %s\n", i, j, &gameSlots[i*j], getSlotString(gameSlots[i*j].slotType));
		}		
	}
	
} // end of setupSlots() function



/* Function Name: 	getSlotString
 * Description:
 * 		Returns a string representation of the enum values of the enum SLOT_TYPES.
 *	Parameters:
 *		slotType : enum SLOT_TYPES - The SLOT_TYPES of a particular slot.
 *
 *	Returns:
 *		slotString : string pointer - The string representation.
 */
char* getSlotString(enum SLOT_TYPES slotType) {
	
	char *slotString = "";
	
	switch (slotType) {
		case LEVEL_GROUND: {
			slotString = "Level Ground";
			break;
		}
		case HILL: {
			slotString = "Hill";
			break;
		}
		case CITY: {
			slotString = "City";
			break;
		}
		default: {
			slotString = "ERROR";
			break;
		}
	}
	return slotString;	
} // end of getSlotString() function



/* Function Name: 	getPtypeString
 * Description:
 * 		Returns a string representation of the enum values of the enum PLAYER_TYPES.
 *	Parameters:
 *		playerType : enum PLAYER_TYPES - The PLAYER_TYPES of a particular slot.
 *
 *	Returns:
 *		typeString : string pointer - The string representation.
 */
char* getPtypeString(enum PLAYER_TYPES playerType) {
	
	char *typeString = "";
	
	switch (playerType) {
		case ELF: {
			typeString = "Elf";
			break;
		}
		case HUMAN: {
			typeString = "Human";
			break;
		}
		case OGRE: {
			typeString = "Ogre";
			break;
		}
		case WIZARD:{
			typeString = "Wizard";
			break;
		}
		default:{
			typeString = "ERROR";
			break;
		}
	}
	
	return typeString;	
} // end of getPtypeString() function


/* Function Name: 	
 * 		setPlayerPositions
 * Description:
 * 		Randomly positions players around the map (in random slots).
 *	Parameters:
 *		boardSize : uint - The number of slots in the game.
 * 		gameSlots : struct SLOT pointer - Pointer to the start of the array of slots. 
 * 		numPlayers : uint - The number of players in the game.
 *      gamePlayers : struct PLAYER pointer - Pointer to the start of the array of players. 
 *
 *	Returns:
 *		N/A
 */
void setPlayerPositions(unsigned int boardSize, struct SLOT * gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers) {

	size_t 
		randRow, // random row
		randColumn, // random column
		i, // stores the index of the current player being placed
		row, // the row the player is positioned on
		column; // the column the player is positioned on
	
	// loop numPlayers times (the number of players in the game)
	for (i = 0; i < numPlayers; i++) {
		
		// get a random slot index
		randRow = (rand() % boardSize);		
		randColumn = (rand() % boardSize);		
		//printf("\nrandIndex = %d", randRow * randColumn);
				
		// update the player's position member
		gamePlayers[i].row = randRow; 
		gamePlayers[i].column = randColumn; 
		
		updateCapabilities(gameSlots, &gamePlayers[i], gamePlayers[i].row * gamePlayers[i].column);
		
		printf("\nPlayer %s was placed at Slots[%d][%d]", gamePlayers[i].name, randRow, randColumn);
		
	}
} // end of setPlayerPositions() function



 

/* Function Name: 
 * 		sortPlayers
 * Description:
 * 		Set up the array of players. 
 *	Parameters:
 * 		gamePlayers : struct PLAYER pointer - Pointer to the start of the array of players. 
 * 		numPlayers : uint - The number of players in the game.
 *
 *	Returns:
 *		N/A
 */
void sortPlayers(struct PLAYER *gamePlayers, unsigned int numPlayers)
{
	size_t 
		curPlayer, // the current player being set up (in the gamePlayers array)
		i; // used to iterate through the player's name
		
	unsigned int 
			type; // the class type the player chooses
	
	

	// loop numPlayers times and ask for the player's name and type
	for (curPlayer = 0; curPlayer < numPlayers; curPlayer++) 
	{
		
		printf("\nPlayer %d, please enter your name (20 characers max.)\n-> ", (curPlayer + 1));
		fflush(stdin); // flush the stdin buffer
		fflush(stdout); // flush the stdout buffer
		fgets(gamePlayers[curPlayer].name, 20, stdin); // get a line of input from the user
		
		// remove the NEWLINE character from the player's name.
		for (i = 0; gamePlayers[curPlayer].name[i] != '\0'; i++) { 				
			if (gamePlayers[curPlayer].name[i] == '\n') {
				gamePlayers[curPlayer].name[i] = '\0'; // set the current character as the EOS character
				break;
			}
		}			
		
		// loop until the player enters a correct player type
		do {
			printf("\n%s, please select your type:\n", gamePlayers[curPlayer].name);
			printf("1. Elf.\n");
			printf("2. Human.\n");
			printf("3. Ogre.\n");
			printf("4. Wizard.\n");
			printf("Your choice: ");
			fflush(stdin);
			scanf("%d", &type);	
			
			if (!(type >= 1 && type <= 4))
				printf("\nERROR INVALID ENTRY: \nPlease enter a number between 1 and 4!\n");
			
		} while (!(type >= 1 && type <= 4));
		
		
		switch(type)
		{
			case 1:
				gamePlayers[curPlayer].playerType = ELF;
				break;

			case 2:
				gamePlayers[curPlayer].playerType = HUMAN;
				break;

			case 3:
				gamePlayers[curPlayer].playerType = OGRE;
				break;

			case 4:
				gamePlayers[curPlayer].playerType = WIZARD;
				break;

			default:
				printf("\nERROR INVALID ENTRY: Please enter a number between 1 and 4!\n");
		}			
		
		gamePlayers[curPlayer].life_pts = MAX_PTS;				
		
		// set up the capabilities for the ith player
		sortCap(gamePlayers, curPlayer);			

	}
	
} // end of sortPlayers() function


/* Function Name: 
 * 		sortCap
 * Description:
 * 		Assigns values to the player capabilities. 
 *	Parameters:
 * 		gamePlayers : struct PLAYER pointer - Pointer to the start of the array of players.
 *		i : integer - The index of the player in the array being set up
 *
 *	Returns:
 *		N/A
 */
void sortCap(struct PLAYER *gamePlayers, int i)
{
	bool 
		valid; // whether the player's capabilities is vald
	time_t 
		currentTime;
			
	switch (gamePlayers[i].playerType) {
		
		case HUMAN: {
			
			// keep randomising all capabilities until the sum is less than 300
			do {
			
				gamePlayers[i].caps.smartness = 1 + (rand() % 100);
				gamePlayers[i].caps.luck = 1 + (rand() % 100);
				gamePlayers[i].caps.strength = 1 + (rand() % 100);
				gamePlayers[i].caps.magicSkills = 1 + (rand() % 100);
				gamePlayers[i].caps.dexterity= 1 + (rand() % 100);
				
				// check if the requirements for the human player type was met
				if(getCapabilitySum(&gamePlayers[i]) < 300)
					valid = true;
				else 
					valid = false;
				
			} while (!valid);
			
			break;
		}
		case OGRE: {
			
			gamePlayers[i].caps.magicSkills = 0;
			gamePlayers[i].caps.strength = 80+rand()%21;
			gamePlayers[i].caps.dexterity = 80+rand()%21;
			
			// keep randomising smartness and luck until the sum is less than 50
			do
			{
				
				gamePlayers[i].caps.smartness = rand()%21;
				gamePlayers[i].caps.luck = rand()%51;
				
				// check if the requirements for the ogre player type was met
				if((gamePlayers[i].caps.smartness + gamePlayers[i].caps.luck) < 50)
					valid = true;
				else
					valid = false;
				
			} while (!valid);	
			
			break;
		}
		case ELF: {
			gamePlayers[i].caps.luck = 60+rand()%41;
			gamePlayers[i].caps.smartness = 70+rand()%31;
			gamePlayers[i].caps.strength = 1+rand()%50;
			gamePlayers[i].caps.magicSkills = 51+rand()%30;
			gamePlayers[i].caps.dexterity = 1+rand()%99;
			break;
		}
		case WIZARD: {
			gamePlayers[i].caps.luck = 50+rand()%51;
			gamePlayers[i].caps.smartness = 90+rand()%11;
			gamePlayers[i].caps.strength = 1+rand()%20;
			gamePlayers[i].caps.magicSkills = 80+rand()%21;
			gamePlayers[i].caps.dexterity = 1+rand()%99;
			break;
		}	
	} // end switch
	
}// end of sortCap() function



/* Function Name: 
 * 		getCapabilitySum
 * Description:
 * 		Returns the sum of the player's capabilities.
 *	Parameters:
 * 		player : struct PLAYER pointer - Pointer to the player. 
 *
 *	Returns:
 *		N/A
 */
int getCapabilitySum(struct PLAYER *player) {
	
	int 
		capSum = 0;
	
	capSum += player->caps.smartness;
	capSum += player->caps.strength;
	capSum += player->caps.magicSkills;
	capSum += player->caps.luck;
	capSum += player->caps.dexterity;

	return capSum;
	
} // end of getCapabilitySum() function

/* Function Name: 
 * 		nextTurn
 * Description:
 * 		Lets a player take their turn - either to move or attack.
 *	Parameters:
 *		numSlots : uint - The number of slots in the game.
 *		gameSlots : struct SLOT pointer - Pointer to the start of the array of slots. 
 * 		numPlayers : uint - The number of players in the game.
 * 		gamePlayers : struct PLAYER pointer - Pointer to the start of the array of players. 
 *		player : struct PLAYER pointer - Pointer to the player taking their turn.
 *
 *	Returns:
 *		N/A
 */
void nextTurn(unsigned int numSlots, struct SLOT *gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers, struct PLAYER *player) {
		
	unsigned int 
		turnChoice; // user input for the menu
	int 
		completedTurn = 0; // ensures every player takes their turn
			
	do {
		
		do {
			printf("\n%s, it is your turn.\nWhat do you want to do?\n1. Attack.\n2. Move.\nYour choice: ", player->name);
			fflush(stdin); // flush the stdin buffer
			scanf("%d", &turnChoice);
	
		} while (turnChoice < 1 || turnChoice > 2);
		
		switch (turnChoice) {		
			case 1: {
				// the player wants to attack
				completedTurn = attack(gamePlayers, player, numPlayers);
				break;
			}
			case 2: {	
				// the player wants to move
				completedTurn = move(numSlots, gameSlots, player);
				break;
			}
		}
	} while (!completedTurn);
	
} // end of nextTurn() function


/* Function Name: attack
 * Description:
 * 		Attacks a target for a player. 
 *	Parameters:
 *		gamePlayers : struct PLAYER pointer - Pointer to the start of the array of players. 
 *		player : struct PLAYER pointer - Pointer to the attacking player.
 * 		numPlayers : uint - The number of players in the game.
 *
 *	Returns:
 *		int - Returns 1 if they completed their move and 0 if they didn't.
 */
int attack(struct PLAYER *gamePlayers, struct PLAYER *player, unsigned int numPlayers)
{
	int 
		completedTurn; // the returned value
		
	size_t 
		i; // used in loops
	
	unsigned int 
			minDist = (20) /*MAX_SLOTS*/,
			numClosePlayers = 0, // the number of players at the same minDist to the player
			attackedPlayer = 0, // index of the attacked player in the closeByPlayers array
			choice; // user input
			
	struct PLAYER 
			** closeByPlayers; // array of pointers to pointers of struct PLAYER
		
	bool	
		validChoice = false; // if the user input is valid
	
	// allocate the required amount of memory for an array of size 2 of type pointer to pointer of struct PLAYER
	closeByPlayers = (struct PLAYER * * const) malloc(sizeof(struct PLAYER) * 2);
	
	// loop through all the players to compute the minimum distance
	for (i = 0; i < numPlayers; i++) {
		
		// skip the iteration for the player attacking
		if ((&gamePlayers[i]) == player)
			continue;
		
		/*
		// if the selected player's position MINUS the currently iterated player's position - update minDist
		if (abs(player->position - gamePlayers[i].position) < minDist) {
			// update the minDist
			minDist = abs(player->position - gamePlayers[i].position);
			/*
				The abs(olute) function is used to get an unsigned integer value for the distance
				Example:
					Index 2 - 4 = abs(-2) = 2
					Index 4 - 2 = 2
			*/
		//}
	}
	
	// loop through all the players to compute the number of players the attacker can attack
	for (i = 0; i < numPlayers; i++) {
		
		// skip the iteration for the player attacking
		if ((&gamePlayers[i]) == player) 
			continue;
				
		// if the selected player's position MINUS the currently iterated player's position - update minDist
		/*if (abs(player->position - gamePlayers[i].position) == minDist) {
			// place the player at minDist from the attacker in the array
			closeByPlayers[numClosePlayers] = &gamePlayers[i];
			numClosePlayers++; // increment
		}*/		
	}
	
	attackedPlayer = 0; // set the default target as element 0 of closeByPlayers
	
	// implement the actual attacking of the players
	if (numClosePlayers == 2) {
		// the attacking player has 2 close targets to attack
		
		do {
			
			printf("\nYou are between two players.\nWho do you want to attack?\n1. %s.\n2. %s.\nAttack: ", closeByPlayers[0]->name, closeByPlayers[1]->name);
			fflush(stdin); // flush the stdin buffer
			scanf("%d", &choice);			
			
			if(choice == 1)
			{
				attackedPlayer = 0; // index of player to be attacked in the closeByPlayers array
				validChoice = true;
			}
			else if(choice == 2)
			{
				attackedPlayer = 1;
				validChoice = true;
			}
			
		} while (!validChoice);
		
	}

	// attack the target player 
	if((closeByPlayers[attackedPlayer]->caps.strength) <= 70)
	{
		// damage the target
		closeByPlayers[attackedPlayer]->life_pts -= (0.5*(closeByPlayers[attackedPlayer]->caps.strength));
		printf("\n%s attacked %s and damaged them!\n", player->name, closeByPlayers[attackedPlayer]->name);
	} else {
		// damage the attacker
		player->life_pts -= (0.3 * (player->caps.strength));
		printf("\n%s attacked %s but wasn't strong enough and got hurt!\n", player->name, closeByPlayers[attackedPlayer]->name);
	}	 
	
	return 1;
	
}// end of attack() function.


/* Function Name: move
 * Description:
 * 		Implements player movement. 
 * 		A player can move in either direction, unless, they are in the first slot (can only go forward) or the last slot (can only go backward)
 *	Parameters:
 *		numSlots : uint - The number of slots in the game.
 * 		gameSlots : struct SLOT pointer - Pointer to the start of the array of slots. 
 * 		player : struct PLAYER pointer - Pointer to the taking their player.
 *
 *	Returns:
 *		int - 1 if they completed their move, 0 if they didn't
 */
int move(unsigned int numSlots, struct SLOT *gameSlots, struct PLAYER *player) {
	
	
	size_t	
		i,
		currentPosition;
	
	int
		completedMove = 0;
		
	unsigned int 
		moveChoice,
		distToNextPlayer;

	for (i = 0; i < numSlots; i++) {
		//printf("\ngameSlots[i].player = %p | player = %p", gameSlots[i].player, player);
		/* FIX if (gameSlots[i].player == player) {
			currentPosition = i;
			break;
		}*/
	}
	
		
	// FIX currentPosition = player->position;
	// FIX printf("\n%s, your location is %d. Please select a direction.\n1. Forward.\n2. Backward\nYour choice: ", player->name, player->position);
	fflush(stdin); // flush the stdin buffer
	scanf("%d", &moveChoice);

	switch (moveChoice) {
		
		case 1: {
			// move forward
			/* FIX if (player->position == (numSlots - 1)) {
				printf("Sorry, you cannot move forward!\n\n");
				break;
			}*/
			
			/* FIX
			// check if the next slot is empty
			if (gameSlots[(currentPosition + 1)].player == NULL)  {
				
				updateCapabilities(gameSlots, player, (player->position + 1));
				
				player->position++;
				printf("\n%s, you moved forward to location %d.", player->name, player->position);
				
				gameSlots[player->position].player = player;
				gameSlots[currentPosition].player = NULL;
				
				completedMove = 1;
				
			} else {
				// the slot has a player already
				printf("\nYou cannot move to that position because another player is already there!\n");
			}*/
			
			break;
		}
		case 2: {
			// move backward
			/* FIX
			if (player->position == 0) {
				printf("Sorry, you cannot move backwards!\n\n");
				break;
			}
			*/
			
			
			// check if the previous slot is empty
			/* FIX if (gameSlots[(currentPosition - 1)].player == NULL)  {
				
				updateCapabilities(gameSlots, player, (player->position - 1));
				
				player->position--;
				printf("\n%s, you moved backwards to location %d.", player->name, player->position);
				
				gameSlots[player->position].player = player;
				gameSlots[currentPosition].player = NULL;
				
				completedMove = 1;
				//updateCapabilities();
			} else {
				// the slot has a player already
				printf("\nYou cannot move to that position because another player is already there!\n");
			}*/
			
			break;
		}
	}
	
	return completedMove;
} // end of move() function



/* Function Name: updateCapabilities
 * Description:
 * 		Updates player capabilities depending on the SLOT_TYPES they are in.
 * 		Leaving a slot that removes capabilities will restore the stats lost.
 * 		Entering a slot that will remove capabilities will do so.
 *	Parameters:
 *		gameSlots : struct SLOT pointer - Pointer to the start of the array of slots. 	
 * 		player : struct PLAYER pointer - Pointer to the taking their player.
 *		nextSlotIndex : size_t	- The index of the slot the player will be in next.
 *	Returns:
 *		N/A
 */
void updateCapabilities(struct SLOT *gameSlots, struct PLAYER *player, size_t nextSlotIndex) {
	
	enum SLOT_TYPES 
			prevSlotType, // the SLOT_TYPES of the old slot
			nextSlotType; // the SLOT_TYPES of the new slot
	
	// FIX prevSlotType = gameSlots[(player->position)].slotType;
	nextSlotType = gameSlots[nextSlotIndex].slotType;
		
		
	// update the players capabilities only if they are not going to the same slot type
	if (nextSlotType != prevSlotType) {
		
		// depending on the next slot type the player will enter, update their capabilities to their previous state
		switch (prevSlotType) {
			case HILL: {
				
				if (player->caps.dexterity < 50) 
					player->caps.strength += 10;
				else if (player->caps.dexterity >= 60)
					player->caps.strength -= 10;
				
				break;
			}
			case CITY: {
				
				if (player->caps.smartness > 60)					
					player->caps.magicSkills -= 10;
				else if (player->caps.smartness <= 50)
					player->caps.dexterity += 10;
				
				break;
			}
		}
		
		// depending on the next slot type the player will enter, update their capabilities
		switch (nextSlotType) {
			case HILL: {
				
				if (player->caps.dexterity < 50)  {
					player->caps.strength -= 10;
					
					if (player->caps.strength < 0)
						player->caps.strength = 0;
					
				} else if (player->caps.dexterity >= 60) {
					player->caps.strength += 10;

					if (player->caps.strength > 100)
						player->caps.strength = 100;
				
				}
				break;
			}
			case CITY: {
				
				if (player->caps.smartness > 60) {		
					player->caps.magicSkills += 10;
					
					if (player->caps.magicSkills > 100)
						player->caps.magicSkills = 100;
					
				} else if (player->caps.smartness <= 50) {
					player->caps.dexterity -= 10;
					
					if (player->caps.dexterity < 0)
						player->caps.magicSkills = 0;
				}
				break;
			}
		}		
	}

	
} // end of updateCapabilities() function


/* START OF TO-DO LIST
// get array of slots within distance from findSlots function
// have an array of players
// loop through array of players and check if their SLOT is in the array of slots returned from findSlots
// CHECK IF PLAYER IS ALIVE
// if alive, compare the players row and column to the slots row and column
for (each player in player array) {
	
	// check if the player is alive
	// if yes, enter loop
	for (each slot in slot array) {		
		// check if player->row, player->column ===== slot->row, slot->column
		// if they match, then add this PLAYER to a player array		
	}	
}
// return player array (so the current player can attack the player they want)
// END OF TO-DO LIST */

/*
 * This function creates the board
 * Parameters:
 * 	size: the size of the board
 * 	upLeft: pointer of pointer to slot at position (0, 0)
 * 	upRight: pointer of pointer to slot at position (0, boardSize -1)
 * 	downLeft: pointer of pointer to slot at position (boardSsize -1, 0)
 * 	upLeft: pointer of pointer to slot at position (boardSize - 1, boardSize -1)
 */
void createBoard(int boardSize, struct SLOT **upLeft, struct SLOT **upRight, struct SLOT **downLeft, struct SLOT **downRight){

	//The board is represented as a pointer of pointer to SLOTs
	//This allocates in memory the space for the pointers to each row of the board
	struct SLOT ** board = malloc(boardSize * sizeof(struct SLOT *));


	for(int i =0; i< boardSize; i++){
		//This allocates in memory the space for the slots in each row of the board
		board[i] = malloc(boardSize * sizeof(struct SLOT));

		//For each slot it sets up the row and column number
		for(int j=0;j < boardSize; j++){
			board[i][j].row = i;
			board[i][j].column = j;
		}
	}

	//It sets up the adjacent slots for the slots that are
	//not at the borders. These slots have 4 adjacent elements
	for(int i =1; i< boardSize-1; i++){
		for(int j=1;j < boardSize-1; j++){
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last row, except the slots at the edges.
	//
	for(int j = 1; j < boardSize -1; j++){
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on top of them
		// because they are on the first row of the board
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on down them
		// because they are on the last row of the board
		board[boardSize - 1][j].right = &board[boardSize - 1][j+1];
		board[boardSize -1][j].left = &board[boardSize - 1][j-1];
		board[boardSize - 1][j].up = &board[boardSize - 2][j];
		board[boardSize - 1][j].down = NULL;
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last column, except the slots at the edges.
	//
	for(int i = 1; i < boardSize -1; i++){
		//It sets up the adjacent slots for the slots that are in the first column.
		//These slots don't have an adjacent element on the left
		// because they are on the first column of the board
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];
		board[i][0].left = NULL;

		//It sets up the adjacent slots for the slots that are in the last column.
		//These slots don't have an adjacent element on the right
		// because they are on the last column of the board
		board[i][boardSize-1].left = &board[i][boardSize-2];
		board[i][boardSize -1].up = &board[i -1][boardSize-1];
		board[i][boardSize -1].down = &board[i+1][boardSize -1];
		board[i][boardSize -1].right = NULL;
	}


		//It sets up the adjacent slots for the slot at position (0,0).
		//This only has only 2 adjacent slots: right and down
		board[0][0].right = &board[0][1];
		board[0][0].down = &board[1][0];

		//It sets up the adjacent slots for the slot at position (0,boardSize -1).
		//This only has only 2 adjacent slots: left and down
		board[0][boardSize-1].left = &board[0][boardSize-2];
		board[0][boardSize -1].down = &board[1][boardSize -1];

		//It sets up the adjacent slots for the slot at position (boarSize -1 ,0).
		//This only has only 2 adjacent slots: up and right
		board[boardSize -1][0].right = &board[boardSize -1][1];
		board[boardSize -1][0].up = &board[boardSize -2][0];

		//It sets up the adjacent slots for the slot at position (boarSize -1 ,boardSize-1).
		//This only has only 2 adjacent slots: up and left
		board[boardSize - 1][boardSize-1].up = &board[boardSize-2][boardSize-1];
		board[boardSize - 1][boardSize -1].left = &board[boardSize -1][boardSize -2];







	//assigns a pointer to slot at position (0, 0)
	*upLeft = &board[0][0];
	//assigns pointer of pointer to slot at position (0, boardSize -1)
	*upRight = &board[0][boardSize -1];
	//assigns pointer of pointer to slot at position ( boardSize -1,)
	*downLeft = &board[boardSize -1][0];
	//assigns pointer of pointer to slot at position (boardSize -1, boardSize -1)
	*downRight = &board[boardSize -1][boardSize -1];
	}



/*
 * This function traverses the board to find a slot at a predefined
 * position (row, column). This function returns a pointer to the desired slot
 * Parameters:
 * 	row: the row in which the desired slot is located
 * 	column: the column in which the desired slot is located
 * 	initialSlot: the slot from which the slot search should start
 */
struct SLOT * reachDesiredElement(int row, int column, struct SLOT * initialSlot){

	bool found = false;
	//current slot
	struct SLOT * currentSlot = initialSlot;

	printf("\nFunction reachDesiredElement invoked\n");

	//prints the column and the row of the initial slot from which the search starts
	printf("Initial slot (%d, %d) -> \n",initialSlot->row,initialSlot->column);


	//while the slot is not found
	while(found == false){


		//if the row of the current slot is > of the row of the desired slot,
		//we move up
		if(currentSlot->row > row){
			//the current slot now points to the slot one row up
			currentSlot = currentSlot->up;
			//prints the column and the row of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);
		}
		//if the row of the current slot is < of the row of the desired slot,
		//we move down
		if(currentSlot->row < row){
			//the current slot now points to the slot one row down
			currentSlot = currentSlot->down;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the column of the current slot is > of the column of the desired slot,
		//we move left
		if(currentSlot->column > column){

			//the current slot now points to the slot one column left
			currentSlot = currentSlot->left;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);
		}

		//if the column of the current slot is < of the column of the desired slot,
		//we move right
		if(currentSlot->column < column){

			//the current slot now points to the slot one column right
			currentSlot = currentSlot->right;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the current slot is at a column and a row equal to the desired column and row, respectively
		// we found the slot
		if(currentSlot->column == column && currentSlot->row == row){
			printf("Found\n");
			found = true;

		}

	}
	//returns the found slot
	return currentSlot;
}

/*
 * The recursive function that traverses the board to find the slots at a predefined
 * distance from the current slot and place them in foundSlots.
 * Parameters:
 * 	reqDist: the required distance from the starting slot
 * 	currDist: the distance of the current slot from the starting slot
 * 	currSlot: a pointer to the current slot that is traversed
 * 	foundSlots: the array of slots that are at a required distance from the starting slot
 * 	count: pointer to an integer representing the number of slots that are found to be at a required distance from the starting slot
 * 	explored: matrix indicating for each slot at row x and column y has been traversed (true) or not (false)
 */
void findSlots(int reqDist, int currDist,  struct SLOT * currSlot, struct SLOT * foundSlots, int * count,  bool explored[7][7]){



	//The base case: the current slot is at the required distance from the starting slot
	if(currDist == reqDist){
		//the current slot was not explored
		if(explored[currSlot->row][currSlot->column] == false){
			//The next availbale position (indicated by count) at foundSlots points to the current slot
			*(foundSlots + *count) = *currSlot;
			//the counter is incremented
			(*count)++;
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
		}
	}
	//The recursive call: the current slot is at a distance that is less than the required distance (more slots still have to be traversed)
	else{
		//if the current slot has the up slot != NULL (i.e. the slot is not in the first row)
		if(currSlot->up != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the up slot
			findSlots(reqDist, currDist +1,  currSlot->up, foundSlots, count, explored);
		}
		//if the current slot has the right slot != NULL (i.e. the slot is not in the last column)
		if(currSlot->right != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the right slot
			findSlots(reqDist, currDist +1,  currSlot->right, foundSlots, count, explored);
		}
		//if the current slot has the down slot != NULL (i.e. the slot is not in the last row)
		if(currSlot->down != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the down slot
			findSlots(reqDist, currDist +1,  currSlot->down, foundSlots, count, explored);
		}
		//if the current slot has the left slot != NULL (i.e. the slot is not in the first column)
		if(currSlot->left != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the left slot
			findSlots(reqDist, currDist +1,  currSlot->left, foundSlots, count, explored);
		}

	}


}