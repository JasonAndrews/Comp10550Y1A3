/*
 ============================================================================
 Name        :	game_definitions.h
 Authors     :
				Jason Andrews
				Jeremiah Wangaruro

 Version     : 	0.1
 Description : 	This header file contains all the necessary definitions
				for implementing the functionality of the game, such as enums
				and define directives.
 ============================================================================
*/

// definitions
#ifndef 	GAME_DEFS_H_
#define 	GAME_DEFS_H_


#define 	MAX_COLUMN_SIZE		100 // the max column size of each string in the 2D arrays

#define 	EXIT_APPLICATION	'x' // the character required for the main menu loop to break

#define 	MIN_BOARD_SIZE		2
#define 	MAX_BOARD_SIZE		7



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

	char
		name[20]; // name of the player

	enum
		PLAYER_TYPES playerType; // the player type

	int
		life_pts, // life points
		alive, // the player's status - 0 if dead or if they exited, 1 if active and alive
		row, // the row that the player is on within the board
		column; // the column that the player is on within the board

	struct
		PLAYER_CAPABILITIES caps; // the player's capabilities - see the PLAYER_CAPABILITIES struct above
};

/*
* This struct will be used to store
* information about each slot
*/
struct SLOT {

	int
		row, // row number
		column; // column number

	struct SLOT
		*left, // adjacent left slot
		*right, // adjacent right slot
		*up, // adjacent above slot
		*down; // adjacent below slot

	enum SLOT_TYPES
		slotType;

};


#endif /* GAME_DEFS_H_*/
