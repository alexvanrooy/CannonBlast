#include "Cube.hpp"

#include <iostream>

Cube::Cube()
{
	points = 0;

	hit = false;
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


	//shape colour
    r = 0.0;
    g = 1.0;
    b = 1.0;


}

void Cube::drawFace(int i)
{
	if(this->points == 100){							//small target

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,5);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3fv(vertex[face[i][0]]);
			glTexCoord2f(1.0, 0.0); glVertex3fv(vertex[face[i][1]]);
			glTexCoord2f(1.0, 1.0); glVertex3fv(vertex[face[i][2]]);
			glTexCoord2f(0.0, 1.0); glVertex3fv(vertex[face[i][3]]);
			glEnd();
			glDisable(GL_TEXTURE_2D);


	}

	if(this->points == 50){								//medium target

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,6);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex[face[i][0]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex[face[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex[face[i][2]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex[face[i][3]]);
		glEnd();
		glDisable(GL_TEXTURE_2D);


	}

	if(this->points == 10 || this->points == 0 ){		//large target

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,7);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex[face[i][0]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex[face[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex[face[i][2]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex[face[i][3]]);
		glEnd();
		glDisable(GL_TEXTURE_2D);


	}

}

void Cube::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 // draw all faces
    glColor3f(1, 1, 1);
    if(this->points == 100){
		glScalef(1,0.3,1);
    }
    else if(this->points == 50)
    	glScalef(3,0.3,3);
    else if(this->points == 10 || this->points == 0)
    	glScalef(5,0.3,5);

	for (int i = 0; i < 6; i++) {
		drawFace(i);
	}
    glPopMatrix();
}

GLint Cube::getPoints(){
	return points;
}

void Cube::setPoints(int points){
	this->points = points;
	return;
}

