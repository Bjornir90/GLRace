#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "GLmain.h"

class CarBody
{
public:
	CarBody();
	virtual ~CarBody();
	void buildBody(int size, float reductionFactor);
	void InitVBO(void);

	void draw();

	unsigned int getSize() { return _size; }

	unsigned int _vao;

protected:
	float * _vertices;
	float * _normals;
	float * _colors;
	float * _texcoors;
	float * _wheelsOffset;
	glm::mat4 modelMatrix;
	unsigned int _size; //Number of Vertices / Normals / Texture Coordinates
};

