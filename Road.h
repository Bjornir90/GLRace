#pragma once
#include <glm.hpp>
#include "Object.h"
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/norm.hpp>

#define ROAD_WIDTH 8.0f

class Road : public Object
{
public:
	Road();
	void buildRoad(glm::vec4 points[], unsigned int pointsCount);
	void draw();
	~Road();
	bool isRoad(float x, float y, unsigned int* pointID);
private:
	void computeInterfaceVertices(glm::vec4 pprevious, glm::vec4 p, glm::vec4 pnext, unsigned int pointID);

};

/*
--- EXAMPLE USE ---

Road* road;


-- SETUP: --

glm::vec4 points[] = {
	glm::vec4( 10.0f,  10.0f, 0.0f, 0.0f),
	glm::vec4( 10.0f, -10.0f, 0.0f, 0.0f),
	glm::vec4(-10.0f, -10.0f, 0.0f, 0.0f),
	glm::vec4(-10.0f,  10.0f, 0.0f, 0.0f)
};
road = new Road();
road->buildRoad(points, 4);
road->InitVBO();


-- AT EACH FRAME: --

// TODO bind object _modelMatrix
road->draw();

*/