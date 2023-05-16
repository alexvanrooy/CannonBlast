/*
 * TargetGrid.hpp
 *
 *  Created on: Nov. 29, 2022
 *      Author: avanr
 */

#ifndef TARGETGRID_HPP_
#define TARGETGRID_HPP_

#include <GL/glut.h>
#include "Cube.hpp"
#include "Shape.hpp"

class TargetGrid: public Shape{
protected:
	Cube* target;
	Cube* grid[30];
	int playerScore;

public:
	int gridSize;
	TargetGrid();
	void draw();
	int checkCollision(GLfloat ballX, GLfloat ballY, GLfloat ballZ);
	int getPlayerScore();
};



#endif /* TARGETGRID_HPP_ */
