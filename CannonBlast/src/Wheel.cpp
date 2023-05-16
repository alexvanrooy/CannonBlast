/*
 * Wheel.cpp
 *
 *  Created on: Nov. 27, 2022
 *      Author: avanr
 */

#include "Wheel.hpp"

Wheel::Wheel(){
	r = 0;
	g = 0;
	b = 1;

	//near vertices
	vertex[0][0] = 0.5;
	vertex[0][1] = 1;
	vertex[0][2] = 1;

	vertex[1][0] = -0.5;
	vertex[1][1] = 1;
	vertex[1][2] = 1;

	vertex[2][0] = -1;
	vertex[2][1] = 1;
	vertex[2][2] = 0;

	vertex[3][0] = -0.5;
	vertex[3][1] = 1;
	vertex[3][2] = -1;

	vertex[4][0] = 0.5;
	vertex[4][1] = 1;
	vertex[4][2] = -1;

	vertex[5][0] = 1;
	vertex[5][1] = 1;
	vertex[5][2] = 0;

	//far vertices
	vertex[6][0] = 0.5;
	vertex[6][1] = -1;
	vertex[6][2] = 1;

	vertex[7][0] = -0.5;
	vertex[7][1] = -1;
	vertex[7][2] = 1;

	vertex[8][0] = -1;
	vertex[8][1] = -1;
	vertex[8][2] = 0;

	vertex[9][0] = -0.5;
	vertex[9][1] = -1;
	vertex[9][2] = -1;

	vertex[10][0] = 0.5;
	vertex[10][1] = -1;
	vertex[10][2] = -1;

	vertex[11][0] = 1;
	vertex[11][1] = -1;
	vertex[11][2] = 0;

	//near face
	base[0][0] = 0;
	base[0][1] = 1;
	base[0][2] = 2;
	base[0][3] = 3;
	base[0][4] = 4;
	base[0][5] = 5;

	//far face
	base[1][0] = 6;
	base[1][1] = 7;
	base[1][2] = 8;
	base[1][3] = 9;
	base[1][4] = 10;
	base[1][5] = 11;

	//side faces
	face[0][0] = 0;
	face[0][1] = 6;
	face[0][2] = 7;
	face[0][3] = 1;

	face[1][0] = 1;
	face[1][1] = 7;
	face[1][2] = 8;
	face[1][3] = 2;

	face[2][0] = 2;
	face[2][1] = 8;
	face[2][2] = 9;
	face[2][3] = 3;

	face[3][0] = 3;
	face[3][1] = 9;
	face[3][2] = 10;
	face[3][3] = 4;

	face[4][0] = 4;
	face[4][1] = 10;
	face[4][2] = 11;
	face[4][3] = 5;

	face[5][0] = 5;
	face[5][1] = 11;
	face[5][2] = 6;
	face[5][3] = 0;


}
void Wheel::drawFace(int i){
	   glColor3f(0.443, 0.447, 0.450);

	   glBegin(GL_POLYGON);
		   glVertex3fv(vertex[face[i][0]]);
		   glVertex3fv(vertex[face[i][1]]);
		   glVertex3fv(vertex[face[i][2]]);
		   glVertex3fv(vertex[face[i][3]]);
	   glEnd();

}

void Wheel::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 // draw all faces
    glRotated(90, 0, 0, 1);
    glScalef(0.5,0.25,0.5);
	glColor3f(0.443, 0.447, 0.450);

    glBegin(GL_POLYGON);
		glVertex3fv(vertex[base[0][0]]);
		glVertex3fv(vertex[base[0][1]]);
		glVertex3fv(vertex[base[0][2]]);
		glVertex3fv(vertex[base[0][3]]);
		glVertex3fv(vertex[base[0][4]]);
		glVertex3fv(vertex[base[0][5]]);
	glEnd();

    glBegin(GL_POLYGON);
		glVertex3fv(vertex[base[1][0]]);
		glVertex3fv(vertex[base[1][1]]);
		glVertex3fv(vertex[base[1][2]]);
		glVertex3fv(vertex[base[1][3]]);
		glVertex3fv(vertex[base[1][4]]);
		glVertex3fv(vertex[base[1][5]]);
    glEnd();


	for (int i = 0; i < 6; i++) {
		drawFace(i);
	}
    glPopMatrix();
}



