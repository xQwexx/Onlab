#pragma once
#include <Eigen/Dense>
#include <math.h>
#include "Point.h"
#include <iostream>
class RBF
{
private:
	size_t n;
	Eigen::MatrixXd V;
	Eigen::MatrixXi F;
	Eigen::MatrixXd fiMatrix;
	Eigen::VectorXd z;
	Eigen::VectorXd a;
	double inline fi(double r);
	double inline calcR(Eigen::VectorXd p1, Eigen::VectorXd p2);
public:
	RBF(Eigen::MatrixXd V, Eigen::MatrixXi F);
	~RBF();
	double interp(Eigen::VectorXd p);
	Mesh interpol(double size, unsigned scale);
};

