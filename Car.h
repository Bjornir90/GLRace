#pragma once

#include "CarBody.h"
#include "Wheel.h"

class Car
{
public:
	Car();
	~Car();

	void buildCar();
	void draw();
	void move(glm::vec3 translation);
	glm::vec3 _position;

protected:
	CarBody * body;
	Wheel * wheels[4];
	float * _wheelsOffset;
};

