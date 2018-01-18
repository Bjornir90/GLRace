#include "stdafx.h"
#include "Car.h"


Car::Car()
{
}


Car::~Car()
{
}


void Car::buildCar() {
	body = new CarBody();
	body->buildBody(28, 1);
	body->InitVBO();
}

void Car::draw() {
	glBindVertexArray(body->_vao);
	body->draw();
}