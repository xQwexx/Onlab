#include "RBF.h"



RBF::RBF(Eigen::MatrixXd V,Eigen::MatrixXi F)
{
	this->V = V;
	this->F = F;
	n = V.size() / 3;
	fiMatrix.resize(n, n);
	z.resize(n);
	//a.resize(n);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			fiMatrix.row(i)[j] = fi(calcR(V.row(j), V.row(i)));
		}
		z[i] = V.row(i)[2];
	}
	a = fiMatrix.inverse() * z;
	std::cout << a;
	//std::cout << fiMatrix.inverse();
}


RBF::~RBF()
{
}

double inline RBF::fi(double r)
{
	double c = 1;
	return exp((pow(c*r,2))*-1);  // eˇ-((cr)ˇ2)
}

double inline RBF::calcR(Eigen::VectorXd p1, Eigen::VectorXd p2)
{
	return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
}

double RBF::interp(Eigen::VectorXd p)
{
	double z = 0;
	for (size_t i = 0; i < n; i++)
	{
		z += a[i] * fi(calcR(p, V.row(i)));
	}
	return z;
}

Mesh RBF::interpol(double size, unsigned scale)
{
	Mesh m;
	double pos = size / 2;
	for (size_t i = 0; i <= scale; ++i) {
		double u = (double)i / scale * size - pos;
		for (size_t j = 0; j <= scale; ++j) {
			double v = (double)j / scale * size - pos;
			m.points.emplace_back(Point{ u, v, interp(Eigen::Vector2d{ u, v }) });
		}
	}
	for (size_t i = 0; i <= scale - 1; ++i) {
		double u = ((double)i+0.5) / scale * size - pos;
		for (size_t j = 0; j <= scale - 1; ++j) {
			double v = ((double)j + 0.5) / scale * size - pos;
			double w = 1.0 - u - v;
			m.points.emplace_back(Point{ u, v, interp(Eigen::Vector2d{ u, v }) });
		}
	}
	size_t index = 0;
	size_t center = (scale+1) * (scale+1);
	for (size_t i = 0; i < scale; ++i, ++index)
		for (size_t j = 0; j < scale; ++j, ++index) {
			size_t next = index + scale+1;
			m.triangles.push_back({ index, center, index + 1 });
			m.triangles.push_back({ index + 1, center, next + 1 });
			m.triangles.push_back({ next + 1, center, next });
			m.triangles.push_back({ next, center, index });
			center++;
			//if (j != 0)
			//	m.triangles.push_back({ index, next + 1, next });
		}
	return m;
}