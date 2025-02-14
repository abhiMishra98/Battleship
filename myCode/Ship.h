/*
 * Ship.h
 *
 *  Created on: 26-Dec-2024
 *      Author: abhim
 *      @brief - This class is used to represent all the ships present in the game battleship
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "GridPosition.h"
#include <iostream>
#include <set>

/**
 * @brief Constitutes of how ships are arranged ship on the board
 *
 * This class is used to represent the different ships at their different grid positions
 */

class Ship: public GridPosition
{
private:
	GridPosition bow;/**<bow of the ship of type grid position*/
	GridPosition stern;/**<stern of the ship of type grid position*/
	std::set<GridPosition> occupiedGridPosn;/**<set of type grid position for storing the occupied grid positions by the ship*/
	std::set<GridPosition> blockedGridPosn;/**<set of type grid position for storing the blocked grid positions by the ship*/
	std::set<GridPosition> shotsTaken;/**<set of type grid position for storing the shots aimed at the ship*/
public:

	/**
	 * @brief Constructor to create a ship
	 */
	Ship();

	/**
	 * @brief Constructor to create a ship with a given bow and a stern
	 */
	Ship(std::string bowEntry, std::string sternEntry);

	/**
	 * @brief - Copy constructor to create a ship with a bow and stern
	 * @param orig - object of type Ship
	 */
	Ship(const Ship &orig);

	/**
	 * @brief - Copy assignment operator to create a ship with a bow and stern
	 * @param orig - Object of type Ship
	 */
	Ship& operator=(const Ship &orig);

	/**
	 * @brief - Move constructor to create a ship with a bow and stern
	 * @param source - object of type Ship
	 */
	Ship(Ship &&source);

	/**
	 * @brief - Move assignment operator to create a ship with a bow and stern
	 * @param source - Object of type Ship
	 */
	Ship& operator=(Ship &&source);
	/**
	 * @brief method to check if a ship is valid or not
	 */
	bool isValid();

	/**
	 * @brief getter method to fetch the bow of the ship
	 */
	GridPosition getBow();

	/**
	 * @brief getter method to fetch the stern of the ship
	 */
	GridPosition getStern();

	/**
	 * @brief method to determine the length of the ship
	 */
	int length();

	/**
	 * @brief method to fetch the equivalent number value to a character
	 * @param ch - char input value
	 */
	int charToNumber(char ch);

	/**
	 * @brief method to add shots to the set shotsTaken
	 * @param shots - shots of type GridPosition
	 */
	void addShots(GridPosition shots);

	/**
	 * @brief getter method to return the number of shots made
	 */
	std::set<GridPosition> getShotsMade();

	/**
	 * @brief method to return the set of grid positions occupied by the ship
	 * @param constGridPosition - object of type GridPosition , used to add grids occupied by the ship one by one
	 */
	std::set<GridPosition> occupiedArea(GridPosition constGridPosition);

	/**
	 * @brief method to return the set of grid positions blocked by the ship
	 * @param constGridPosition - object of type GridPosition , used to add grids blocked by the ship one by one
	 */
	std::set<GridPosition> blockedArea(GridPosition constGridPosition);

	/**
	 * @brief getter method to fetch the occupied grid positions of the ship
	 */
	std::set<GridPosition> getOccupiedArea() const;

	/**
	 * @brief getter method to fetch the blocked grid positions of the ship
	 */
	std::set<GridPosition> getBlockedArea() const;

	/**
	 * @brief operator overloading for comparing between two ship positions
	 */
	bool operator<(const Ship &other) const;

	virtual ~Ship();
};

/**
 * @brief overloaded "<<" operator to print the grid positions
 */

std::ostream& operator<<(std::ostream &lhs, const std::set<GridPosition> &rhs);

#endif /* SHIP_H_ */
