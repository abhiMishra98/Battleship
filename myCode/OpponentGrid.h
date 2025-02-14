/*
 * OpponentGrid.h
 *
 *  Created on: 26-Dec-2024
 *      Author: abhim
 * @brief - Class implementation for the opponent grid in the board
 */

#ifndef OPPONENTGRID_H_
#define OPPONENTGRID_H_
#include "Ship.h"
#include "Shot.h"
#include <map>

/**
 * @brief Constitutes of the opponent grid on the board
 *
 * This class is used to represent the opponent grid on the board
 */

class OpponentGrid: public Ship
{
private:
	int rows;/**<number of rows of the opponent board*/
	int columns;/**<number of columns of the opponent board*/
	char *m_oppBoard;/**<pointer to the opponent board*/
	std::set<Ship> sunkenShips;/**<Set of type Ship*/

	std::map<GridPosition, Shot::Impact> shots;/**<Map of type gridPosition, Shot::Impact to store details on the shots and it's impact*/
	std::map<int, int> oppShipDetails = /**<Map of type int,int to store opponent's ship details*/
	{
	{ 5, 0 },  // Carrier: Length 5, 1 ship
			{ 4, 0 },  // Battleship: Length 4, 2 ships
			{ 3, 0 },  // Destroyer: Length 3, 3 ships
			{ 2, 0 }   // Submarine: Length 2, 4 ships
	};
	std::set<Ship> oppShips;/**<Set of type ship to store details on the opponent's ships*/
public:

	/**
	 * @brief Constructor to create a grid of opponent grid board
	 */
	OpponentGrid();

	/**
	 * @brief Parameterized constructor to create a grid of opponent grid board
	 * @param rowEntry - number of rows of the opponent grid on the board
	 * @param colEntry - number of columns of the opponent grid on the board
	 */
	OpponentGrid(int rowEntry, int colEntry);

	/**
	 * @brief Copy constructor to create a grid of opponent grid board
	 * @param orig - Object of type OpponentGrid
	 */
	OpponentGrid(const OpponentGrid &other);

	/**
	 * @brief Copy assignment operator to create a grid of opponent grid board
	 * @param orig - Object of type OpponentGrid
	 */
	OpponentGrid& operator=(const OpponentGrid &orig);

	/**
	 * @brief Move constructor to create a grid of opponent grid board
	 * @param source - Object of type OpponentGrid
	 */
	OpponentGrid(OpponentGrid &&source);

	/**
	 * @brief Move assignment operator to create a grid of opponent grid board
	 * @param source - Object of type OpponentGrid
	 */
	OpponentGrid& operator=(OpponentGrid &&source);

	/**
	 * @brief Getter method to fetch the number of rows of the opponent grid
	 */
	int getRows() const;

	/**
	 * @brief Getter method to fetch the number of columns of the opponent grid
	 */
	int getColumns() const;

	/**
	 * @brief method to store the result of the shot made on the opponent grid.
	 * @param shot - Reference to an object of type shot storing details on the grid position where shot was made
	 * @param impact - stores the result whether the shot hits a ship or not
	 */
	Shot::Impact shotResult(const Shot &shot, Shot::Impact impact);

	/**
	 * @brief method to store opponent ships
	 * @param opponentShips - set of type Ship
	 */
	void storeOpponentShips(std::set<Ship> opponentShips);

	/**
	 * @brief method to check if a ship is present at a grid position or not
	 * @param shotPosition - object of type GridPosition
	 */
	Ship getOpponentShip(GridPosition shotPosition);

	/**
	 * @brief method to determine the total number of ships of the opponent
	 */
	void getOpponentTotShipDetails() const;

	/**
	 * @brief method to decrement the ships which sunk
	 * @param ship - Object of type ship which is sunk
	 */
	void updateOpponentShipDetails(Ship &ship);

	/**
	 * @brief method to return the opponent grid
	 */
	char* rtrnGridOpponent();

	/**
	 * @brief method to convert a grid object to it's equivalent index value
	 * @param shot - Object of type shot
	 */
	int gridObjToIndex(const Shot &shot);

	/**
	 * @brief getter method to return a set of shots fired at the grid
	 */
	const std::map<GridPosition, Shot::Impact>& getShotsAt() const;

	/**
	 * @brief setter method to insert the shots fired
	 * @param shot - Object of type GridPosition
	 * @param Shot::Impact - Enum value storing the impact on the grid
	 */
	void setShotsAt(const GridPosition &shot, Shot::Impact);

	/**
	 * @brief method to convert the whole ship to a sunken ship after the last shot hitting it
	 * @param shot - Object of type GridPosition
	 */
	void convertToSunkenShip(const Shot &shot);

	virtual ~OpponentGrid();
};

#endif /* OPPONENTGRID_H_ */
