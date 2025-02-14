/*
 * Board.h
 *
 *  Created on: 01-Jan-2025
 *      Author: abhim
 *
 *      @brief - Class implementation to manage the board contents.
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "OwnGrid.h"
#include "OpponentGrid.h"

/**
 * @brief Represents a game board of battleship for a player.
 *
 * This class stores the row and column numbers and has own grid and opponent's grid.
 */

class Board
{
private:
	int rowsBoard;/**<Rows of the board*/
	int columnsBoard;/**<Columns of the board*/
	OwnGrid ownGrid;/**< Own grid object "ownGrid"*/
	OpponentGrid opponentGrid;/**< Opponent grid object "opponentGrid"*/
public:
	/**
	 * @brief Constructor to create the board and set the initial state.
	 *
	 */

	Board();

	/**
	 * @brief Parameterized constructor to create the board and set the initial state.
	 * @param rows - Number of rows of the board.
	 * @param columns - Number of columns of the board.
	 */
	Board(int rows, int columns);

	/**
	 * @brief Copy constructor to create the board and set the initial state.
	 * @param board - Object of type Board
	 */
	Board(const Board &orig);

	/**
	 * @brief Copy assignment operator to create the board and set the initial state.
	 * @param orig - Object of type Board
	 */
	Board& operator=(const Board &orig);

	/**
	 * @brief Move constructor to create the board and set the initial state.
	 * @param source - Object of type Board
	 */
	Board(Board &&source);

	/**
	 * @brief Move assignment operator to create the board and set the initial state.
	 * @param source - Object of type Board
	 */
	Board& operator=(Board &&source);

	/**
	 * @brief getter method to fetch the number of rows of the board.
	 */
	int getRows();

	/**
	 * @brief getter method to fetch the number of columns of the board.
	 */
	int getColumns();

	/**
	 * @brief method to return a reference to the ownGrid.
	 */
	OwnGrid& getOwnGrid();

	/**
	 * @brief method to return a reference to the opponentGrid.
	 */

	OpponentGrid& getOpponentGrid();
	virtual ~Board();
};

#endif /* BOARD_H_ */
