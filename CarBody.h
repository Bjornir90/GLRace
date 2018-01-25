#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "GLmain.h"
#include "Object.h"

class CarBody : public Object
{
public:
	CarBody();
	virtual ~CarBody();
	void buildBody(int size, float reductionFactor);

	void draw();


private:
	void tesselate(int n);
};

