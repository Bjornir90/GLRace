#include "stdafx.h"
#include "Cylinder.h"


Cylinder::Cylinder()
{

	_topRadius = 0;
	_baseRadius = 0;
	_height = 0;
}


Cylinder::~Cylinder()
{

}

// array is 71 floats (24 * 3 = 71).
void Cylinder::buildCylinder(float baseRadius, float height, int nbSlices)
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
	_topRadius = baseRadius;
	_height = height;

	// angular distance between two lines
	deltaPhi = 2 * M_PI / nbSlices;

	float *vertices = _vertices;
	float *normals = _normals;
	float *colors=_colors;
	float *texcoors = _texcoors;

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
		*normals = xPolar / normalNorm;
		*vertices = xPolar * baseRadius;
		*colors=0.2; //red

		normals++;
		vertices++;
		colors++;
		
		*normals = normY / normalNorm;
		*vertices = 0;
		*colors=0.2; //green

		normals++;
		vertices++;
		colors++;

		*normals = zPolar / normalNorm;
		*vertices = zPolar * baseRadius;
		*colors=0.2; //blue
		
		normals++;
		vertices++;
		colors++;
		
		*texcoors = (float)j / (float)nbSlices;
		texcoors++;
		*texcoors = 0.f;
		texcoors++;

		// vertex #2 (theta , phiPrime)
		*normals = xPolar / normalNorm;
		*vertices = xPolar * _topRadius;
		*colors=0.2; //red

		normals++;
		vertices++;
		colors++;

		*normals = (baseRadius - _topRadius) / height;
		*vertices = height;
		*colors=0.2; //green

		normals++;
		vertices++;
		colors++;

		*normals = zPolar / normalNorm;
		*vertices = zPolar * _topRadius;
		*colors=0.2; //blue;

		normals++;
		vertices++;
		colors++;

		*texcoors = (float)j / (float)nbSlices;
		texcoors++;
		*texcoors = 1.f;
		texcoors++;
	}
}

void Cylinder::draw() {
	// draw triangle strips from the currently bound VAO
	// with current in-use shader
	int nbStackTriangles = (_slices + 1) * 2;
	// draw triangles from the currently bound VAO with current in-use shader
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0,
		nbStackTriangles);
}
