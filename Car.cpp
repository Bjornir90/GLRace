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
	_angle_x = 0.0f;
	_angle_y = 0.0f;
	_angle_z = 0.0f;
}

void Car::draw() {
	body->draw();
	for (int i = 0; i < 4; i++) {
		wheels[i]->draw();
	}
}

void Car::move(glm::vec3 translation) {
	_position += translation;
	body->updatePosition(0, 0, 0, _position);
	for (int i = 0; i < 4; i++) {
		wheels[i]->updatePosition(0, 0, 0, _position);
	}
}

void Car::rotate(GLfloat angle_x, GLfloat angle_y, GLfloat angle_z) {
	_angle_x += angle_x;
	_angle_y += angle_y;
	_angle_z += angle_z;
	body->updatePosition(_angle_x, _angle_y, _angle_z, glm::vec3(0,0,0));
	for (int i = 0; i < 4; i++) {
		float norm = sqrt(_wheelsOffset[0] * _wheelsOffset[0] + _wheelsOffset[1] * _wheelsOffset[1] + _wheelsOffset[2] * _wheelsOffset[2]);
		wheels[i]->updatePosition(_angle_x, _angle_y, _angle_z, glm::vec3(0, 0, 0));
	}
}