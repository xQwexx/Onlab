#pragma once

#include "Point.h"
class CTTriangle
{
private:
	Point vertices[19];
public:
	CTTriangle(Point vertices[3], Point n[3]);
	~CTTriangle();
	Mesh evalMesh() const;
};

