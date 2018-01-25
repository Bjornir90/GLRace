#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	_size = 0;
	_vertices = _normals = _texcoors = _colors = NULL;
	_vao = 0;
}

Object::~Object()
{
	if (_vertices != NULL)
		delete[] _vertices;

	if (_normals != NULL)
		delete[] _normals;

	if (_colors != NULL)
		delete[] _colors;

	if (_texcoors != NULL)
		delete[] _texcoors;
}

void Object::InitVBO(void) {
	// vertex buffer objects and vertex array
	unsigned int vboVertices = 0;
	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER,
		3 * _size * sizeof(float),
		_vertices,
		GL_STATIC_DRAW);

	unsigned int vboNormals = 0;
	glGenBuffers(1, &vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glBufferData(GL_ARRAY_BUFFER,
		3 * _size * sizeof(float),
		_normals,
		GL_STATIC_DRAW);

	unsigned int vboColors = 0;
	glGenBuffers(1, &vboColors);
	glBindBuffer(GL_ARRAY_BUFFER, vboColors);
	glBufferData(GL_ARRAY_BUFFER,
		3 * _size * sizeof(float),
		_colors,
		GL_STATIC_DRAW);

	_vao = 0;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// vertex positions are location 0
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(0);

	// vertex colors are location 1
	glBindBuffer(GL_ARRAY_BUFFER, vboColors);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(1); // don't forget this!

	// normals are location 2
	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(2); // don't forget this!


}


void Object::updatePosition(GLfloat angle_x, GLfloat angle_y, GLfloat angle_z, glm::vec3 translation) {
	_modelMatrix = glm::rotate(_modelMatrix, angle_z, glm::vec3(0, 0, 1));
	_modelMatrix = glm::rotate(_modelMatrix, angle_y, glm::vec3(0, 1, 0));
	_modelMatrix = glm::rotate(_modelMatrix, angle_x, glm::vec3(1, 0, 0));
	_modelMatrix = glm::translate(_modelMatrix, translation);
}