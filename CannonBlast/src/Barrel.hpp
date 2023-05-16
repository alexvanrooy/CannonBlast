/*
 * Barrel.hpp
 *
 *  Created on: Nov. 27, 2022
 *      Author: avanr
 */

#ifndef BARREL_HPP_
#define BARREL_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Barrel: public Shape {
protected:
	GLfloat vertex[12][3];  	/* 2D array to store wheel vertices */
	GLint base[2][6];			/* wheel base face */
	GLint face[6][4];      		/* wheel side face */
	GLfloat faceNormal[8][3];
	GLfloat r, g, b;       		/* color wheel */

public:
	Barrel();
	void drawFace(int i);
	void draw();
};



#endif /* BARREL_HPP_ */
