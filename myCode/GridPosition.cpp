/*
 * GridPosition.cpp
 *
 *  Created on: 26-Dec-2024
 *      Author: abhim
 */

#include "GridPosition.h"
#include <iostream>

/** OPTIMIZATIONS
 * 2) Improvise the gridPosition constructor.
 */

GridPosition::GridPosition()
{

}

GridPosition::GridPosition(char rows, int columns)
{
	row = rows;
	column = columns;
	if (!isValid())
	{
		std::cout << "Invalid Grid Position!" << std::endl;
	}
}

GridPosition::GridPosition(std::string position)
{
	row = position[0];
	column = atoi(position.substr(1).c_str());
	if (!isValid())
	{
		std::cout << "Invalid Grid Position!" << std::endl;
	}
}

GridPosition::GridPosition(const GridPosition &other)
{
	row = other.row;
	column = other.column;
}

GridPosition& GridPosition::operator =(const GridPosition &orig)
{
	row = orig.row;
	column = orig.column;
	return *this;
}

GridPosition::GridPosition(GridPosition &&source) :
		row
		{ source.row }, column
		{ source.column }
{
	source.row = 0;
	source.column = 0;
}

GridPosition& GridPosition::operator =(GridPosition &&source)
{
	row = std::move(source.row);
	column = std::move(source.column);
	source.row = 0;
	source.column = 0;
	return *this;
}

bool GridPosition::isValid()
{
	std::string positionString = std::string(1, row) + std::to_string(column);
	int enteredRow = (char) (positionString[0]);
	int enteredColumn = atoi(positionString.substr(1).c_str());

	if ((enteredRow >= 65 && enteredRow <= 90) && enteredColumn > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char GridPosition::getRow() const
{
	return row;
}

int GridPosition::getColumn() const
{
	return column;
}

GridPosition::operator std::string()
{
	return std::string(1, row) + std::to_string(column);
}

bool GridPosition::operator ==(const GridPosition &other) const
{
	if (row == other.row && column == other.column)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GridPosition::operator <(const GridPosition &other) const
{
	if (row < other.row)
	{
		return true;
	}
	else if (row == other.row)
	{
		return column < other.column;
	}
	else
	{
		return false;
	}
}

std::ostream& operator<<(std::ostream &os, const GridPosition &pos)
{
	os << pos.getRow() << pos.getColumn(); // or whatever representation you want
	return os;
}

GridPosition::~GridPosition()
{
	// TODO Auto-generated destructor stub
}

