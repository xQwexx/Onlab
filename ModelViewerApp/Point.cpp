#include "Point.h"

Point::Point(double x, double y, double z) : data{ x, y, z }
{
}

Point::Point(Eigen::Vector3d p)
{
	data[0] = (double)p[0];
	data[1] = (double)p[1];
	data[2] = (double)p[2];
}

double Point::operator[](size_t i) const {
	return data[i];
}

Point Point::operator*(double x) const {
	return{ data[0] * x, data[1] * x, data[2] * x };
}

void Point::operator+=(const Point &p) {
	data[0] += p.data[0];
	data[1] += p.data[1];
	data[2] += p.data[2];
}

Point Point::operator+(const Point &p) const {
	Point re;
	re.data[0] += p.data[0] + data[0];
	re.data[1] += p.data[1] + data[1];
	re.data[2] += p.data[2] + data[2];
	return re;
}


Point Point::operator/(const double x) const {
	return{ data[0] / x, data[1] / x, data[2] / x };
}

Mesh Mesh::operator+(const Mesh &m) const {
	Mesh re;
	re.points = points;
	for (const auto &p : m.points)
		re.points.emplace_back(p);
	size_t pointSize = points.size();
	re.triangles = triangles;
	for (const auto &t : m.triangles)
		re.triangles.push_back({ pointSize+t[0], pointSize+t[1], pointSize+t[2] });
	return re;
}