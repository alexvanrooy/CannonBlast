/*
 * CannonBall.cpp
 *
 *  Created on: Nov. 27, 2022
 *      Author: avanr
 */
#include "CannonBall.hpp"
#include <stdio.h>

#define TRAVELING 0;
#define HIT_GROUND 1;
#define HIT_TARGET 2;

GLfloat ballX, ballY, ballZ;

CannonBall::CannonBall(){
	r = 0.2;
	g = 0.2;
	b = 0.2;
	fired = false;
}

GLfloat calculateHeight(GLfloat x, GLfloat angle, GLint power){
	angle = angle/40;


	GLfloat y = -(angle/power)*(pow(x,2)) + 2*angle*x;


	return y;

}

int CannonBall::FireCannon(GLfloat x, GLfloat y, GLfloat angle, GLfloat power, TargetGrid* grid){
	this->fired = true;
	int status = TRAVELING;
	if(angle == 0){
		angle = -0.5;
	}

	ballX = x;
	ballY = y;
	ballZ = calculateHeight(-ballY, -angle, power);

	this->draw();

	if(ballZ < 0){
		status = HIT_GROUND;
	}

	//after updating, check the collision of the ball and any target
	if(grid->checkCollision(ballX, ballY, ballZ) == 1){
		status = HIT_TARGET;
	}



	return status;
}

void CannonBall::draw()
{
	if(fired){
		glPushMatrix();
		this->ctmMultiply();
		glTranslatef(ballX, ballY, ballZ);
		glScalef(0.45,0.45,0.45);
		glColor3f(r, g, b);

		glutSolidSphere(1, 10, 10);


		glPopMatrix();
	}
}


