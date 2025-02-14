/*
 * part3tests.cpp
 *
 *  Created on: 09-Jan-2025
 *      Author: abhim
 */
#include <iostream>

using namespace std;

#include "part3tests.h"

void assertTrueTest3(bool condition, string failedMessage)
{
	if (!condition)
	{
		cout << failedMessage << endl;
	}
}

void part3tests()
{
	Board player1
	{ 10, 10 };
	Board player2 = player1;

	OwnGrid &player1OwnGrid = player1.getOwnGrid();
	OpponentGrid &player1sOpponentGrid = player1.getOpponentGrid();
	std::cout << std::endl;
	Ship ship3
	{ "A3", "D3" };
	Ship ship4
	{ "A5", "D5" };
	Ship ship5
	{ "A7", "C7" };
	player1OwnGrid.placeShip(std::move(ship4));
	player1OwnGrid.placeShip(std::move(ship3));
	player1OwnGrid.placeShip(std::move(ship5));

	OwnGrid &player2OwnGrid = player2.getOwnGrid();
	OpponentGrid &player2sOpponentGrid = player2.getOpponentGrid();
	std::cout << std::endl;
	Ship ship1
	{ "A1", "A3" };
	Ship ship2
	{ "A3", "A7" };
	player2OwnGrid.placeShip(std::move(ship1));
	player2OwnGrid.placeShip(std::move(ship2));
	player2sOpponentGrid.storeOpponentShips(player1OwnGrid.getShips());
	player1sOpponentGrid.storeOpponentShips(player2OwnGrid.getShips());

	//
	//MAKING SHOTS BY PLAYERS 1 AND 2
	//
	std::cout << "Making shots" << std::endl << std::endl;
	std::string playerMove;
	Shot::Impact shotResultGrid;

	//Player1 making valid shots
	playerMove = "A3";
	shotResultGrid = player2OwnGrid.takeBlow(
	{ playerMove });
	assertTrueTest3((shotResultGrid != Shot::Impact::INVALID) == true,
			"Shot valid");
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player1sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}

	//Player 1 making shot which hits the ship
	playerMove = "A2";
	shotResultGrid = player2OwnGrid.takeBlow(
	{ playerMove });
	assertTrueTest3((shotResultGrid == Shot::Impact::HIT) == true,
			"Shot valid");
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player1sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}

	//Player1 making invalid shots
	playerMove = "A11";
	shotResultGrid = player2OwnGrid.takeBlow(
	{ playerMove });
	assertTrueTest3((shotResultGrid == Shot::Impact::INVALID) == true,
			"Shot invalid");
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player1sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}

	//Player 1 making shot which sinks the ship(Destroyer ship)
	playerMove = "A1";
	shotResultGrid = player2OwnGrid.takeBlow(
	{ playerMove });
	assertTrueTest3((shotResultGrid == Shot::Impact::SUNKEN) == true,
			"Shot sinks the ship");
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player1sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}

	//Player2 making shots
	playerMove = "C1";
	shotResultGrid = player1OwnGrid.takeBlow(
	{ playerMove });
	assertTrueTest3((shotResultGrid != Shot::Impact::INVALID) == true,
			"Shot was valid");
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player2sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}
}

