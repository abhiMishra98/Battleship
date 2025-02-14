/*
 * Ship.cpp
 *
 *  Created on: 26-Dec-2024
 *      Author: abhim
 */

#include "Ship.h"

/** OPTIMIZATIONS
 * 1) Optimise the function isValid(); Reduce the number of lines.
 * 3) Change the logic for determining the alphabet and the numbers. It is now working for 3 characters.
 */

Ship::Ship()
{

}

Ship::Ship(std::string bowEntry, std::string sternEntry) :
		bow
		{ bowEntry }, stern
		{ sternEntry }
{
	if (!isValid())
	{
		// Handle invalid case (e.g., throw an exception, set default values, etc.)
		std::cout << "Invalid Ship placement" << std::endl;
	}
}

Ship::Ship(const Ship &orig) :
		bow
		{ orig.bow }, stern
		{ orig.stern }, occupiedGridPosn
		{ orig.occupiedGridPosn }, blockedGridPosn
		{ orig.blockedGridPosn }, shotsTaken
		{ orig.shotsTaken }
{

}

Ship& Ship::operator=(const Ship &orig)
{
	bow = orig.bow;
	stern = orig.stern;
	occupiedGridPosn = orig.occupiedGridPosn;
	blockedGridPosn = orig.blockedGridPosn;
	shotsTaken = orig.shotsTaken;
	return *this;
}

Ship::Ship(Ship &&source) :
		bow(std::move(source.bow)), stern(std::move(source.stern)), occupiedGridPosn(
				std::move(source.occupiedGridPosn)), blockedGridPosn(
				std::move(source.blockedGridPosn)), shotsTaken(
				std::move(source.shotsTaken))
{
	source.bow = GridPosition();
	source.stern = GridPosition();

}

Ship& Ship::operator =(Ship &&source)
{
	bow = std::move(source.bow);
	stern = std::move(source.stern);
	occupiedGridPosn = std::move(source.occupiedGridPosn);
	blockedGridPosn = std::move(source.blockedGridPosn);
	shotsTaken = std::move(source.shotsTaken);
	return *this;
}

bool Ship::isValid()
{
	std::string bowString = bow;
	std::string sternString = stern;
	unsigned short enteredRowBow = (char) (bowString[0]);
	unsigned short enteredColumnBow = atoi(bowString.substr(1).c_str());
	unsigned short enteredRowStern = (char) (sternString[0]);
	unsigned short enteredColumnStern = atoi(sternString.substr(1).c_str());
	unsigned short diffRow = abs(enteredRowBow - enteredRowStern) + 1;
	unsigned short diffCol = abs(enteredColumnBow - enteredColumnStern) + 1;
	if (enteredRowBow == enteredRowStern) //Horizontal
	{
		if (diffCol >= 2 && diffCol <= 5)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (enteredColumnBow == enteredColumnStern) //Vertical
	{
		if (diffRow >= 2 && diffRow <= 5)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}

GridPosition Ship::getBow()
{
	return bow;
}

GridPosition Ship::getStern()
{
	return stern;
}

int Ship::length()
{
	std::string bowString = bow;
	std::string sternString = stern;
	unsigned short enteredRowBow = (char) (bowString[0]);
	unsigned short enteredColumnBow = atoi(bowString.substr(1).c_str());
	unsigned short enteredRowStern = (char) (sternString[0]);
	unsigned short enteredColumnStern = atoi(sternString.substr(1).c_str());
	if (enteredRowBow == enteredRowStern) //Horizontal
	{
		return abs(enteredColumnBow - enteredColumnStern) + 1; //1 added to include the first grid also
	}
	else if (enteredColumnBow == enteredColumnStern) //Vertical
	{
		return abs(enteredRowBow - enteredRowStern) + 1; //1 added to include the first grid also
	}
	else
	{
		return -1;
	}
}

std::set<GridPosition> Ship::occupiedArea(GridPosition constGridPosition)
{
	occupiedGridPosn.insert(constGridPosition);
	return occupiedGridPosn;
}

std::set<GridPosition> Ship::blockedArea(GridPosition constGridPosition)
{
	blockedGridPosn.insert(constGridPosition);
	return blockedGridPosn;
}

int Ship::charToNumber(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		return ch - 'A';
	}
	else
	{
		return -1; // Invalid character
	}
}

std::ostream& operator<<(std::ostream &lhs, const std::set<GridPosition> &rhs)
{
	lhs << "{";    // Start with the curly braces
	for (const auto &pos : rhs)
	{
		lhs << " " << pos;
	}
	lhs << " }";    // End with curly braces
	return lhs;
}

Ship::~Ship()
{
	// TODO Auto-generated destructor stub
}

std::set<GridPosition> Ship::getOccupiedArea() const
{
	return occupiedGridPosn;
}

std::set<GridPosition> Ship::getBlockedArea() const
{
	return blockedGridPosn;
}

void Ship::addShots(GridPosition shots)
{
	shotsTaken.insert(shots);
}

std::set<GridPosition> Ship::getShotsMade()
{
	return shotsTaken;
}

bool Ship::operator<(const Ship &other) const
{
	return this->bow < other.bow
			|| (this->bow == other.bow && this->stern < other.stern);
}

