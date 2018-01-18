#pragma once

#include "CarBody.h"

class Car
{
public:
	Car();
	~Car();

	void buildCar();
	void draw();

protected:
	CarBody * body;
};

