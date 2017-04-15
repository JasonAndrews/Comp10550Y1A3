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

		gamePlayers[i].alive = 1; // set the player to be alive

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
void nextTurn(unsigned int numSlots, struct SLOT *gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers, struct PLAYER *player, struct SLOT *currSlot) {

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
				completedTurn = attack(gamePlayers, player, numPlayers, currSlot, numSlots);
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
 * 		Finds players to attack depending on specified attack and attacks the player of choice
 *	Parameters:
 *		gamePlayers : struct PLAYER pointer - Pointer to the start of the array of players.
 *		player : struct PLAYER pointer - Pointer to the attacking player.
 *		currSlot : a pointer to the current slot that is traversed.
 * 		numPlayers : uint - The number of players in the game.
 *
 *	Returns:
 *		int - Returns 1 if they completed their move and 0 if they didn't.
 */
int attack(struct PLAYER *gamePlayers, struct PLAYER *player, unsigned int numPlayers, struct SLOT *currSlot, unsigned int boardSize) {

	int
		completeAttack = 0,
		choice,
		attChoice, // player to attack
		count, // number of slots found
		numEnemies; //number of attackable players

	bool
		explored[boardSize][boardSize]; //2-D boolean array used for mapping foundSlot in findSlot()


	size_t  // used in loops
		i,
		j;

	struct SLOT
		*foundSlots;

	struct PLAYER
		**enemy; // array of pointers to pointers of struct PLAYER (enemy -> gamePlayers -> players);

	foundSlots = malloc(boardSize * boardSize * sizeof(struct SLOT ));
	enemy = (struct PLAYER * * const)malloc(sizeof(struct PLAYER) * numPlayers);




	printf("\n%s, your location is row %d, column %d.Please enter \n1)for near attack \n2)for distant attack", player->name, player->row, player->column);

	if(((player->caps.smartness)+(player->caps.magicSkills)) > 150){
		printf("\n3)for magic attack");
	}

	do{
		printf("\nChoice: ");
		fflush(stdin); // flush the stdin buffer
		scanf("%d", &choice);

		//(re)set explored for iteration
		for(i=0; i<boardSize; i++){
			for(j=0; j<boardSize;j++){
				explored[i][j] = false;
			}
		}

		//(re)set counters
		count =0;
		numEnemies=0;

		switch(choice){

			case 1 :
					findSlots(NEAR_ATTACK, 0, currSlot, foundSlots, &count, explored);

					for(i=0; i < count; i++){
						for(j=0; j < numPlayers; j++){
							if((gamePlayers[j].row == foundSlots[i].row) && (gamePlayers[j].column == foundSlots[i].column)){

								enemy[numEnemies]  = &gamePlayers[j];
								numEnemies++;
							}
						}
					}

					if(numEnemies > 0){
						printf("\nYou can attack:");
						for(i=0; i < numEnemies; i++){
							printf("\n%d)%s Life points:%d",i+1, enemy[i]->name, enemy[i]->life_pts);
						}

						printf("Choice: ");
						scanf("%d", &attChoice);

						//the attChoice-1 is to get the right array index
						if(enemy[attChoice-1]->caps.strength <= 70){
							enemy[attChoice-1]->life_pts = enemy[attChoice-1]->life_pts - (0.5 * player->caps.strength);
							completeAttack = 1;
						}
						else if(enemy[attChoice-1]->caps.strength > 70){
							player->life_pts = player->life_pts - (0.3 * enemy[attChoice-1]->caps.strength);
							completeAttack = 1;
						}
					}
					else{
						printf("There is no nearby players.\nPlease choose a different type of attack");
						completeAttack = 0;
					}
				break;

			case 2 :
					findSlots(DISTANT_ATTACK, 0, currSlot, foundSlots, &count, explored);

					//loop through foundSlots and only slots that are not adjacent to the current player slot get to be compared to gamePlayers
					for(i=0; i < count; i++){
						if((foundSlots[i].row != currSlot->row) && (foundSlots[i].column != currSlot->column))

							if((foundSlots[i].row != currSlot->up->row) && (foundSlots[i].column != currSlot->up->column))

								if((foundSlots[i].row != currSlot->down->row) && (foundSlots[i].column != currSlot->down->column))

									if((foundSlots[i].row != currSlot->left->row) && (foundSlots[i].column != currSlot->left->column))

										if((foundSlots[i].row != currSlot->right->row) && (foundSlots[i].column != currSlot->right->column)){

											for(j=0; j < numPlayers; j++){
												if((gamePlayers[j].row == foundSlots[i].row) && (gamePlayers[j].column == foundSlots[i].column)){

													enemy[numEnemies]  = &gamePlayers[j];
													numEnemies++;
												}
											}
										}
					}

					if(numEnemies > 0){
						printf("\nYou can attack:");
						for(i=0; i < numEnemies; i++){
							printf("\n%d)%s Life points:%d",i+1, enemy[i]->name, enemy[i]->life_pts);
						}

						printf("Choice: ");
						fflush(stdin); // flush the stdin buffer
						scanf("%d", &attChoice);

						if(player->caps.dexterity >= enemy[attChoice-1]->caps.dexterity){
							/*nothing happens (attaked player remain unchanged)*/
						}
						else if(player->caps.dexterity > enemy[attChoice-1]->caps.dexterity){
							enemy[attChoice-1]->life_pts -= 0.3 * (player->caps.strength);
						}

						completeAttack = 1;
					}
					else{
						printf("There is no far away players.\nPlease choose a different type of attack");
						completeAttack = 0;
					}
				break;

			case 3:

					if((player->caps.smartness)+(player->caps.magicSkills) > 150){
						printf("\nSorry you are not eligible for this attack.\nYou need the total sum of your smartness and magic skills points to be greater than 150");
						completeAttack = 0;
					}else{

						findSlots(DISTANT_ATTACK, 0, currSlot, foundSlots, &count, explored);

						for(i=0; i < count; i++){
							for(j=0; j < numPlayers; j++){
								if((gamePlayers[j].row == foundSlots[i].row) && (gamePlayers[j].column == foundSlots[i].column)){

									enemy[numEnemies]  = &gamePlayers[j];
									numEnemies++;
								}
							}
						}


						printf("\nYou can attack:");
						for(i=0; i < numEnemies; i++){
							printf("\n%d)%s Life points:%d",i+1, enemy[i]->name, enemy[i]->life_pts);
						}

						printf("Choice: ");
						fflush(stdin); // flush the stdin buffer
						scanf("%d", &attChoice);

						enemy[attChoice]->life_pts -= ((0.5 * player->caps.magicSkills)+(0.2 * player->caps.smartness));

						completeAttack = 1;
					}
				break;

			default:
				printf("\nINVALID CHOICE: Please enter a valid choice");
				completeAttack = 0;

		}//end of switch

	}while(!completeAttack);

	free(enemy);
	free(foundSlots);

	return completeAttack;

}// end of attack() function.


/* Function Name: move
 * Description:
 * 		Implements player movement.
 * 		A player can move in either direction, unless, they are in the first slot (can only go forward) or the last slot (can only go backward)
 *	Parameters:
 *		boardSize : uint - The size of the board.
 * 		gameSlots : struct SLOT pointer - Pointer to the start of the array of slots.
 * 		player : struct PLAYER pointer - Pointer to the taking their player.
 *
 *	Returns:
 *		int - 1 if they completed their move, 0 if they didn't
 */
int move(unsigned int boardSize, struct SLOT *gameSlots, struct PLAYER *player) {


	size_t
		i;

	int
		completedMove = 0;

	unsigned int
		moveChoice;

	printf("\n%s, your location is row %d, column %d. Please select a direction.\n1. Right.\n2. Left.\n3. Up.\n4. Down.\nYour choice: ", player->name, player->row, player->column);
	fflush(stdin); // flush the stdin buffer
	scanf("%d", &moveChoice);

	switch (moveChoice) {

		case 1: {
			// move right
			if (player->column == (boardSize - 1)) {
				printf("Sorry, you cannot move to the right!\n\n");
				break;
			}

			updateCapabilities(gameSlots, player, (player->row * (player->column + 1)));

			player->column++;
			printf("\n%s, you moved rightwards to location row %d, column %d.", player->name, player->row, player->column);

			completedMove = 1;

			break;
		}

		case 2: {
			// move left
			if (player->column == 0) {
				printf("Sorry, you cannot move to the left!\n\n");
				break;
			}

			updateCapabilities(gameSlots, player, (player->row * (player->column - 1)));

			player->column--;
			printf("\n%s, you moved leftwards to location row %d, column %d.", player->name, player->row, player->column);

			completedMove = 1;

			break;
		}
		case 3: {
			// move up
			if (player->row == 0) {
				printf("Sorry, you cannot move upwards!\n\n");
				break;
			}

			updateCapabilities(gameSlots, player, ((player->row - 1) * (player->column)));

			player->row--;
			printf("\n%s, you moved upwards to location row %d, column %d.", player->name, player->row, player->column);

			completedMove = 1;

			break;
		}
		case 4: {
			// move down
			if (player->row == (boardSize - 1)) {
				printf("Sorry, you cannot move downwards!\n\n");
				break;
			}

			updateCapabilities(gameSlots, player, ((player->row + 1) * (player->column)));

			player->row++;
			printf("\n%s, you moved downwards to location row %d, column %d.", player->name, player->row, player->column);

			completedMove = 1;

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

	prevSlotType = gameSlots[(player->row) * (player->column)].slotType;
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


/* Function Name: getTotalAlivePlayers
 * Description:
 * 		This function returns how many players are still alive (i.e. they didn't manually exit or die).
 *	Parameters:
 *		gameSlots : struct PLAYER pointer - Pointer to the start of the array of players.
 *		numStartPlayers : uint - The number of players that started the game.
 *	Returns:
 *		numAlivePlayers : int - the number of players still alive
 */
int getTotalAlivePlayers(unsigned int numStartPlayers, struct PLAYER *gameSlots) {

	size_t
		i;
	int
		numAlivePlayers;

	numAlivePlayers = 0;

	for (i = 0; i < numStartPlayers; i++) {
		if (gameSlots[i].alive == 1)
			numAlivePlayers++;
	}

	return numAlivePlayers;
}


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
