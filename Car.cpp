#include "stdafx.h"
#include "Car.h"


Car::Car()
{
	_wheelsOffset = NULL;
	_position = glm::vec3(0.0f);
}


Car::~Car()
{
}


void Car::buildCar() {
	float wheelsOffset[] = { 1.7, -0.7, 1.5,
		-1.7, -0.7, 1.5,
		1.7, -0.7, -1.5,
		-1.7, -0.7, -1.5
	};

	_wheelsOffset = new float[12];

	for (unsigned int i = 0; i < 12; i++) {
		_wheelsOffset[i] = wheelsOffset[i];
	}

	body = new CarBody();
	body->buildBody(28, 1);
	body->InitVBO();

	for (int i = 0; i < 4; i++) {
		wheels[i] = new Wheel();
		glm::vec3 offset = glm::vec3(_wheelsOffset[i * 3], _wheelsOffset[i * 3 + 1], _wheelsOffset[i * 3 + 2]);
		wheels[i]->setModel(glm::translate(wheels[i]->getModel(), offset));
		wheels[i]->buildWheel();
	}
	//Car::rotate(3.1415 / 2, 0, 0);
}

void Car::draw() {
	body->draw();
	for (int i = 0; i < 4; i++) {
		wheels[i]->draw();
	}
}

void Car::move(glm::vec3 translation) {
	body->updatePosition(0, 0, 0, translation);
	for (int i = 0; i < 4; i++) {
		wheels[i]->updatePosition(0, 0, 0, translation);
	}
}

void Car::rotate(GLfloat angle_x, GLfloat angle_y, GLfloat angle_z) {
	body->updatePosition(angle_x, angle_y, angle_z, glm::vec3(0,0,0));
	for (int i = 0; i < 4; i++) {
		wheels[i]->updatePosition(0, 0, 0, glm::vec3(-_wheelsOffset[i * 3], -_wheelsOffset[i * 3 + 1], -_wheelsOffset[i * 3 + 2]));
		wheels[i]->updatePosition(angle_x, angle_y, angle_z, glm::vec3(0, 0, 0));
		wheels[i]->updatePosition(0, 0, 0, glm::vec3(_wheelsOffset[i * 3], _wheelsOffset[i * 3 + 1], _wheelsOffset[i * 3 + 2]));
	}
}