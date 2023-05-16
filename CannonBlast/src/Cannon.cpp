/*
 * Cannon.cpp
 *
 *  Created on: Nov. 27, 2022
 *      Author: avanr
 */

#include "Cannon.hpp"

Cannon::Cannon()
{
	cannonX = 0;
	cannonRotation = 0;
	cannonPower = 5;

	wheelL =  new Wheel();
	wheelL->setParentMC(&mc);
	wheelL->translate(-1, 0.75, 0);

	wheelR =  new Wheel();
	wheelR->setParentMC(&mc);
	wheelR->translate(1, 0.75, 0);

	barrel = new Barrel();
	barrel->setParentMC(&mc);
}

Cannon::~Cannon()
{
	delete wheelL;
	delete wheelR;
	delete barrel;
}

void Cannon::draw()
{

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	wheelL->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	wheelR->draw();
	glPopMatrix();

    glPushMatrix();
    this->ctmMultiply();
	glScalef(s, s, s);
	glRotated(cannonRotation, 1, 0, 0);
	barrel->draw();
	glPopMatrix();
}
