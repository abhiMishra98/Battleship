/*
 * part1tests.h
 *
 *  Created on: 09-Jan-2025
 *      Author: abhim
 */

#ifndef PART1TESTS_H_
#define PART1TESTS_H_

#include <iostream>
#include <string>
#include "GridPosition.h"  // Include necessary headers
#include "Ship.h"
/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrue(bool condition, std::string failedMessage);

/**
 * This function runs the part 1 tests for the GridPosition and Ship classes.
 */
void part1tests();

#endif /* PART1TESTS_H_ */
