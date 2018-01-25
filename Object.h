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
	glm::mat4 getModel() { return _modelMatrix;}
	void setModel(glm::mat4 model) { _modelMatrix = model; }
	void updatePosition(GLfloat angle_x, GLfloat angle_y, GLfloat angle_z, glm::vec3 translation);
	

protected:
	float * _vertices;
	float * _normals;
	float * _texcoors;
	float * _colors;
	unsigned int _size; //Number of Vertices / Normals / Texture Coordonates
	glm::mat4 _modelMatrix;
};

