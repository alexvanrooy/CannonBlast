/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03 (update)
 */
#include <stdio.h>
#include "Camera.hpp"
#include "Matrix.hpp"
#include <math.h>

Point* cameraModePoint = new Point();

Camera::Camera(){
	reset();
}

void Camera::reset(void) { // HOME SCREEN
	eye.set(0, 0, 20.0);
	ref.set(0, -10, 10);
	viewup.set(0, 0, 1);
	aspect = 1.0, vangle = 90.0, dnear = 1, dfar = 100.0;
	setViewNorm();
}

void Camera::set(Point Eye, Point Look, Vector Up) {
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Camera::setViewNorm() {
	GLfloat x, y, z, sr;
	x = ref.x-eye.x;
	y = ref.y-eye.y;
	z = ref.z-eye.z;
	sr = sqrt(x*x + y*y + z*z);
	x = x/sr;
	y = y/sr;
	z = z/sr;
	viewNorm.set(x, y, z);
}

void Camera::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle){ //w.r.p.t WC
	Matrix m;
	m.rotateMatrix(rx, ry, rz, angle);
	GLfloat vector[4];
	vector[0] = eye.x;
	vector[1] = eye.y;
	vector[2] = eye.z;
	vector[3] = 1;
	m.multiplyVector(vector);
	eye.x = vector[0];
	eye.y = vector[1];
	eye.z = vector[2];
}

void Camera::translate(GLfloat tx, GLfloat ty, GLfloat tz){ //w.r.p.t WC
	eye.x += tx;
	eye.y += ty;
	eye.z += tz;
}

void Camera::setRef(GLfloat lx, GLfloat ly, GLfloat lz) {
	ref.set(lx, ly, lz);
}

void Camera::setProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(vangle, aspect, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, ref.x, ref.y, ref.z, viewup.x,viewup.y,viewup.z);
}

void Camera::changeCameraMode(int mode, GLfloat cannonX, GLfloat cannonY, GLfloat cannonZ){
	switch(mode){
	case 0:
		eye.set(-25 + cannonX, -15 + cannonY, 4);										//far away view
		ref.set(cannonX, -15, 2);
		vangle = 100.0;
		setViewNorm();
		break;

	case 1:
		eye.set(0 + cannonX, 10.0 + cannonY, 2 + cannonZ);			//first person
		ref.set(cannonX, cannonY, cannonZ);
		vangle = 90.0;
		setViewNorm();
		break;

	case 2:
		eye.set(-50, -5, 0);
		ref.set(-50, -10, 0);
		vangle = 90.0;
		setViewNorm();
		break;

	case 3:
		eye.set(-50, -5, 0);
		ref.set(-50, -10, 0);
		vangle = 90.0;
		setViewNorm();
		break;
	}

}

