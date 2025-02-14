// Standard (system) header files
#include <iostream>
#include <cstdlib>

#include "part1tests.h"
#include "part2tests.h"
#include "part3tests.h"

#include "GridPosition.h"
#include "Ship.h"
#include "Board.h"
#include "ConsoleView.h"
#include "OwnGrid.h"
#include "Shot.h"
#include <set>

// Main program
int main()
{
	// TODO: Add your program code here
	std::cout << "battleship started." << std::endl << std::endl;
//	part1tests();
//	part2tests();
//	part3tests();

//	CREATING BOARDS

	Board player1
	{ 10, 10 };
	Board player2 = player1;

	std::cout << "Player 1 and player 2 boards created" << std::endl;

	//
	//PLACING SHIPS ON THE RESPECTIVE GRIDS AND PRINTING THE BOARD STATE
	//
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

	ConsoleView consolePlayer1(player1);
	ConsoleView consolePlayer2(player2);
	std::cout << "Printing player 1 board";
	consolePlayer1.printGrids();
	std::cout << "Printing player 2 board";
	consolePlayer2.printGrids();

	//
	//MAKING SHOTS BY PLAYERS 1 AND 2
	//
	std::cout << "Making shots" << std::endl << std::endl;
	std::string playerMove;
	Shot::Impact shotResultGrid;

	//Player1 making shots
	playerMove = "A3";
	shotResultGrid = player2OwnGrid.takeBlow(
	{ playerMove });
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player1sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}

	playerMove = "A2";
	shotResultGrid = player2OwnGrid.takeBlow(
	{ playerMove });
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player1sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}
	playerMove = "A1";
	shotResultGrid = player2OwnGrid.takeBlow(
	{ playerMove });
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player1sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}

	//Player2 making shots
	playerMove = "C3";
	shotResultGrid = player1OwnGrid.takeBlow(
	{ playerMove });
	if (shotResultGrid == Shot::Impact::HIT
			|| shotResultGrid == Shot::Impact::SUNKEN
			|| shotResultGrid == Shot::Impact::NONE)
	{
		player2sOpponentGrid.shotResult(
		{ playerMove }, shotResultGrid);
	}

	//
	//PRINTING BOARDS AFTER MAKING SHOTS
	//
	std::cout << "Printing player 1 board" << std::endl;
	consolePlayer1.printGrids();
	std::cout << "Printing player 2 board" << std::endl;
	consolePlayer2.printGrids();

	//
	//PRINTING HIT SHIP DETAILS IN THE END
	//
	std::cout << "Printing opponent ship details" << std::endl;
	std::cout << std::endl << "Player1s hit ship details" << std::endl
			<< std::endl;
	player2sOpponentGrid.getOpponentTotShipDetails();
	std::cout << std::endl << "Player2s hit ship details" << std::endl
			<< std::endl;
	player1sOpponentGrid.getOpponentTotShipDetails();

	return 0;
}
