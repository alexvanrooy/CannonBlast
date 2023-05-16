#include "World.hpp"
#include "Wheel.hpp"
#include "CannonBall.hpp"
#include "Barrel.hpp"
#include "Cannon.hpp"
#include "BallPath.hpp"
#include "Cube.hpp"
#include "TargetGrid.hpp"
#include "Ground.hpp"

using namespace std;
CannonBall* ballWorld;
Cannon* cannonWorld;
TargetGrid* targetGrid;

World::World() {
	Shape *obj = NULL;

	obj = new Ground();
	obj->setId(5);
	obj->translate(0, 0, -4);
	objlist.push_back(obj);

	//add cannon
	cannonWorld = new Cannon();
	obj = cannonWorld;
	obj->setId(1);
	obj->scaleChange(-0.2);
	objlist.push_back(obj);

	//add the path of the ball
	obj = new BallPath(this->searchById(1));
	obj->setId(2);
	obj->scaleChange(0.005);
	objlist.push_back(obj);

	//add the targets
	targetGrid = new TargetGrid();
	obj = targetGrid;
	obj->setId(3);
	objlist.push_back(obj);

	//add cannon ball
	ballWorld = new CannonBall();
	obj = ballWorld;
	obj->setId(4);
	objlist.push_back(obj);


}

World::~World(){
	Shape *obj;
	while (!objlist.empty()) {
		obj = objlist.front();
		objlist.pop_front();
		free(obj);
	}
}


void World::draw() {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  (*it)->draw();
    }
}

void World::reset(){
	Shape *obj = NULL;

	obj = this->searchById(1);
	obj->reset();
	obj->setScale(0.5);
	obj->translate(2.5, 0, 0);

	obj = this->searchById(2);
	obj->reset();
	obj->setScale(0.5);
	obj->translate(4, 0, 0);

	obj = this->searchById(3);
	obj->reset();
	obj->setScale(0.5);

}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  if ((*it)->getId() == i) return *it;
    }
	return NULL;
}

int World::fireCannon(int yPos){
	return ballWorld->FireCannon(cannonWorld->cannonX, yPos, cannonWorld->cannonRotation,cannonWorld->cannonPower, targetGrid);
}

int World::getPlayerScore(){
	return targetGrid->getPlayerScore();
}

