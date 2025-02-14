/*
 * part2tests.h
 *
 *  Created on: 09-Jan-2025
 *      Author: abhim
 */

#ifndef PART2TESTS_H_
#define PART2TESTS_H_

#include <iostream>
#include <string>
#include "GridPosition.h"  // Include necessary headers
#include "ConsoleView.h"
#include "OwnGrid.h"
#include "OpponentGrid.h"
#include "Ship.h"
#include "Board.h"

/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrueTest2(bool condition, std::string failedMessage);

/**
 * This function runs the part 1 tests for the GridPosition and Ship classes.
 */
void part2tests();

#endif /* PART2TESTS_H_ */
