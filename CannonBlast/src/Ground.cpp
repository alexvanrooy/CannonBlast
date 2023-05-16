#include "Ground.hpp"

#include <iostream>

Ground::Ground()
{

	// set cordinate values for all vertices
	vertex[0][0] = -0.5;
	vertex[0][1] = -0.5;
	vertex[0][2] = -0.5;

	vertex[1][0] = -0.5;
	vertex[1][1] = 0.5;
	vertex[1][2] = -0.5;

	vertex[2][0] = 0.5;
	vertex[2][1] = 0.5;
	vertex[2][2] = -0.5;

	vertex[3][0] = 0.5;
	vertex[3][1] = -0.5;
	vertex[3][2] = -0.5;

	vertex[4][0] = -0.5;
	vertex[4][1] = -0.5;
	vertex[4][2] = 0.5;

	vertex[5][0] = -0.5;
	vertex[5][1] = 0.5;
	vertex[5][2] = 0.5;

	vertex[6][0] = 0.5;
	vertex[6][1] = 0.5;
	vertex[6][2] = 0.5;

	vertex[7][0] = 0.5;
	vertex[7][1] = -0.5;
	vertex[7][2] = 0.5;

    // other faces
	//face[0] = {0, 1, 2, 3};
	face[0][0] = 0;
	face[0][1] = 1;
	face[0][2] = 2;
	face[0][3] = 3;

	//face[1] = {7, 6, 5, 4};
	face[1][0] = 7;
	face[1][1] = 6;
	face[1][2] = 5;
	face[1][3] = 4;

	//face[2] = {0, 4, 5, 1};
	face[2][0] = 0;
	face[2][1] = 4;
	face[2][2] = 5;
	face[2][3] = 1;

	//face[3] = {2, 1, 5, 6};
	face[3][0] = 2;
	face[3][1] = 1;
	face[3][2] = 5;
	face[3][3] = 6;

	//face[4] = {3, 2, 6, 7};
	face[4][0] = 3;
	face[4][1] = 2;
	face[4][2] = 6;
	face[4][3] = 7;

	//face[5] = {0, 3, 7, 4};
	face[5][0] = 0;
	face[5][1] = 3;
	face[5][2] = 7;
	face[5][3] = 4;


}

void Ground::drawFace(int i)
{
	   glColor3f(0, 1, 0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,4);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex[face[i][0]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex[face[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex[face[i][2]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex[face[i][3]]);
		glEnd();
		glDisable(GL_TEXTURE_2D);
}

void Ground::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 // draw all faces
	glScalef(1000,1000,0.05);
	for (int i = 0; i < 6; i++) {
		drawFace(i);
	}
    glPopMatrix();
}



