#pragma once
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "stdlib.h"
#include "math.h"
#include "GLmain.h"

class Object
{
public:
	Object();
	~Object();
	unsigned int _vao;
	void InitVBO(void);
	unsigned int getSize() { return _size; }

protected:
	float * _vertices;
	float * _normals;
	float * _texcoors;
	float * _colors;
	unsigned int _size; //Number of Vertices / Normals / Texture Coordonates
	glm::mat4 modelMatrix;
};

