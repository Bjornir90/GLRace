#pragma once

#include "CarBody.h"
#include "Wheel.h"

class Car
{
public:
	Car();
	~Car();

	void Car::buildCar();
	void Car::draw();
	void Car::move(glm::vec3 translation);
	CarBody * body;
	Wheel * wheels[4];
	void Car::rotate(GLfloat angle_x, GLfloat angle_y, GLfloat angle_z);

protected:
	float * _wheelsOffset;
	float _angle_x, _angle_y, _angle_z;
	glm::vec3 _position;
};

