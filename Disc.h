#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#define _USE_MATH_DEFINES 
#include <cmath>
#include "Object.h"
class Disc :
	public Object
{
public:
	Disc();
	~Disc();
	void buildDisc(float baseRadius, float height, int nbSlices);
	void draw();

	unsigned int getSize() { return _size; }
	unsigned int getSlices() { return _slices; }

	float        _baseRadius;
	float		 _height;
	float        _angle; //time variation of the rotation angle


protected:
	int _slices;
};

