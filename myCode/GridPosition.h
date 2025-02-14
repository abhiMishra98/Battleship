/*
 * GridPosition.h
 *
 *  Created on: 26-Dec-2024
 *      Author: abhim
 *
 * @brief - Class implementation for the grids of the board
 */

#ifndef GRIDPOSITION_H_
#define GRIDPOSITION_H_

#include <string>

/**
 * @brief Constitutes the whole grid(opponent and own grid)
 *
 * This class is used to refer to one single grid position on the board
 */

class GridPosition
{
private:
	char row;/**<row position of the grid*/
	int column;/**<column position of the grid*/
public:

	/**
	 * @brief Constructor to create a grid position on the board
	 */
	GridPosition();

	/**
	 * @brief Parameterized constructor to create a grid position on the board
	 * @param rows - row position of the grid
	 * @param columns - column position of the grid
	 */
	GridPosition(char rows, int columns);

	/**
	 * @brief Copy constructor to create a grid position on the board
	 * @param other - Object of type GridPosition
	 */
	GridPosition(const GridPosition &other);

	/**
	 * @brief copy assignment operator to create a grid position on the board
	 * @param orig -object of type GridPosition
	 */
	GridPosition& operator=(const GridPosition &orig);

	/**
	 * @brief Move constructor to create a grid position on the board
	 * @param source -object of type GridPosition
	 */
	GridPosition(GridPosition &&source);

	/**
	 * @brief Move assignment operator to create a grid position on the board
	 * @param orig -object of type GridPosition
	 */
	GridPosition& operator=(GridPosition &&source);

	/**
	 * @brief Parameterized constructor to create a grid position on the board
	 * @param position - position of the grid on the board
	 */
	GridPosition(std::string position);

	/**
	 * @brief checks if an entered grid is valid or not
	 */
	bool isValid();

	/**
	 * @brief getter method to get the row position of a grid
	 */
	char getRow() const;

	/**
	 * @brief getter method to get the column position of a grid
	 */
	int getColumn() const;

	/**
	 * @brief overloading the string operator
	 */
	operator std::string();

	/**
	 * @brief overloading the '==' operator to check if two grid positions are equal or not
	 * @param other - reference to a GridPosition object
	 */
	bool operator==(const GridPosition &other) const;

	/**
	 * @brief overloading the '<' operator to compare two grid positions
	 * @param other - reference to a GridPosition object
	 */
	bool operator<(const GridPosition &other) const;

	virtual ~GridPosition();

	/**
	 * @brief overloading the '<<' operator to print grid positions
	 * @param pos - reference to a GridPosition object
	 * @param os - reference to std::ostream object
	 */
	friend std::ostream& operator<<(std::ostream &os, const GridPosition &pos);
};

#endif /* GRIDPOSITION_H_ */
