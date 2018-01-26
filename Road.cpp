#include "stdafx.h"
#include "Road.h"
#include <iostream>

void displayvector(glm::vec3 vector) {
	float* data = glm::value_ptr(vector);
	for (int i = 0; i < 3; i++)
		std::cout << data[i] << ' ';
	std::cout << std::endl;
}

Road::Road()
{

}

void Road::buildRoad(glm::vec4 points[], unsigned int pointsCount)
{
	// checking size and setting the nb of vertices
	if (pointsCount < 2) {
		_size = 0;
		return;
	}
	else if (pointsCount == 2)
		_size = 4;
	else
		_size = 2* pointsCount + 2;
	
	// std::cout << pointsCount << " points, " << _size << " vertices." << std::endl;

	_vertices = new float[_size * 3];
	_normals = new float[_size * 3];
	_colors = new float[_size * 3];

	if (pointsCount == 2) {
		computeInterfaceVertices(points[0], points[0], points[1], 0);
		computeInterfaceVertices(points[0], points[1], points[1], 1);
	}
	else {
		computeInterfaceVertices(points[pointsCount - 1], points[0], points[1], 0);
		for (unsigned int i = 1; i < pointsCount - 1; i++) {
			computeInterfaceVertices(points[i - 1], points[i], points[i + 1], i);
		}
		computeInterfaceVertices(points[pointsCount - 2], points[pointsCount - 1], points[0], pointsCount - 1);
		computeInterfaceVertices(points[pointsCount - 1], points[0], points[1], pointsCount); // last vertices identical to 2 first ones, to connect end with beginning
	}

	const float color[3] = { 0.6, 0.6, 0.8 };
	for (int i = 0; i < _size*3; i++) {
		_colors[i] = color[i % 3];
	}

	_modelMatrix = glm::mat4(1.0f);

}


Road::~Road()
{
}

void Road::computeInterfaceVertices(glm::vec4 pprevious, glm::vec4 p, glm::vec4 pnext, unsigned int pointID)
{
	/* std::cout << "COMPUTING VERTICES FOR POINT " << pointID << std::endl; */

	// the point vectors are formatted as (x, y, z, left-right tilt angle of the frangment)

	// AB and BC vectors
	glm::vec3 dir1 = p - pprevious;
	dir1 /= glm::l2Norm(dir1);
	glm::vec3 dir2 = pnext - p;
	dir2 /= glm::l2Norm(dir2);

	/* std::cout << "	DIRECTION1 VECTOR" << std::endl << "\t\t";
	displayvector(dir1);
	std::cout << "	DIRECTION2 VECTOR" << std::endl << "\t\t";
	displayvector(dir2); */

	// create a vector pointing upwards, but tilt angle
	glm::vec3 up = glm::rotate(glm::vec3(0.0, 0.0, 1.0), p[3], dir1);

	// vectors normal to road direction, pointing to the left
	glm::vec3 normal1 = glm::cross(up, dir1);
	glm::vec3 normal2 = glm::cross(up, dir2);

	// average of these two vectors
	glm::vec3 diagonal = normal1 + normal2;
	diagonal /= 2;
	diagonal /= glm::l2Norm(diagonal);
	diagonal *= ROAD_WIDTH / glm::dot(normal1, diagonal);

	/* std::cout << "	DIAGONAL VECTOR" << std::endl << "\t\t";
	displayvector(diagonal); */

	glm::vec3 leftVertexCoords = glm::vec3(p) + diagonal;
	glm::vec3 rightVertexCoords = glm::vec3(p) - diagonal;

	glm::vec3 surfaceNormal = glm::cross(dir1 + dir2, diagonal);
	
	/* std::cout << "	LEFT VERTEX COORDS" << std::endl << "\t\t";
	displayvector(leftVertexCoords);
	std::cout << "	RIGHT VERTEX COORDS" << std::endl << "\t\t";
	displayvector(rightVertexCoords); */

	// copying to proper object arrays
	for (int i = 0; i < 3; i++) {
		_vertices[pointID * 6 + i] = leftVertexCoords[i];
		_vertices[pointID * 6 + 3 + i] = rightVertexCoords[i];
		_normals[pointID * 6 + i] = surfaceNormal[i];
		_normals[pointID * 6 + 3 + i] = surfaceNormal[i];
	}
}

bool Road::isRoad(float x, float y, unsigned int* pointID)
{
	
}


void Road::draw() {
	// draw triangle strips from the currently bound VAO
	// with current in-use shader
	//int nbStackTriangles = (_slices + 1) * 2;
	// draw triangles from the currently bound VAO with current in-use shader
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0,
		_size);
}
