/*
 * OwnGrid.h
 *
 *  Created on: 01-Jan-2025
 *      Author: abhim
 *@brief -  This class is used to represent the player's own grid on the board
 */

/**
 * OPTIMIZATIONS
 *
 * 1) Check the usage of other pointers instead of the standard pointer.
 */

/**
 * @brief Constitutes of the player's own grid on the board
 *
 * This class is used to represent the player's own grid on the board
 */

#ifndef OWNGRID_H_
#define OWNGRID_H_
#include "Ship.h"
#include "Shot.h"
#include <vector>
#include <map>

class OwnGrid: public Ship
{
private:
	int rows;/**<number of rows of the player's own board*/
	int columns;/**<number of columns of the player's own board*/
	char *m_oGrid;/**<pointer to the player's own board*/
	std::set<Ship> ships;/**<set of type Ship*/
	std::set<GridPosition> shotAt;
	std::map<int, int> shipDetails = /**<Map of type int,int to store player's own ship details*/
	{
	{ 5, 1 },  // Carrier: Length 5, 1 ship
			{ 4, 2 },  // Battleship: Length 4, 2 ships
			{ 3, 3 },  // Destroyer: Length 3, 3 ships
			{ 2, 4 }   // Submarine: Length 2, 4 ships
	};
	static const int immediateCellDirections[8][2]; /**<Static array to store the offset in 8 directions. */
public:

	/**
	 * @brief Constructor to create a grid of player's own board
	 */
	OwnGrid();

	/**
	 * @brief Parameterized constructor to create a grid of player's own board
	 * @param rows - rows of the board
	 * @param columns - columns of the board
	 */
	OwnGrid(int rows, int columns);

	/**
	 * @brief Copy constructor to create a grid of player's own board
	 * @param other - Object of type ownGrid
	 */
	OwnGrid(const OwnGrid &other);

	/**
	 * @brief Copy assignment to create a grid of player's own board
	 * @param orig - Object of type OwnGrid
	 */
	OwnGrid& operator=(const OwnGrid &orig);

	/**
	 * @brief Move constructor to create a grid of player's own board
	 * @param source - Object of type ownGrid
	 */
	OwnGrid(OwnGrid &&source);

	/**
	 * @brief Move assignment to create a grid of player's own board
	 * @param source - Object of type OwnGrid
	 */
	OwnGrid& operator=(OwnGrid &&source);

	/**
	 * @brief getter method to get the number of rows of the board
	 */
	int getRows();

	/**
	 * @brief getter method to get the number of columns of the board
	 */
	int getColumns();

	/**
	 * @brief method to determine the equivalent number value of a character
	 * @param row - row of the board
	 */
	int charToNumber(char row);

	/**
	 * @brief method to convert a number back to the equivalent row value
	 * @param rowNumber - row of the board
	 */
	char numberToChar(int rowNumber);

	/**
	 * @brief method to determine the nearby blocked positions to a ship where other ships can't be placed
	 * @param row - row of the board
	 * @param column - column of the board
	 * @param ship - Object of type ship
	 */
	void checkNearbyCells(char row, int column, Ship &ship);

	/**
	 * @brief getter method to own grid
	 */
	char* rtrnGrid();

	/**
	 * @brief method to convert a grid obejct to equivalent index
	 * @param shot - Object of type Shot
	 */
	int gridObjToIndex(const Shot &shot);

	/**
	 * @brief method to check if two ships are not in each other's blocked area
	 * @param ship - Object of type Ship
	 */
	bool shipNoTouch(Ship &ship);

	/**
	 * @brief method to place the ship in the grid
	 * @param ship - Object of type Ship
	 */
	bool placeShip(Ship &&ship);

	/**
	 * @brief method to get the set of all ships placed on the board.
	 */
	std::set<Ship> getShips();

	/**
	 * @brief method to return if a shot has hit a ship or not
	 * @param shot - Object of type Shot
	 */
	Shot::Impact takeBlow(const Shot &shot);

	/**
	 * @brief getter function to return the list of positions where shots have been fired
	 */
	std::set<GridPosition> getShotAt() ;

	/**
	 * @brief setter function to make a shot at a grid position
	 */
	void setShotAt(const Shot &shot);

	/**
	 * @brief getter function to get the ship details
	 */
	std::map<int, int> getShipDetails();

	/**
	 * @brief method to print the ship details
	 */
	void printShipDetails();

	/**
	 * @brief method to check if the shot falls on the grid
	 */
	int checkShotBounds(const Shot &shot);

	virtual ~OwnGrid();
};

#endif /* OWNGRID_H_ */
