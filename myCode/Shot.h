/*
 * Shot.h
 *
 *  Created on: 07-Jan-2025
 *      Author: abhim
 *       @brief - This class is used to represent an individual shot made by a player
 */

#ifndef SHOT_H_
#define SHOT_H_

#include "GridPosition.h"
#include <iostream>

/**
 * @brief Constitutes of the different shots made by the players
 *
 */

class Shot: public GridPosition
{
private:
	GridPosition targetPosition;/**<grid position at which the shot was made*/
public:

	/**
	 * @brief Constructor to create a shot
	 */
	Shot();

	/**
	 * @brief Constructor to create a shot
	 * @param target - shot made at a target GridPosition
	 */
	Shot(GridPosition target);

	/**
	 * @brief - Copy constructor to create a shot on a target position
	 * @param orig - object of type Shot
	 */
	Shot(const Shot &orig);

	/**
	 * @brief - Copy assignment operator to create a shot on a target position
	 * @param orig - Object of type Shot
	 */
	Shot& operator=(const Shot &orig);

	/**
	 * @brief - Move constructor to create a shot on a target position
	 * @param source - object of type Shot
	 */
	Shot(Shot &&source);

	/**
	 * @brief - Move assignment operator to create a shot on a target position
	 * @param source - Object of type Shot
	 */
	Shot& operator=(Shot &&source);

	/**
	 * @brief getter method to fetch the target position
	 */
	const GridPosition& getTargetPosition() const;

	/**
	 * @brief enum to represent three different results of a shot on the board
	 */
	enum Impact
	{
		NONE, HIT, SUNKEN, INVALID, ALREADYHIT
	};
	virtual ~Shot();
};

#endif /* SHOT_H_ */
