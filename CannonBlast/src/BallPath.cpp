/*
 * BallPath.cpp
 *
 *  Created on: Nov. 28, 2022
 *      Author: avanr
 */

#include "BallPath.hpp"
#include <cmath>
#include <stdio.h>

/*
 * Calculates the height of the cannon ball at a given x
 * Equation for path: y = -(a/p)(x^2) + 2ax where a = angle, p = power, 0 < a < 90
 */
GLfloat calculatePoint(GLfloat x, GLfloat angle, GLint power){
	angle = angle/40;


	GLfloat y = -(angle/power)*(pow(x,2)) + 2*angle*x;


	return y;

}

BallPath::BallPath(Shape* cannon){
	r = 1;
	g = 0;
	b = 0;
	dotNum = 15;
	this->cannon = cannon;

}


void BallPath::draw()
{
	int x = 0;
	for(int i = 0; i < dotNum; i++){
		//calculate point
		vertex[i][0] = cannon->cannonX;		//the x is the same as the cannon
		vertex[i][1] = -x;		// the y is the x in the equation

		GLfloat z = calculatePoint(x,-1*cannon->cannonRotation,cannon->cannonPower);

		vertex[i][2] = z;		// the z is the result of the equation
		x += 1;
	}


	glColor3f(1, 0, 0);
    glPushMatrix();
    this->ctmMultiply();
    glPointSize(5);
    GLfloat limit = cannon->cannonPower;
    if(limit > dotNum ){
    	limit = dotNum;
    }

    glBegin(GL_POINTS);
    	for(int i = 0; i < limit; i++){
    		glVertex3f(vertex[i][0], vertex[i][1], vertex[i][2]);
    	}
    glEnd();

    glPopMatrix();
}









