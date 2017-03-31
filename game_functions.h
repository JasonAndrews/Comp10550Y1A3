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

#define 	MAX_COLUMN_SIZE		100 // the max column size of each string in the 2D arrays

#define 	EXIT_APPLICATION	'x' // the character required for the main menu loop to break

#define 	MIN_NUM_OF_SLOTS	2
#define 	MAX_NUM_OF_SLOTS	20

#define 	MAX_PTS				100

#define 	MIN_PLAYERS			2
#define 	MAX_PLAYERS			6

#define 	TOTAL_SLOT_TYPES	3


// values are assigned by default from ranging from 0 to 3 (Elf=0, Human=1, etc.)
enum PLAYER_TYPES {
	ELF,
	HUMAN,
	OGRE,
	WIZARD
};

// The different types available for a slot
enum SLOT_TYPES {
	LEVEL_GROUND = 1,
	HILL = 2,
	CITY = 3	
};

/*
* This struct will be used to store	
* information about each player's capabilities
*/
struct PLAYER_CAPABILITIES {
	int 
		smartness,
		strength,
		magicSkills,
		luck,
		dexterity;
};

/*
* This struct will be used to store	
* information about each player
*/
struct PLAYER {
	char name[20]; // name of the player
	enum PLAYER_TYPES playerType; // the player type
	int life_pts; // life points 
	struct PLAYER_CAPABILITIES caps; // the player's capabilities - see the PLAYER_CAPABILITIES struct above
	int position; // the player's position in the slot array (zero based as it's an array)
};

/*
* This struct will be used to store	
* information about each slot
*/
struct SLOT {
	struct PLAYER *player;
	enum SLOT_TYPES slotType;
};

// function prototypes
void setupSlots(unsigned int numPlayers, unsigned int numSlots, struct SLOT *gameSlots);
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




#endif /* GAME_FUNCTIONS_H_*/