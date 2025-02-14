/*
 * ConsoleView.cpp
 *
 *  Created on: 02-Jan-2025
 *      Author: abhim
 */

#include "ConsoleView.h"

ConsoleView::ConsoleView()
{
	// TODO Auto-generated constructor stub

}

ConsoleView::ConsoleView(Board &board) :
		board
		{ &board }
{

}

void ConsoleView::printGrids()
{
	std::cout <<std::endl;

	// Get grids and dimensions
	OwnGrid &ownGrid = board->getOwnGrid();
	OpponentGrid &opponentGrid = board->getOpponentGrid();
	int gridRows = board->getRows();
	int gridCols = board->getColumns();

	// Print headers for both grids
	std::cout << "  Own Grid";
	for (int i = 0; i < gridCols * 2; i++)
		std::cout << " ";  // Adjust spacing
	std::cout << "Opponent Grid" << std::endl;

	// Print tens digit header for both grids
	std::cout << "  ";
	for (int col = 1; col <= gridCols; col++)
	{
		if (col < 10)
			std::cout << "  ";
		else
			std::cout << "1 ";
	}
	std::cout << "     ";  // Add space between grids
	for (int col = 1; col <= gridCols; col++)
	{
		if (col < 10)
			std::cout << "  ";
		else
			std::cout << "1 ";
	}
	std::cout << std::endl;

	// Print ones digit header for both grids
	std::cout << "  ";
	for (int col = 1; col <= gridCols; col++)
	{
		std::cout << col % 10 << " ";
	}
	std::cout << "     ";  // Add space between grids
	for (int col = 1; col <= gridCols; col++)
	{
		std::cout << col % 10 << " ";
	}
	std::cout << std::endl;

	// Print both grids row by row
	for (int row = 0; row < gridRows; row++)
	{
		// Print row label
		char rowLabel = 'A' + row;
		std::cout << rowLabel << " ";

		// Print own grid row
		for (int col = 0; col < gridCols; col++)
		{
			std::cout << ownGrid.rtrnGrid()[row * gridCols + col] << " ";
		}

		// Add space between grids
		std::cout << "    ";

		// Print opponent grid row
		std::cout << rowLabel << " ";
		for (int col = 0; col < gridCols; col++)
		{
			std::cout << opponentGrid.rtrnGridOpponent()[row * gridCols + col]
					<< " ";
		}

		// Move to the next line
		std::cout << std::endl;
	}
}

ConsoleView::~ConsoleView()
{
	// TODO Auto-generated destructor stub
}

