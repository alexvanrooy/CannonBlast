/*
 * CannonBall.hpp
 *
 *  Created on: Nov. 27, 2022
 *      Author: avanr
 */

#ifndef CANNONBALL_HPP_
#define CANNONBALL_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "TargetGrid.hpp"

class CannonBall: public Shape {
protected:
	GLfloat r, g, b;       /* color cube */
	bool fired;

public:
	CannonBall();

	int FireCannon(GLfloat x,GLfloat y, GLfloat angle, GLfloat power,TargetGrid* grid);
	void draw();
};



#endif /* CANNONBALL_HPP_ */
