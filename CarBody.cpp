#include "stdafx.h"
#include "CarBody.h"
#include "Wheel.h"

CarBody::CarBody() : Object::Object()
{
}


CarBody::~CarBody()
{
}

void CarBody::tesselate(int n) { //subdivise each rectangle n times in 4
	int newSize = _size * pow(4, n);//Number of vertices after tesselation
	/*float * newVertices = (float *)malloc(sizeof(float)*newSize); //Temporary array where we put all vertices (new and old)
	float * newColors = (float *)malloc(sizeof(float)*newSize);
	float * newNormals = (float *)malloc(sizeof(float)*newSize);*/
	float * newVertices = new float[newSize*3];
	float * newColors = new float[newSize*3];
	float * newNormals = new float[newSize*3];
	for (int i = 0; i < n; i++) {
		int newVertexIndex = 0;
		printf("N : %d\n", i+1);
		for (int vertexIndex = 0; vertexIndex < _size*3; vertexIndex+=12) { //Iterate over every squares
			float firstVertex[3] = { _vertices[vertexIndex], _vertices[vertexIndex + 1], _vertices[vertexIndex + 2] };
			float secondVertex[3] = { _vertices[vertexIndex + 3], _vertices[vertexIndex + 4], _vertices[vertexIndex + 5] };
			float thirdVertex[3] = { _vertices[vertexIndex + 6], _vertices[vertexIndex + 7], _vertices[vertexIndex + 8] };
			float fourthVertex[3] = { _vertices[vertexIndex + 9], _vertices[vertexIndex + 10], _vertices[vertexIndex + 11] };
			printf("Vertex Index : %d / %d\n", vertexIndex, _size*3);

			float firstMidpoint[3];
			float secondMidpoint[3];
			float thirdMidpoint[3];
			float fourthMidpoint[3];
			float center[3];
			float colors[3] = { _colors[vertexIndex], _colors[vertexIndex+1], _colors[vertexIndex+2] };//All new surfaces share same colors and normals
			float normals[3] = { _normals[vertexIndex], _normals[vertexIndex + 1], _normals[vertexIndex + 2] };

			printf("Colors : R:%f G:%f B:%f\n", colors[0], colors[1], colors[2]);

			for (int j = 0; j < 3; j++) {
				firstMidpoint[j] = (firstVertex[j] + secondVertex[j]) / 2;//Calculate midpoints
				secondMidpoint[j] = (secondVertex[j] + thirdVertex[j]) / 2;
				thirdMidpoint[j] = (thirdVertex[j] + fourthVertex[j]) / 2;
				fourthMidpoint[j] = (firstVertex[j] + fourthVertex[j]) / 2;
				center[j] = (firstVertex[j] + thirdVertex[j]) / 2; //Center of a square is the middle of diagonal
			}

			for (int j = vertexIndex * 4; j < vertexIndex * 4 + 4*4*3; j++) {
				int modulo = j % 3;
				//printf("J : %d : %d color : %f\n", j, modulo, colors[modulo]);
				newColors[j] = colors[modulo];
				//printf("J : %d : %d newColor : %f\n", j, modulo, newColors[j]);
				newNormals[j] = normals[modulo];
			}
			/*for (int k = vertexIndex * 4; k < vertexIndex * 4 + 4 * 4 * 3; k += 3) {
				printf("%d/%d : Colors : %f %f %f\n", k, newSize * 3, newColors[k], newColors[k + 1], newColors[k + 2]);
			}*/
			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = firstVertex[j];//Add first vertex in the new array
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++; //Update index of the temp array
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = firstMidpoint[j];//Add first midpoint in the new array
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++; //Update index of the temp array
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = center[j];//Add center in the new array
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++; //Update index of the temp array
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = fourthMidpoint[j];//Add last midpoint in the new array
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++; //Update index of the temp array
			}



			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = secondVertex[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++; 
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = firstMidpoint[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++; 
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = center[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++; 
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = secondMidpoint[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++; 
			}




			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = thirdVertex[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++;
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = secondMidpoint[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++;
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = center[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++;
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = thirdMidpoint[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++;
			}


			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = fourthVertex[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++;
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = thirdMidpoint[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++;
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = center[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++;
			}

			for (int j = 0; j < 3; j++) {
				newVertices[newVertexIndex] = fourthMidpoint[j];
				//newColors[newVertexIndex] = colors[j];
				//newNormals[newVertexIndex] = normals[j];
				newVertexIndex++;
			}
		}
	}
	_size = newSize;
	_vertices = new float[_size * 3];
	_colors = new float[_size * 3];
	_normals = new float[_size * 3];
	for (int index = 0; index < _size * 3; index++) {
		_vertices[index] = newVertices[index];
		//printf("%d : %f -> ", index, newColors[index]);
		_colors[index] = newColors[index];
		/*printf("%f ", _colors[index]);
		if ((index+1) % 3 == 0) {
			printf("\n");
		}*/
		_normals[index] = newNormals[index];
	}
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

	_size = size;
	_vertices = new float[_size * 3];
	_normals = new float[_size * 3];
	_colors = new float[_size * 3];
	_texcoors = new float[_size * 2];

	for (unsigned int i = 0; i<_size * 3; i++)
	{
		_vertices[i] = vertices[i];
		_normals[i] = normals[i];
		_colors[i] = colors[i];
	}

	for (unsigned int i = 0; i<_size * 2; i++)
	{
		_texcoors[i] = texCoord[i];
	}

	/*CarBody::tesselate(1);
	CarBody::tesselate(1);
	CarBody::tesselate(1);
	CarBody::tesselate(1);
	*/
}


void CarBody::draw() {
	glBindVertexArray(_vao);
	glDrawArrays(GL_QUADS, 0, getSize());
}

