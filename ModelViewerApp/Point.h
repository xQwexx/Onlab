#pragma once
#include <Eigen/Dense>
#include <array>
#include <vector>

struct Point {
	double data[3];
	Point(double x = 0.0, double y = 0.0, double z = 0.0);
	Point(Eigen::Vector3d p);
	double operator[](size_t i) const;
	Point operator*(double x) const;
	void operator+=(const Point &p);
	Point operator+(const Point &p) const;
	Point operator/(const double x) const;
};

struct Mesh {
	using Triangle = std::array<size_t, 3>;
	std::vector<Point> points;
	std::vector<Triangle> triangles;
	Mesh operator+(const Mesh &m) const;
};
