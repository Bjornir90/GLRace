#include "stdafx.h"
#include "CarBody.h"


CarBody::CarBody()
{
	_size = 0;
	_vertices = _normals = _texcoors = _wheelsOffset = NULL;
	_colors = NULL;
	_vao = 0;
}


CarBody::~CarBody()
{
}


void CarBody::buildBody(int size, float reductionFactor) {
	// vertices array
	float vertices[] = { 1.5, 1, 2,  -1.5, 1, 2,   -1.5, -1, 2,		1.5, -1, 2, //front face
		1.5, 1, 2,   1.5, -1, 2,	1.5, -1, -2,  1.5, 1, -2,//Left face
		-1.5, 1, -2,   -1.5, -1, -2,	1.5, -1, -2,  1.5, 1, -2,//back face
		-1.5, 1, 2,   -1.5, 1, -2,	-1.5, -1, -2,  -1.5, -1, 2,//right face
		1.5, 1, 2,   1.5, 1, -2,	-1.5, 1, -2,  -1.5, 1, 2, //top face
		1.5, -1, 2,   1.5, -1, -2,	-1.5, -1, -2,  -1.5, -1, 2, //bottom face
		1.5, 1, 1.5,  -1.5, 1, 1.5, -1.5, 2, 0.5,		1.5, 2, 0.5, };//windshield

	// normal array
	float normals[] = { 0, 0, 1,  0, 0, 1,   0, 0, 1,	0, 0, 1,
		1, 0, 0,   1, 0, 0, 	1, 0, 0,  1, 0, 0,
		0, 0, -1,   0, 0, -1, 	0, 0, -1,  0, 0, -1,
		-1, 0, 0,   -1, 0, 0, 	-1, 0, 0,  -1, 0, 0,
		0, 1, 0,   0, 1, 0, 	0, 1, 0,  0, 1, 0,
		0, -1, 0,   0, -1, 0, 	0, -1, 0,  0, -1, 0,
		0, 0.5, 0.5,   0, 0.5, 0.5,     0, 0.5, 0.5,  0, 0.5, 0.5, };

	// color array
	float colors[] = { 0.2, 1, 0.2,  0.2, 1, 0.2,   0.2, 1, 0.2,	0.2, 1, 0.2,
		0.2, 1, 0.2,  0.2, 1, 0.2,   0.2, 1, 0.2,	0.2, 1, 0.2,
		0.2, 1, 0.2,  0.2, 1, 0.2,   0.2, 1, 0.2,	0.2, 1, 0.2,
		0.2, 1, 0.2,  0.2, 1, 0.2,   0.2, 1, 0.2,	0.2, 1, 0.2,
		0.2, 1, 0.2,  0.2, 1, 0.2,   0.2, 1, 0.2,	0.2, 1, 0.2,
		0.2, 1, 0.2,  0.2, 1, 0.2,   0.2, 1, 0.2,	0.2, 1, 0.2,
		0.5, 0.5, 1,	0.5, 0.5, 1,	0.5, 0.5, 1,	0.5, 0.5, 1};

	// texCoord array
	float texCoord[] = { 0, 0,   0, 0,   0, 0,	0, 0,
		0, 0,   0, 0,   0, 0,	0, 0,
		0, 0,   0, 0,   0, 0,	0, 0,
		0, 0,   0, 0,   0, 0,	0, 0,
		0, 0,   0, 0,   0, 0,	0, 0,
		0, 0,   0, 0,   0, 0,	0, 0, 
		0, 0,   0, 0,   0, 0,	0, 0, };

	//Position of wheels relative to center of car (CoG)

	//Avant gauche; avant droite; arriere gauche; arriere droite
	float wheelsOffset[] = { 1, -0.5, 1.5,
		-1, -0.5, 1.5,
		1, -0.5, -1.5,
		-1, -0.5, -1.5
	};

	_size = size;
	_vertices = new float[_size * 3];
	_normals = new float[_size * 3];
	_colors = new float[_size * 3];
	_wheelsOffset = new float[12];
	_texcoors = new float[_size * 2];

	for (unsigned int i = 0; i<_size * 3; i++)
	{
		_vertices[i] = vertices[i]*reductionFactor;
		_normals[i] = normals[i];
		_colors[i] = colors[i];
	}

	for (unsigned int i = 0; i<_size * 2; i++)
	{
		_texcoors[i] = texCoord[i];
	}

	for (unsigned int i = 0; i < 12; i++) {
		_wheelsOffset[i] = wheelsOffset[i];
	}
}


void CarBody::InitVBO(void) {
	// vertex buffer objects and vertex array
	unsigned int vboVertices = 0;
	//creates 1 buffer at the identifier "vboVertices"
	glGenBuffers(1, &vboVertices);
	//bind the buffer and tell it which kind of buffer it is. in this case, just an array
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	//load data into the buffer. (type of buffer, size of buffer, pointer to data, kind of usage)
	glBufferData(GL_ARRAY_BUFFER,
		3 * _size * sizeof(float),
		_vertices,
		GL_STATIC_DRAW);

	unsigned int vboColors = 0;
	glGenBuffers(1, &vboColors);
	glBindBuffer(GL_ARRAY_BUFFER, vboColors);
	glBufferData(GL_ARRAY_BUFFER,
		3 * _size * sizeof(float),
		_colors,
		GL_STATIC_DRAW);

	unsigned int vboNormals = 0;
	glGenBuffers(1, &vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glBufferData(GL_ARRAY_BUFFER,
		3 * _size * sizeof(float),
		_normals,
		GL_STATIC_DRAW);

	_vao = 0;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// vertex positions are location 0
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	//make OpenGL understand what the vertex is (position of the vertex to be defined, size (2 for 2D), type, normalized between 0 and 1,
	//size of one vertex, offset of the first component to the vertex to be defined)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(0);

	// vertex colors are location 1
	glBindBuffer(GL_ARRAY_BUFFER, vboColors);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(1); // don't forget this!

								  // vertex normals are location 2
	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(2); // don't forget this!

}

void CarBody::draw() {
	glDrawArrays(GL_QUADS, 0, getSize());
}