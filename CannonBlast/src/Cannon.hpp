/*
 * Cannon.hpp
 *
 *  Created on: Nov. 27, 2022
 *      Author: avanr
 */

#ifndef CANNON_HPP_
#define CANNON_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "Wheel.hpp"
#include "Barrel.hpp"

class Cannon: public Shape{
protected:
	Wheel* wheelL;
	Wheel* wheelR;
	Barrel* barrel;

public:

	~Cannon();
	Cannon();
	void draw();
};



#endif /* CANNON_HPP_ */
