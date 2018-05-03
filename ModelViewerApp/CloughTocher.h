#pragma warning(disable:4996)
#define D_SCL_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include "btriangle.hh"
#include "CTTriangle.h"
#include <list>
#include <Eigen/Dense>
#include <igl/readOFF.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/per_vertex_normals.h>
#include <igl/flipped_triangles.h>
#include <map>

class CloughTocher
{
private:
	//double coord[][5];
	Eigen::MatrixXd V;
	Eigen::MatrixXi F;
	Eigen::MatrixXd N;

	Eigen::MatrixXd calcV;
	Eigen::MatrixXi calcF;

	//unsigned tempPoint[];

	unsigned searchPointIndex(unsigned parent1, unsigned parent2, unsigned index);
	Eigen::VectorXf calcPoint(unsigned pointIndex, Eigen::MatrixXd calcPoint);
	Eigen::VectorXf calcPoint(unsigned pointIndex, Eigen::MatrixXd calcPoint, Eigen::VectorXd normal);
	Eigen::VectorXf calcPoint(Eigen::VectorXd point, Eigen::VectorXd calcPoint, Eigen::VectorXd normal);
	//listOfInts.push_back(1);
public:
	CloughTocher();
	~CloughTocher();
	void calcModel();
	Eigen::MatrixXd getVertex() { return calcV; };
	Eigen::MatrixXi getFace() { return calcF; };
};

