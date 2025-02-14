/*
 * part3tests.h
 *
 *  Created on: 09-Jan-2025
 *      Author: abhim
 */

#ifndef PART3TESTS_H_
#define PART3TESTS_H_

#include <iostream>
#include <string>
#include "GridPosition.h"  // Include necessary headers
#include "ConsoleView.h"
#include "OwnGrid.h"
#include "OpponentGrid.h"
#include "Ship.h"           // Assuming Ship.h exists

/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrueTest3(bool condition, std::string failedMessage);

/**
 * This function runs the part 1 tests for the GridPosition and Ship classes.
 */
void part3tests();

#endif /* PART3TESTS_H_ */

