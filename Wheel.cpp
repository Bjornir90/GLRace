#include "stdafx.h"
#include "Wheel.h"


Wheel::Wheel()
{
	_baseRadius = 0.5;
	_height =0.1;
	_angle = 0;

}


Wheel::~Wheel()
{
}

void Wheel::buildWheel() {
	_side[LEFT] = new Disc();
	_side[RIGHT] = new Disc();
	_edge = new Cylinder();

	_side[LEFT]->buildDisc(_baseRadius, 0.0, 20);
	_side[RIGHT]->buildDisc(_baseRadius, _height, 20);
	_edge->buildCylinder(_baseRadius, _height, 20);

	_side[LEFT]->InitVBO();
	_side[RIGHT]->InitVBO();
	_edge->InitVBO();
}

void Wheel::draw()
{
	glBindVertexArray(_side[LEFT]->_vao);
	_side[LEFT]->draw();
	glBindVertexArray(_side[RIGHT]->_vao);
	_side[RIGHT]->draw();
	glBindVertexArray(_edge->_vao);
	_edge->draw();
}