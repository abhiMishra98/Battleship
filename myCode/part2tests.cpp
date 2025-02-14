/*
 * part1tests.cpp
 *
 *  Created on: 09-Jan-2025
 *      Author: abhim
 */

/*
 * part1tests.cpp
 *
 *  Created on: 15.11.2019
 *      Author: mnl
 */

#include <iostream>

using namespace std;

#include "part2tests.h"

/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrueTest2(bool condition, string failedMessage)
{
	if (!condition)
	{
		cout << failedMessage << endl;
	}
}

/**
 */
void part2tests()
{
	Board player1
	{ 10, 10 };
	OwnGrid &player1OwnGrid = player1.getOwnGrid();

	// Ships can be placed only horizontally or vertically
	assertTrueTest2(player1OwnGrid.placeShip(
	{ "A3", "A5" }), "Vertical placement not considered valid");
	assertTrueTest2(!player1OwnGrid.placeShip(
	{ "A3", "D5" }),
			"Should not allow ships to be placed apart from horizontal or vertical directions");
	assertTrueTest2(player1OwnGrid.placeShip(
	{ "F3", "F4" }), "Should allow a ship of length 2 to be placed");
	assertTrueTest2(!player1OwnGrid.placeShip(
	{ "A3", "A3" }), "Should not allow ships of length 1 to be placed");

	//Ships should not be placed in blocked areas
	Ship ship2
	{ "A3", "D3" };
	player1OwnGrid.placeShip(std::move(ship2));
	assertTrueTest2(player1OwnGrid.placeShip(
	{ "D7", "D9" }), "Should allow ships to be placed in non-blocked areas");
	assertTrueTest2(!player1OwnGrid.placeShip(
	{ "A4", "D4" }), "Ships should not be placed in nearby blocked areas");

	//Ships can be placed as per their numbers, not more than that
	//Check for submarine ships
	Ship ship3
	{ "A3", "B3" };
	player1OwnGrid.placeShip(std::move(ship3));
	Ship ship4
	{ "E3", "F3" };
	player1OwnGrid.placeShip(std::move(ship4));
	Ship ship5
	{ "E5", "E6" };
	player1OwnGrid.placeShip(std::move(ship5));
	Ship ship6
	{ "E2", "F2" };
	player1OwnGrid.placeShip(std::move(ship6));
	assertTrueTest2(!player1OwnGrid.placeShip(
	{ "A5", "B5" }), "Submarine ships already exhausted");

}

