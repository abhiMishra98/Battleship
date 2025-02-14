/*
 * Board.cpp
 *
 *  Created on: 01-Jan-2025
 *      Author: abhim
 */

#include "Board.h"

Board::Board()
{
	// TODO Auto-generated constructor stub
	rowsBoard = 0;
	columnsBoard = 0;
}

Board::Board(int rowsOfBoard, int columnsOfBoard) :
		rowsBoard
		{ rowsOfBoard }, columnsBoard
		{ columnsOfBoard }, ownGrid
		{ rowsOfBoard, columnsOfBoard }, opponentGrid
		{ rowsOfBoard, columnsOfBoard }
{

}

Board::Board(const Board &orig) :
		rowsBoard
		{ orig.rowsBoard }, columnsBoard
		{ orig.columnsBoard }, ownGrid
		{ orig.ownGrid }, opponentGrid
		{ orig.opponentGrid }
{
}

Board::Board(Board &&source) :
		rowsBoard
		{ source.rowsBoard }, columnsBoard
		{ source.columnsBoard }
{
	source.rowsBoard = 0;
	source.columnsBoard = 0;
}

Board& Board::operator =(Board &&source)
{
	rowsBoard = std::move(source.rowsBoard);
	columnsBoard = std::move(source.columnsBoard);
	source.rowsBoard = 0;
	source.columnsBoard = 0;
	return *this;
}

int Board::getRows()
{
	return rowsBoard;
}

int Board::getColumns()
{
	return columnsBoard;
}

OwnGrid& Board::getOwnGrid()
{
	return ownGrid;
}

OpponentGrid& Board::getOpponentGrid()
{
	return opponentGrid;
}

Board& Board::operator =(const Board &orig)
{
	rowsBoard = orig.rowsBoard;
	columnsBoard = orig.columnsBoard;
	ownGrid = orig.ownGrid;
	opponentGrid = orig.opponentGrid;
	std::cout << "Copy assignment called from Board.h" << std::endl;
	return *this;
}

Board::~Board()
{
	// TODO Auto-generated destructor stub
}

