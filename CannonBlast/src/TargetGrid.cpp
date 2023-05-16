/*
 * TargetGrid.cpp
 *
 *  Created on: Nov. 29, 2022
 *      Author: avanr
 */

#include "TargetGrid.hpp"
#include <stdlib.h>
#include <stdio.h>
#define NO_COLLISION 0
#define COLLISION 1

TargetGrid::TargetGrid(){
	/*
	 * 30 targets
	 * 		8 are small (1x1)
	 * 		12 are medium (3x3)
	 * 		10 are large (5x5)
	 */
	this->playerScore = 0;

	gridSize = 30;

	int count = 0;
	int x;
	int y;
	int z = 0;
	int targetSize;
	int smallCount = 8, mediumCount = 12, largeCount = 10;

	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 6; j++){
			target = new Cube();

			targetSize = rand() % 3;

			if(targetSize == 0 && smallCount > 0){		//target is small
				target->setPoints(100);
				smallCount--;
			}

			else if(targetSize == 1 && mediumCount > 0){		//target is medium
				target->setPoints(50);
				mediumCount--;
			}

			else if(targetSize == 2 && largeCount > 0){		//target is large
				target->setPoints(10);
				largeCount--;
			}
			else{
				if(smallCount > 0){
					target->setPoints(100);
					smallCount--;
				}
				else if (mediumCount > 0){
					target->setPoints(50);
					mediumCount--;
				}
				else if (largeCount > 0){
					target->setPoints(10);
					largeCount--;

				}
			}

			x = (((count*5) + (rand() % 5)) % 40);
			y = -30 + (rand() % 3);

			target->translate(x - 15, y, z);

			grid[count] = target;
			count += 1;
		}
		z+=4;

	}


}



void TargetGrid::draw()
{
	for(int i = 0; i < gridSize; i++){
		if(!grid[i]->hit)
			grid[i]->draw();
	}
}

int TargetGrid::checkCollision(GLfloat ballX, GLfloat ballY, GLfloat ballZ){

	GLfloat targetX;
	GLfloat targetY;
	GLfloat targetZ;
	int collision = NO_COLLISION;
	for(int i = 0; i < gridSize; i++){
		if(grid[i]->hit){
			continue;
		}

		Matrix targetMC = this->grid[i]->getMC();
		targetX = targetMC.mat[0][3];
		targetY = targetMC.mat[1][3];
		targetZ = targetMC.mat[2][3];

		//calculate the dimensions of the target
		int targetPoints = grid[i]->getPoints();
		GLfloat targetLeft;
		GLfloat targetRight;
		GLfloat targetUp;
		GLfloat targetDown;

		if(targetPoints == 0 || targetPoints == 10){
			targetLeft = targetX + 2;
			targetRight = targetX - 3;
			targetUp = targetZ + 3;
			targetDown = targetZ - 3;
		}
		else if(targetPoints == 50){
			targetLeft = targetX + 1;
			targetRight = targetX - 2;
			targetUp = targetZ + 2;
			targetDown = targetZ - 2;

		}
		else if(targetPoints == 100){
			targetLeft = targetX + 1;
			targetRight = targetX - 1;
			targetUp = targetZ + 1;
			targetDown = targetZ - 1;

		}

		if(ballX <= targetLeft && ballX >= targetRight){
			if(targetY == ballY)
				if(ballZ >= targetDown && ballZ <= targetUp){
					collision = COLLISION;
					this->grid[i]->hit = true;
					this->playerScore += targetPoints;
				}
		}
	}

	return collision;
}

int TargetGrid::getPlayerScore(){
	return this->playerScore;
}




