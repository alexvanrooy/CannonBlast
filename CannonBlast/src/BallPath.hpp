/*
 * BallPath.hpp
 *
 *  Created on: Nov. 28, 2022
 *      Author: avanr
 */

#ifndef BALLPATH_HPP_
#define BALLPATH_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class BallPath: public Shape {
protected:
	GLfloat vertex[15][3];  	/* 2D array to store wheel vertices */
	GLfloat r, g, b;       		/* color wheel */
	Shape* cannon;
	int dotNum;

public:
	BallPath(Shape* cannon);
	void draw();
};


#endif /* BALLPATH_HPP_ */
