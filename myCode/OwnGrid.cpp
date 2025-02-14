/*
 * OwnGrid.cpp
 *
 *  Created on: 01-Jan-2025
 *      Author: abhim
 */

#include "OwnGrid.h"
#include <set>
#include <algorithm>
#include <iomanip>

const int OwnGrid::immediateCellDirections[8][2] =
{
{ -1, 0 },  // Up
		{ 1, 0 },   // Down
		{ 0, -1 },  // Left
		{ 0, 1 },   // Right
		{ -1, -1 }, // Up-left (diagonal)
		{ -1, 1 },  // Up-right (diagonal)
		{ 1, -1 },  // Down-left (diagonal)
		{ 1, 1 }    // Down-right (diagonal)
};

OwnGrid::OwnGrid()
{
	// TODO Auto-generated constructor stub

}

OwnGrid::OwnGrid(int rows, int columns) :
		rows
		{ rows }, columns
		{ columns }
{
	m_oGrid = new char[rows * columns];
	for (unsigned short index = 0; index < (rows * columns); index++)
	{
		m_oGrid[index] = '~';
	}

}

OwnGrid::OwnGrid(const OwnGrid &other) :
		rows
		{ other.rows }, columns
		{ other.columns }, ships
		{ other.ships }, shotAt
		{ other.shotAt }, shipDetails
		{ other.shipDetails }
{
	m_oGrid = new char[rows * columns];
	for (unsigned short index = 0; index < (rows * columns); index++)
	{
		m_oGrid[index] = other.m_oGrid[index];
	}
}

OwnGrid& OwnGrid::operator =(const OwnGrid &orig)
{
	delete[] m_oGrid;
	rows = orig.rows;
	columns = orig.columns;
	ships = orig.ships;
	shotAt = orig.shotAt;
	shipDetails = orig.shipDetails;
	m_oGrid = new char[rows * columns];
	for (unsigned short index = 0; index < (rows * columns); index++)
	{
		m_oGrid[index] = orig.m_oGrid[index];
	}
	return *this;
}

OwnGrid::OwnGrid(OwnGrid &&source) :
		rows
		{ source.rows }, columns
		{ source.columns }, m_oGrid
		{ source.m_oGrid }, ships
		{ std::move(source.ships) }, shotAt
		{ std::move(source.shotAt) }, shipDetails
		{ std::move(source.shipDetails) }
{
	source.rows = 0;
	source.columns = 0;
	source.m_oGrid = nullptr;
	source.ships.clear();
	source.shotAt.clear();
	source.shipDetails.clear();
}

OwnGrid& OwnGrid::operator =(OwnGrid &&source)
{
	// Free existing memory to prevent leaks
	delete[] m_oGrid;

	// Transfer ownership of resources
	rows = source.rows;
	columns = source.columns;
	m_oGrid = source.m_oGrid;
	ships = std::move(source.ships);
	shotAt = std::move(source.shotAt);
	shipDetails = std::move(source.shipDetails);

	// Nullify the source object's resources
	source.rows = 0;
	source.columns = 0;
	source.m_oGrid = nullptr;
	return *this;
}

void OwnGrid::checkNearbyCells(char row, int column, Ship &ship)
{
	int rowTemp, columnTemp;
	rowTemp = charToNumber(row);
	columnTemp = column;
	for (int i = 0; i < 8; ++i)
	{
		int newRow = rowTemp + OwnGrid::immediateCellDirections[i][0];
		int newCol = columnTemp + OwnGrid::immediateCellDirections[i][1];

		// Ensure the new position is within bounds
		if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns)
		{
			char newRowChar = numberToChar(newRow); // Convert row number to letter
			int newColOneBased = newCol + 1;    // Convert back to 1-based index
			GridPosition gridObj
			{ newRowChar, newColOneBased };

			// If the cell is free, add it to the blocked area
			if (m_oGrid[newRow * columns + newCol] == '~')
			{
				ship.blockedArea(gridObj);
			}
		}
	}
}

bool OwnGrid::shipNoTouch(Ship &ship)
{
	const std::set<GridPosition> &newShipOccupiedPosn = ship.getOccupiedArea();
	for (auto &existingShip : ships)
	{
		const std::set<GridPosition> &placedShipBlockedPosn =
				existingShip.getBlockedArea();

		// Check for intersection
		std::set<GridPosition> intersectionSet;
		std::set_intersection(newShipOccupiedPosn.begin(),
				newShipOccupiedPosn.end(), placedShipBlockedPosn.begin(),
				placedShipBlockedPosn.end(),
				std::inserter(intersectionSet, intersectionSet.begin()));

		// If any intersection is found, return false
		if (!intersectionSet.empty())
		{
			return false;
		}
	}

	// No intersection found with any ship
	return true;
}

Shot::Impact OwnGrid::takeBlow(const Shot &shot)
{
	std::set<Ship>::iterator itr;
	GridPosition shotTgtPosn;
	int checkShot = checkShotBounds(shot);
	if (checkShot == -1)
	{
		std::cout << "Shot out of bounds" << std::endl;
		return Shot::Impact::INVALID;
	}
	for (itr = ships.begin(); itr != ships.end(); itr++)
	{
		Ship shipObj = *itr;
		std::set<GridPosition> shipOccupiedPosn = shipObj.getOccupiedArea();
		std::set<GridPosition> shots = getShotAt();
		shotTgtPosn = shot.getTargetPosition();
		bool isHit = shipOccupiedPosn.find(shotTgtPosn)
				!= shipOccupiedPosn.end();
		if (isHit == true)
		{
			std::set<GridPosition> intersectionSet;
			std::set_intersection(shipOccupiedPosn.begin(),
					shipOccupiedPosn.end(), shots.begin(), shots.end(),
					std::inserter(intersectionSet, intersectionSet.begin()));
			if (intersectionSet.size()
					== static_cast<size_t>(shipObj.length() - 1)) // For last part of the ship
			{
				int index = gridObjToIndex(shot);
				m_oGrid[index] = 'O';
				shipObj.addShots(shot);
				setShotAt(shot);
				return Shot::Impact::SUNKEN;
			}
			else
			{
				int index = gridObjToIndex(shot); // For any part of the ship taking shot
				m_oGrid[index] = 'O';
				shipObj.addShots(shot);
				setShotAt(shot);
				return Shot::Impact::HIT;
			}
		}
		else if (isHit == false) //Missed shots
		{
			int index = gridObjToIndex(shot);
			setShotAt(shot);
			m_oGrid[index] = '^';
		}
	}
	return Shot::Impact::NONE;
}

int OwnGrid::gridObjToIndex(const Shot &shot)
{
	GridPosition gridObj = shot.getTargetPosition();
	int row = charToNumber(gridObj.getRow());
	int column = gridObj.getColumn() - 1;
	int gridCols = getColumns();
	int index = row * gridCols + column;
	return index;
}

std::set<Ship> OwnGrid::getShips()
{
	return ships;
}

bool OwnGrid::placeShip(Ship &&ship)
{
	std::string posBow = ship.getBow();
	std::string posStern = ship.getStern();
	std::set<GridPosition>::iterator itr;
	int bowRow = charToNumber(posBow[0]) + 1;
	int bowCol = atoi(posBow.substr(1).c_str()) - 1;
	int sternRow = charToNumber(posStern[0]) + 1;
	int sternCol = atoi(posStern.substr(1).c_str()) - 1;
	int gridCols = getColumns();
	if (bowRow == sternRow)
	{
		// Vertical placement
		for (int col = bowCol; col <= sternCol; col++)
		{
			ship.occupiedArea(
			{ posBow[0], (col + 1) });
			ship.blockedArea(
			{ posBow[0], (col + 1) });
			checkNearbyCells(posBow[0], col, ship);
		}
	}
	else if (bowCol == sternCol)
	{
		// Horizontal placement
		char nextRow = posBow[0];
		for (int row = bowRow; row <= sternRow; row++)
		{
			nextRow = posBow[0] + row;
			ship.occupiedArea(
			{ nextRow, (bowCol + 1) });
			ship.blockedArea(
			{ nextRow, (bowCol + 1) });
			checkNearbyCells(nextRow, bowCol, ship);
		}
	}
	else
	{
		std::cout
				<< "Error: Ship must be placed either horizontally or vertically!"
				<< std::endl;
		return false;
	}

	// Validate and place the ship
	if (shipDetails.find(ship.length()) == shipDetails.end()
			|| shipDetails[ship.length()] <= 0)
	{
		std::cout << "Cannot place ships of this length" << std::endl;
		return false;
	}
	shipDetails[ship.length()]--;
	for (const auto &gridObj : ship.getOccupiedArea())
	{
		if (!ships.empty() && !shipNoTouch(ship))
			return false;

		int row = charToNumber(gridObj.getRow());
		int column = gridObj.getColumn() - 1;
		m_oGrid[row * gridCols + column] = '#';
	}
	ships.insert(std::move(ship));
	return true;
}

int OwnGrid::charToNumber(char ch)
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

int OwnGrid::getRows()
{
	return rows;
}

int OwnGrid::getColumns()
{
	return columns;
}

char* OwnGrid::rtrnGrid()
{
	return m_oGrid;
}

char OwnGrid::numberToChar(int rowNumber)
{
	return 'A' + rowNumber;
}

std::set<GridPosition> OwnGrid::getShotAt()
{
	return shotAt;
}

void OwnGrid::setShotAt(const Shot &shot)
{
	shotAt.insert(shot.getTargetPosition());
}

std::map<int, int> OwnGrid::getShipDetails()
{
	return shipDetails;
}

void OwnGrid::printShipDetails()
{
	// Print header
	std::cout << std::left << std::setw(15) << "Ship Type" << std::setw(15)
			<< "Length" << "Number of Ships" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	// Print the map contents in table format
	for (const auto &ship : shipDetails)
	{
		std::cout << std::left << std::setw(15)
				<< (ship.first == 5 ? "Carrier" :
					ship.first == 4 ? "Battleship" :
					ship.first == 3 ? "Destroyer" : "Submarine")
				<< std::setw(15) << ship.first << ship.second << std::endl;
	}
}

int OwnGrid::checkShotBounds(const Shot &shot)
{
	int gridCols = getColumns();
	int gridRows = getRows();
	GridPosition shotMade = shot.getTargetPosition();
	int shotRow = charToNumber(shotMade.getRow());
	int shotCol = shotMade.getColumn();
	if (shotCol > 0 && shotRow >= 0)
	{
		if (shotCol < gridCols && shotRow < gridRows)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	return 0;
}

OwnGrid::~OwnGrid()
{
// TODO Auto-generated destructor stub
	delete[] m_oGrid;
}

