/*
 * OpponentGrid.cpp
 *
 *  Created on: 26-Dec-2024
 *      Author: abhim
 */

#include "OpponentGrid.h"
#include <set>
#include <algorithm>
#include <iomanip>

OpponentGrid::OpponentGrid()
{
	// TODO Auto-generated constructor stub

}

OpponentGrid::OpponentGrid(int rowEntry, int colEntry) :
		rows
		{ rowEntry }, columns
		{ colEntry }
{
	m_oppBoard = new char[rows * columns];
	for (unsigned short index = 0; index < (rows * columns); index++)
	{
		m_oppBoard[index] = '~';
	}
}

OpponentGrid::OpponentGrid(const OpponentGrid &other) :
		rows
		{ other.rows }, columns
		{ other.columns }, sunkenShips
		{ other.sunkenShips }, shots
		{ other.shots }, oppShipDetails
		{ other.oppShipDetails }
{
	m_oppBoard = new char[rows * columns];
	for (unsigned short index = 0; index < (rows * columns); index++)
	{
		m_oppBoard[index] = other.m_oppBoard[index];
	}
}

OpponentGrid::OpponentGrid(OpponentGrid &&source) :
		rows
		{ source.rows }, columns
		{ source.columns }, sunkenShips
		{ std::move(source.sunkenShips) }, oppShips
		{ std::move(source.oppShips) }, m_oppBoard
		{ source.m_oppBoard }
{
	source.rows = 0;
	source.columns = 0;
	source.sunkenShips.clear();
	source.oppShipDetails.clear();
	source.oppShips.clear();
	source.shots.clear();
	source.m_oppBoard = nullptr;
}

OpponentGrid& OpponentGrid::operator =(OpponentGrid &&source)
{
	// Free existing resources (if any)
	delete[] m_oppBoard;

	// Move primitive types
	rows = std::move(source.rows);
	columns = std::move(source.columns);

	// Move dynamic memory (board pointer)
	m_oppBoard = source.m_oppBoard;
	source.m_oppBoard = nullptr; // Nullify source pointer

	// Move sets and maps
	sunkenShips = std::move(source.sunkenShips);
	shots = std::move(source.shots);
	oppShipDetails = std::move(source.oppShipDetails);
	oppShips = std::move(source.oppShips);
	return *this;
}

OpponentGrid& OpponentGrid::operator =(const OpponentGrid &orig)
{
	delete[] m_oppBoard;
	rows = orig.rows;
	columns = orig.columns;
	sunkenShips = orig.sunkenShips;
	shots = orig.shots;
	oppShipDetails = orig.oppShipDetails;
	m_oppBoard = new char[rows * columns];
	for (unsigned short index = 0; index < (rows * columns); index++)
	{
		m_oppBoard[index] = orig.m_oppBoard[index];
	}
	return *this;
}

int OpponentGrid::getRows() const
{
	return rows;
}

int OpponentGrid::getColumns() const
{
	return columns;
}

char* OpponentGrid::rtrnGridOpponent()
{
	return m_oppBoard;
}

Shot::Impact OpponentGrid::shotResult(const Shot &shot, Shot::Impact impact)
{
	int index = gridObjToIndex(shot);
	std::set<GridPosition> shots;
	Ship shipObj;
	shipObj = getOpponentShip(shot);
	std::map<GridPosition, Shot::Impact> getShots = getShotsAt();
	if (impact == Shot::Impact::HIT)
	{
		std::set<GridPosition> intersectionSet;
		const std::set<GridPosition> &shipOccupiedPosn =
				shipObj.getOccupiedArea();
		for (const auto &pair : getShots)
		{
			shots.insert(pair.first); // Add the key (pair.first) to the vector
		}
		std::set_intersection(shipOccupiedPosn.begin(), shipOccupiedPosn.end(),
				shots.begin(), shots.end(),
				std::inserter(intersectionSet, intersectionSet.begin()));
		if (intersectionSet.size() == static_cast<size_t>(shipObj.length() - 1)) // For last part of the ship
		{
			m_oppBoard[index] = '#';
			shipObj.addShots(shot);
			convertToSunkenShip(shot);
			setShotsAt(shot.getTargetPosition(), impact);
			updateOpponentShipDetails(shipObj);
			return Shot::Impact::SUNKEN;
		}
		else //For any part of the ship which is hit
		{
			m_oppBoard[index] = 'O';
			shipObj.addShots(shot);
			setShotsAt(shot.getTargetPosition(), impact);
			return Shot::Impact::HIT;
		}

	}
	else if (impact == Shot::Impact::NONE)
	{
		m_oppBoard[index] = '^';
		setShotsAt(shot.getTargetPosition(), impact);
		return Shot::Impact::NONE;
	}
	else if (impact == Shot::Impact::SUNKEN)
	{
		m_oppBoard[index] = '#';
		shipObj.addShots(shot);
		convertToSunkenShip(shot);
		setShotsAt(shot.getTargetPosition(), impact);
		updateOpponentShipDetails(shipObj);
		return Shot::Impact::SUNKEN;
	}
	return Shot::Impact::NONE;
}

void OpponentGrid::storeOpponentShips(std::set<Ship> opponentShips)
{
	oppShips = opponentShips; //Stores the opponent ship details
}

Ship OpponentGrid::getOpponentShip(GridPosition shotPosition)
{
	std::set<Ship>::iterator itr;
	Ship shipObj, retShip;
	std::set<GridPosition> occupiedGridPosns;
	GridPosition gridObj;
	for (itr = oppShips.begin(); itr != oppShips.end(); itr++)
	{
		shipObj = *itr;
		occupiedGridPosns = shipObj.getOccupiedArea();
		if (occupiedGridPosns.find(shotPosition) != occupiedGridPosns.end())
		{
			// If found, return the corresponding ship
			return shipObj;
		}
	}
	return shipObj;
}

int OpponentGrid::gridObjToIndex(const Shot &shot)
{
	GridPosition gridObj = shot.getTargetPosition();
	int row = charToNumber(gridObj.getRow());
	int column = gridObj.getColumn() - 1;
	int gridCols = getColumns();
	int index = row * gridCols + column;
	return index;
}

void OpponentGrid::getOpponentTotShipDetails() const
{
	// Print header
	std::cout << std::left << std::setw(15) << "Ship Type" << std::setw(15)
			<< "Length" << "Number of ships sunken" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	// Print the map contents in table format
	for (const auto &ship : oppShipDetails)
	{
		std::cout << std::left << std::setw(15)
				<< (ship.first == 5 ? "Carrier" :
					ship.first == 4 ? "Battleship" :
					ship.first == 3 ? "Destroyer" : "Submarine")
				<< std::setw(15) << ship.first << ship.second << std::endl;
	}
}

void OpponentGrid::updateOpponentShipDetails(Ship &ship)
{
	int shipLength = ship.length();

	if (oppShipDetails.find(shipLength) != oppShipDetails.end())
	{
		oppShipDetails[shipLength]++;
	}
	else
	{
		std::cout << "Ship does not exist";
	}
}

const std::map<GridPosition, Shot::Impact>& OpponentGrid::getShotsAt() const
{
	return shots;
}

void OpponentGrid::setShotsAt(const GridPosition &shot, Shot::Impact impact)
{
	shots.insert(
	{ shot, impact });
}

void OpponentGrid::convertToSunkenShip(const Shot &shot)
{
	Ship shipObj;
	GridPosition gridObj;
	std::set<GridPosition> shipOccupiedArea;
	std::set<GridPosition>::iterator itr;
	shipObj = getOpponentShip(shot);
	shipOccupiedArea = shipObj.getOccupiedArea();
	for (itr = shipOccupiedArea.begin(); itr != shipOccupiedArea.end(); itr++)
	{
		gridObj = *itr;
		int index = gridObjToIndex(gridObj);
		m_oppBoard[index] = '#';
	}
}

OpponentGrid::~OpponentGrid()
{
// TODO Auto-generated destructor stub
	delete[] m_oppBoard;
}

