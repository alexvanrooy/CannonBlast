/*
 *  CannonBlast
 *  Author: Alex Van Rooy
 *  Version: 2022-11-27
 */

//------INCLUDES------//
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "World.hpp"
#include "Camera.hpp"
#include "CannonBall.hpp"
#include "pixmap/RGBpixmap.h"

#include <windows.h>  // for playing sound
#include <mmsystem.h> //

//------GLOBAL VARIABLES------//
#define SPACEBAR 32

GLint winWidth = 800, winHeight = 800;
GLint translation = 0,
	  ballMovement = 0,
	  cameraMode = 0,
	  ballStatus = 1,
	  gameOver = -1, 			// -1 = game started, 0 = game is being played, 1 = game over
	  shotsLeft = 10;
RGBpixmap pix[8];


World myWorld;
Camera myCamera;

Shape *cannon = NULL;  // pointer to select object

//------FUNCTIONS------//

void message(char str[], int value, GLint x, GLint y) {
	glRasterPos2i(x, y);
	int i = 0;
	while (str[i]) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
		i++;
	}

	i = 0;
	char valueString[33];
	itoa(value,valueString,10);

	if(value != -1){
		while (valueString[i]) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, valueString[i]);
			i++;
		}
	}
}

void init(void) {
	glClearColor(0.529, 0.808, 0.922, 1.0);

	//Load textures
	pix[1].readBMPFile("texture/startscreen.bmp");
	pix[1].setTexture(1);

	pix[2].readBMPFile("texture/endscreen.bmp");
	pix[2].setTexture(2);

	pix[3].readBMPFile("texture/cannon.bmp");
	pix[3].setTexture(3);

	pix[4].readBMPFile("texture/ground.bmp");
	pix[4].setTexture(4);

	pix[5].readBMPFile("texture/small_target.bmp");
	pix[5].setTexture(5);

	pix[6].readBMPFile("texture/medium_target.bmp");
	pix[6].setTexture(6);

	pix[7].readBMPFile("texture/large_target.bmp");
	pix[7].setTexture(7);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	cannon = myWorld.searchById(1);		//creates a pointer to the cannon

}

/*
 * Displays the start screen to the user
 */
void startScreen(){

	myCamera.changeCameraMode(2, 0, 0, 0);

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,1);
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-46.6,-10,-3);
	glTexCoord2f(1.0, 0.0); glVertex3f(-53.5,-10,-3);
	glTexCoord2f(1.0, 1.0); glVertex3f(-53.5,-10,5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-46.5,-10,5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	return;
}

/*
 * Displays the end screen to the user
 */
void endScreen(){

	myCamera.changeCameraMode(2, 0, 0, 0);

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,2);
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-46.6,-10,-3);
	glTexCoord2f(1.0, 0.0); glVertex3f(-53.5,-10,-3);
	glTexCoord2f(1.0, 1.0); glVertex3f(-53.5,-10,5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-46.5,-10,5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	return;
}



void drawHUD(){
	//setup for rendering to screen
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winWidth, winHeight, 0);
	glMatrixMode(GL_MODELVIEW);


	//Draws HUD element SHOTS LEFT:
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1,1,0);
	message("SHOTS LEFT: ",shotsLeft, 50 ,winHeight - 50);
	glPopMatrix();

	//Draws HUD element SCORE:
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1,1,0);
	message("SCORE: ",myWorld.getPlayerScore(), 50 ,winHeight - 70);
	glPopMatrix();


	//restore state before drawing to screen
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myCamera.setProjectionMatrix();
	myWorld.draw();
	if(gameOver == 1){			//if the game is over
		endScreen();
	}

	if(gameOver == -1){			//if the game has just started
		startScreen();
	}
	drawHUD();


	glFlush();
	glutSwapBuffers();
}


void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseActionFcn(int button, int state, int xMouse, int yMouse) {
	Matrix cannonMC = cannon->getMC();
	if(gameOver == 1){
		return;
	}

	//Click mouse button to start game
	if(button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON){
		if(gameOver == -1){
			gameOver = 0;
		}
	}

	//change camera mode
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cameraMode = (cameraMode + 1) % 2;
		myCamera.changeCameraMode(cameraMode, cannonMC.mat[0][3],cannonMC.mat[1][3],cannonMC.mat[2][3]);
	}

	//change camera mode
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		cameraMode = (cameraMode - 1) % 2;
		if(cameraMode < 0)
			cameraMode *= -1;
		myCamera.changeCameraMode(cameraMode, cannonMC.mat[0][3],cannonMC.mat[1][3],cannonMC.mat[2][3]);
	}

	//Scroll wheel for increasing/decreasing power
	if (ballStatus == 1){
		if (button == 3 && cannon->cannonPower < 20) {
			cannon->cannonPower += 0.5;
		}

		if (button == 4 && cannon->cannonPower > 5 ) {
			cannon->cannonPower -= 0.5;
		}

	}
	glutPostRedisplay();
}

/*
 * Shoot function that loops until cannon ball has reached the ground
 */
void shoot(int value){
	ballStatus = myWorld.fireCannon(-ballMovement);			//update the position of the cannon ball
	ballMovement++;											//increment the position of the ball's y-axis
	glutPostRedisplay();									//redisplay the updated cannon ball

	if(ballStatus == 1){									//ball has hit the ground
		if(shotsLeft == 0){
			gameOver = 1;
			endScreen();
		}
		return;
	}
	if(ballStatus == 2){									//ball hits a target
		PlaySound((LPCSTR) "sounds/hit_target.wav", NULL, SND_FILENAME | SND_ASYNC);
	}

	if(ballStatus != 1){									//checks to see that the ball is still traveling
		glutTimerFunc(50, shoot, 1);
	}


	return;
}

void keyboard(unsigned char key, int x, int y) {
	Matrix cannonMC = cannon->getMC();

	if(gameOver == 1){
		return;
	}

	switch (key) {
		case 'A':
		case 'a':														//moves the cannon right
			if(ballStatus == 1 && cannon->cannonX < 35){
				cannon->cannonX += 1;
				cannon->translate(1, 0, 0);
				myCamera.translate(1, 0, 0);
				myCamera.setRef(myCamera.ref.x + 1, myCamera.ref.y, myCamera.ref.z);
			}
			break;
		case 'D':
		case 'd':														//moves the cannon left
			if(ballStatus == 1 && cannon->cannonX > -30){
				cannon->cannonX -= 1;
				cannon->translate(-1, 0, 0);
				myCamera.translate(-1, 0, 0);

				myCamera.setRef(myCamera.ref.x - 1, myCamera.ref.y, myCamera.ref.z);
			}
			break;
		case 'W':
		case 'w':														//rotates the cannon up
			if(ballStatus == 1){
				if(cannon->cannonRotation > -40){
					cannon->cannonRotation -= 1;
					myCamera.setRef(myCamera.ref.x, myCamera.ref.y, myCamera.ref.z + 0.05);
				}
			}
			break;
		case 'S':
		case 's':														//rotates the cannon down
			if(ballStatus == 1){
				if(cannon->cannonRotation < 0){
					cannon->cannonRotation += 1;
					myCamera.setRef(myCamera.ref.x, myCamera.ref.y, myCamera.ref.z - 0.05);
				}
			}
			break;

		case SPACEBAR:													//fires the cannon
			if(ballStatus == 1 && shotsLeft > 0){
				PlaySound((LPCSTR) "sounds/fire_cannon.wav", NULL, SND_FILENAME | SND_ASYNC);
				glutTimerFunc(0, shoot, 1);
				ballMovement = 0;
				shotsLeft--;
			}
			break;
		default:
			break;
	}

	glutPostRedisplay();
}


int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(400, 0);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Cannon Blast");


	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseActionFcn);
	glutKeyboardFunc(keyboard);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
