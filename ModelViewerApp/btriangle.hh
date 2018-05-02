#pragma once

#include "Point.h"

class BTriangle {
public:
	
	BTriangle(size_t degree, std::vector<Point> cp);
	Point eval(const Point &p) const;
	Mesh evalMesh(size_t resolution) const;

private:
	size_t degree;
	std::vector<Point> cp;
};
