/*
 *
 *  Author: Alex Van Rooy
 *  Version: 2022-11-05
 */
#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"


class Cube: public Shape {
protected:
	GLfloat vertex[8][3];  /* 2D array to store cube vertices */
	GLint face[6][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color cube */
	GLint points;			//100 for small, 50 for medium, 10 for large

public:
	bool hit;
	Cube();
	void draw();
	void drawFace(int);
	GLint getPoints();
	void setPoints(GLint points);
};

#endif
