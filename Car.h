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

protected:
	CarBody * body;
	Wheel * wheels[4];
	float * _wheelsOffset;
};

