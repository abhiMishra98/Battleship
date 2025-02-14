/*
 * Shot.cpp
 *
 *  Created on: 07-Jan-2025
 *      Author: abhim
 */

#include "Shot.h"

Shot::Shot()
{
	// TODO Auto-generated constructor stub

}

Shot::Shot(GridPosition target) :
		targetPosition
		{ target }
{
}

Shot::Shot(const Shot &orig) :
		targetPosition
		{ orig.targetPosition }
{
	std::cout << "Copy constructor called from shot.h" << std::endl;
}

Shot& Shot::operator =(const Shot &orig)
{
	targetPosition = orig.targetPosition;
	std::cout << "Copy constructor called from ship.h" << std::endl;
	return *this;
}

Shot::Shot(Shot &&source) :
		targetPosition
		{ source.targetPosition }
{
	source.targetPosition = GridPosition();
	std::cout << "Move constructor called from shot.h" << std::endl;
}

Shot& Shot::operator =(Shot &&source)
{
	targetPosition = std::move(source.targetPosition);
	std::cout << "Move assignment called from shot.h" << std::endl;
	return *this;
}

const GridPosition& Shot::getTargetPosition() const
{
	return targetPosition;
}

Shot::~Shot()
{
	// TODO Auto-generated destructor stub
}

