#pragma once
#include "Object.h"
#include "Disc.h"
#include "Cylinder.h"

class Wheel :
	public Object
{
public:
	Wheel();
	~Wheel();

	void buildWheel();
	void draw();

	float        _baseRadius;
	float        _height;
	float		 _angle; //time variation of the rotation angle

	enum part { LEFT = 0, RIGHT = 1 };

	Disc *_side[2];
	Cylinder *_edge;


protected:
	int _slices;
};

