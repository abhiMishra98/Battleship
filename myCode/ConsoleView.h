/*
 * ConsoleView.h
 *
 *  Created on: 02-Jan-2025
 *      Author: abhim
 *
 *       @brief - Class implementation to print the board contents.
 */

#ifndef CONSOLEVIEW_H_
#define CONSOLEVIEW_H_

#include "Board.h"
#include "OwnGrid.h"
#include "OpponentGrid.h"

/**
 * @brief Prints own grid and opponent for a board
 *
 * This class stores the board object.
 */

class ConsoleView: public Board
{
private:
	Board *board;/**<Pointer to the board object*/
public:

	/**
	 * @brief Constructor to create the consoleView and set the initial state
	 *
	 */
	ConsoleView();

	/**
	 * @brief Parameterized constructor to create the consoleView and set the initial state
	 * @param *board - Pointer to a board object of type Board
	 */
	ConsoleView(Board &board);

	/**
	 * @brief method to print the grids
	 *
	 */
	void printGrids();

	/**
	 * @brief destructor to deallocate memory(if created any)
	 *
	 */
	virtual ~ConsoleView();
};

#endif /* CONSOLEVIEW_H_ */
