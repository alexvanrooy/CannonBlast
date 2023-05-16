/*
 *
 *  Author: Alex Van Rooy
 *  Version: 2022-11-05
 */
#ifndef CGROUND_H
#define CGROUND_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"


class Ground: public Shape {
protected:
	GLfloat vertex[8][3];  /* 2D array to store cube vertices */
	GLint face[6][4];      /* 2D array to store faces */

public:
	Ground();
	void draw();
	void drawFace(int);
};

#endif
