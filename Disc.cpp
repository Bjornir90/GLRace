#include "stdafx.h"
#include "Disc.h"


Disc::Disc()
{
	_baseRadius = 0;
	_height = 0;
}


Disc::~Disc()
{
}

void Disc::buildDisc(float baseRadius, float height, int nbSlices)
{
	float deltaPhi;
	// vertex, normal and texture coordinates
	_slices = nbSlices;
	_size = (nbSlices + 1) * 2;

	_vertices = new float[_size * 3];
	_normals = new float[_size * 3];
	_colors = new float[_size * 3];
	_texcoors = new float[_size * 2];

	_baseRadius = baseRadius;
	_height = height;
	
	//if (height==0){
		int sign=-1;
	//}
	// angular distance between two lines
	deltaPhi = 2 * M_PI / nbSlices;

	float *vertices = _vertices;
	float *normals = _normals;
	float *texcoors = _texcoors;
	float *colors = _colors;

	// triangle strips made of vertical stacks
	// tesselating the triangle strip into nbSlices
	// note <= instead of < for making sure that the last angle is used
	for (int j = 0; j <= nbSlices; j++) {
		// polar angle
		float phi = j * deltaPhi;

		// polar vector in a vertical plane
		float xPolar = cos(phi);
		float zPolar = sin(phi);

		float normY = 0;// (height != 0 ? (baseRadius - _topRadius) / height : 0);

		float normalNorm = sqrt(1 + normY * normY);

		// vertex #1 (theta , phi)
		*normals = sign*1;
		*vertices = xPolar * baseRadius;
		*colors=0.8; //red

		normals++;
		vertices++;
		colors++;

		*normals = sign*1;
		*vertices = height;
		*colors=0.8; //green

		normals++;
		vertices++;
		colors++;

		*normals = sign*1;
		*vertices = zPolar * baseRadius;
		*colors=0.8;//blue

		normals++;
		vertices++;
		colors++;

		*texcoors = (float)j / (float)nbSlices;
		texcoors++;
		*texcoors = 0.f;
		texcoors++;

		// vertex #2 (theta , phiPrime)
		*normals = sign*1;
		*vertices = height;
		*colors=0.8;//red

		normals++;
		vertices++;
		colors++;

		*normals = sign*1;
		*vertices = height; 
		*colors=0.8; //green

		normals++;
		vertices++;
		colors++;

		*normals = sign*1;
		*vertices = height;
		*colors=0.8;//blue

		normals++;
		vertices++;
		colors++;

		*texcoors = (float)j / (float)nbSlices;
		texcoors++;
		*texcoors = 1.f;
		texcoors++;
	}
}

void Disc::draw() {
	// draw triangle strips from the currently bound VAO
	// with current in-use shader
	int nbStackTriangles = (_slices + 1) * 2;
	// draw triangles from the currently bound VAO with current in-use shader
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0,
		nbStackTriangles);
}