#include "CloughTocher.h"



CloughTocher::CloughTocher()
{
	// Load a mesh in OFF format
	igl::readOBJ("B:/MyPrograms/VisualStudio/BME/ModelViewerApp/ModelViewerApp/proba.obj", V, F);
	//igl::readOFF("B:/MyPrograms/VisualStudio/BME/ModelViewerApp/ModelViewerApp/bunny.off", V, F);
	
	igl::per_vertex_normals(V, F, N);
	calcModel();
	// Plot the mesh
	igl::opengl::glfw::Viewer viewer;
	viewer.data().set_mesh(calcV, calcF);
	viewer.launch();
}


CloughTocher::~CloughTocher()
{
}

void CloughTocher::calcModel() {
	calcV.resize(V.size()/3 + F.size()/3 * 1500, 3);
	calcF.resize(F.size()/3 * 2700, 3);
	calcF.fill(0);
	unsigned oVertexSize = V.size() / 3;
	for (unsigned i = 0; i < oVertexSize; ++i)
		calcV.row(i) = V.row(i);
	
	size_t vertexIndex = 0;
	size_t faceIndex = 0;
	Mesh mesh;

	for (unsigned i = 0; i < F.size()/3; ++i) {
		//calcV.row(i) = V.row(i);
		
		unsigned A = F.coeff(i, 0);
		unsigned B = F.coeff(i, 1);
		unsigned C = F.coeff(i, 2);
		Point v[3] = { V.row(A), V.row(B), V.row(C) };
		Point n[3] = { N.row(A), N.row(B), N.row(C) };
		CTTriangle triangle(v, n);
		mesh = mesh + triangle.evalMesh();
		
		/*
		Eigen::MatrixXd weightPoint = ( V.row(A) + V.row(B) + V.row(C)) / 3;
		calcV.row(oVertexSize + 16 * i + 0) = calcPoint(A, (2 * V.row(A) + V.row(B)) / 3, (N.row(A) + N.row(B)) / 2);
		calcV.row(oVertexSize + 16 * i + 1) = calcPoint(B, (2 * V.row(B) + V.row(A)) / 3, (N.row(B) + N.row(A)) / 2);
		calcV.row(oVertexSize + 16 * i + 2) = calcPoint(B, (2 * V.row(B) + V.row(C)) / 3, (N.row(B) + N.row(C)) / 2);
		calcV.row(oVertexSize + 16 * i + 3) = calcPoint(C, (2 * V.row(C) + V.row(B)) / 3, (N.row(C) + N.row(B)) / 2);
		calcV.row(oVertexSize + 16 * i + 4) = calcPoint(C, (2 * V.row(C) + V.row(A)) / 3, (N.row(C) + N.row(A)) / 2);
		calcV.row(oVertexSize + 16 * i + 5) = calcPoint(A, (2 * V.row(A) + V.row(C)) / 3, (N.row(A) + N.row(C)) / 2);
		/*
		calcV.row(oVertexSize + 16 * i + 0) = calcPoint(A, (2 * V.row(A) + V.row(B)) / 3, (2 * N.row(A) + N.row(B)) / 3);
		calcV.row(oVertexSize + 16 * i + 1) = calcPoint(B, (2 * V.row(B) + V.row(A)) / 3, (2 * N.row(B) + N.row(A)) / 3);
		calcV.row(oVertexSize + 16 * i + 2) = calcPoint(B, (2 * V.row(B) + V.row(C)) / 3, (2 * N.row(B) + N.row(C)) / 3);
		calcV.row(oVertexSize + 16 * i + 3) = calcPoint(C, (2 * V.row(C) + V.row(B)) / 3, (2 * N.row(C) + N.row(B)) / 3);
		calcV.row(oVertexSize + 16 * i + 4) = calcPoint(C, (2 * V.row(C) + V.row(A)) / 3, (2 * N.row(C) + N.row(A)) / 3);
		calcV.row(oVertexSize + 16 * i + 5) = calcPoint(A, (2 * V.row(A) + V.row(C)) / 3, (2 * N.row(A) + N.row(C)) / 3);

		calcV.row(oVertexSize + 16 * i + 0) = calcPoint(A, (2 * V.row(A) + V.row(B)) / 3);
		calcV.row(oVertexSize + 16 * i + 1) = calcPoint(B, (2 * V.row(B) + V.row(A)) / 3);
		calcV.row(oVertexSize + 16 * i + 2) = calcPoint(B, (2 * V.row(B) + V.row(C)) / 3);
		calcV.row(oVertexSize + 16 * i + 3) = calcPoint(C, (2 * V.row(C) + V.row(B)) / 3);
		calcV.row(oVertexSize + 16 * i + 4) = calcPoint(C, (2 * V.row(C) + V.row(A)) / 3);
		calcV.row(oVertexSize + 16 * i + 5) = calcPoint(A, (2 * V.row(A) + V.row(C)) / 3);
		
		calcV.row(oVertexSize + 16 * i + 0) = calcPoint(A, (2 * V.row(A) + V.row(B)) / 3);// + 2 * N.row(A)/3 + N.row(B) /3;
		calcV.row(oVertexSize + 16 * i + 1) = (2 * V.row(B) + V.row(A)) / 3 + N.row(A) / 3 + 2 * N.row(B) / 3;
		calcV.row(oVertexSize + 16 * i + 2) = (2 * V.row(B) + V.row(C)) / 3 + 2 * N.row(B) / 3 + N.row(C) / 3;
		calcV.row(oVertexSize + 16 * i + 3) = (2 * V.row(C) + V.row(B)) / 3 + N.row(B) / 3 + 2 * N.row(C) / 3;
		calcV.row(oVertexSize + 16 * i + 4) = (2 * V.row(C) + V.row(A)) / 3 + 2 * N.row(A) / 3 + N.row(C) / 3;
		calcV.row(oVertexSize + 16 * i + 5) = (2 * V.row(A) + V.row(C)) / 3 + N.row(A) / 3 + 2 * N.row(C) / 3;

		calcV.row(oVertexSize + 16 * i + 6) = (2 * V.row(A) + weightPoint) / 3;// N.row(A);
		calcV.row(oVertexSize + 16 * i + 7) = (V.row(A) + V.row(B) + weightPoint) / 3;//N.row(A) + N.row(B);
		calcV.row(oVertexSize + 16 * i + 8) = (2 * V.row(B) + weightPoint) / 3;// N.row(B);
		calcV.row(oVertexSize + 16 * i + 9) = (V.row(B) + V.row(C) + weightPoint) / 3;//N.row(B) + N.row(C);
		calcV.row(oVertexSize + 16 * i + 10) = (2 * V.row(C) + weightPoint) / 3;// N.row(C);
		calcV.row(oVertexSize + 16 * i + 11) = (V.row(C) + V.row(A) + weightPoint) / 3;//N.row(C) + N.row(A);/------------------------------
		calcV.row(oVertexSize + 16 * i + 6) = calcPoint(A, (2 * V.row(A) + weightPoint) / 3, (2*N.row(A) + N.row(B) + N.row(C)) / 4);// N.row(A);
		calcV.row(oVertexSize + 16 * i + 7) = calcPoint((V.row(A) + V.row(B)) / 2, (V.row(A) + V.row(B) + weightPoint) / 3, (N.row(A) + N.row(B))/2);
		calcV.row(oVertexSize + 16 * i + 8) = calcPoint(B, (2 * V.row(B) + weightPoint) / 3, (N.row(A) + 2 * N.row(B) + N.row(C)) / 4);// N.row(B);
		calcV.row(oVertexSize + 16 * i + 9) = calcPoint((V.row(B) + V.row(C)) / 2, (V.row(B) + V.row(C) + weightPoint) / 3, (N.row(B) + N.row(C))/2);
		calcV.row(oVertexSize + 16 * i + 10) = calcPoint(C, (2 * V.row(C) + weightPoint) / 3, (N.row(A) + N.row(B) + 2 * N.row(C)) / 4);// N.row(C);
		calcV.row(oVertexSize + 16 * i + 11) = calcPoint((V.row(C) + V.row(A)) / 2, (V.row(C) + V.row(A) + weightPoint) / 3, (N.row(C) + N.row(A))/2);
		calcV.row(oVertexSize + 16 * i + 12) = (calcV.row(oVertexSize + 16 * i + 6) + calcV.row(oVertexSize + 16 * i + 7) + calcV.row(oVertexSize + 16 * i + 11))/3;
		calcV.row(oVertexSize + 16 * i + 13) = (calcV.row(oVertexSize + 16 * i + 8) + calcV.row(oVertexSize + 16 * i + 9) + calcV.row(oVertexSize + 16 * i + 7)) / 3;
		calcV.row(oVertexSize + 16 * i + 14) = (calcV.row(oVertexSize + 16 * i + 10) + calcV.row(oVertexSize + 16 * i + 11) + calcV.row(oVertexSize + 16 * i + 9)) / 3;
		calcV.row(oVertexSize + 16 * i + 15) = (calcV.row(oVertexSize + 16 * i + 12) + calcV.row(oVertexSize + 16 * i + 13) + calcV.row(oVertexSize + 16 * i + 14)) / 3;

		calcF.row(i * 27 + 0) << A, oVertexSize + (i * 16) + 6, oVertexSize + (i * 16) + 0;
		calcF.row(i * 27 + 1) << oVertexSize + (i * 16) + 6, oVertexSize + (i * 16) + 7, oVertexSize + (i * 16) + 0;
		calcF.row(i * 27 + 2) << oVertexSize + (i * 16) + 0, oVertexSize + (i * 16) + 7, oVertexSize + (i * 16) + 1;
		calcF.row(i * 27 + 3) << oVertexSize + (i * 16) + 1, oVertexSize + (i * 16) + 7, oVertexSize + (i * 16) + 8;
		calcF.row(i * 27 + 4) << oVertexSize + (i * 16) + 1, oVertexSize + (i * 16) + 8, B;
		calcF.row(i * 27 + 5) << oVertexSize + (i * 16) + 6, oVertexSize + (i * 16) + 12, oVertexSize + (i * 16) + 7;
		calcF.row(i * 27 + 6) << oVertexSize + (i * 16) + 12, oVertexSize + (i * 16) + 13, oVertexSize + (i * 16) + 7;
		calcF.row(i * 27 + 7) << oVertexSize + (i * 16) + 7, oVertexSize + (i * 16) + 13, oVertexSize + (i * 16) + 8;
		calcF.row(i * 27 + 8) << oVertexSize + (i * 16) + 12, oVertexSize + (i * 16) + 13, oVertexSize + (i * 16) + 15;

		calcF.row(i * 27 + 9) << B, oVertexSize + (i * 16) + 8, oVertexSize + (i * 16) + 2;
		calcF.row(i * 27 + 10) << oVertexSize + (i * 16) + 8, oVertexSize + (i * 16) + 9, oVertexSize + (i * 16) + 2;
		calcF.row(i * 27 + 11) << oVertexSize + (i * 16) + 2, oVertexSize + (i * 16) + 9, oVertexSize + (i * 16) + 3;
		calcF.row(i * 27 + 12) << oVertexSize + (i * 16) + 3, oVertexSize + (i * 16) + 9, oVertexSize + (i * 16) + 10;
		calcF.row(i * 27 + 13) << oVertexSize + (i * 16) + 3, oVertexSize + (i * 16) + 10, C;
		calcF.row(i * 27 + 14) << oVertexSize + (i * 16) + 8, oVertexSize + (i * 16) + 13, oVertexSize + (i * 16) + 9;
		calcF.row(i * 27 + 15) << oVertexSize + (i * 16) + 13, oVertexSize + (i * 16) + 14, oVertexSize + (i * 16) + 9;
		calcF.row(i * 27 + 16) << oVertexSize + (i * 16) + 9, oVertexSize + (i * 16) + 14, oVertexSize + (i * 16) + 10;
		calcF.row(i * 27 + 17) << oVertexSize + (i * 16) + 13, oVertexSize + (i * 16) + 14, oVertexSize + (i * 16) + 15;

		calcF.row(i * 27 + 18) << C, oVertexSize + (i * 16) + 10, oVertexSize + (i * 16) + 4;
		calcF.row(i * 27 + 19) << oVertexSize + (i * 16) + 10, oVertexSize + (i * 16) + 11, oVertexSize + (i * 16) + 4;
		calcF.row(i * 27 + 20) << oVertexSize + (i * 16) + 4, oVertexSize + (i * 16) + 11, oVertexSize + (i * 16) + 5;
		calcF.row(i * 27 + 21) << oVertexSize + (i * 16) + 5, oVertexSize + (i * 16) + 11, oVertexSize + (i * 16) + 6;
		calcF.row(i * 27 + 22) << oVertexSize + (i * 16) + 5, oVertexSize + (i * 16) + 6, A;
		calcF.row(i * 27 + 23) << oVertexSize + (i * 16) + 10, oVertexSize + (i * 16) + 14, oVertexSize + (i * 16) + 11;
		calcF.row(i * 27 + 24) << oVertexSize + (i * 16) + 14, oVertexSize + (i * 16) + 12, oVertexSize + (i * 16) + 11;
		calcF.row(i * 27 + 25) << oVertexSize + (i * 16) + 11, oVertexSize + (i * 16) + 12, oVertexSize + (i * 16) + 6;
		calcF.row(i * 27 + 26) << oVertexSize + (i * 16) + 14, oVertexSize + (i * 16) + 15, oVertexSize + (i * 16) + 12;
		*/

	
		/*for (size_t j = 0; j < 30; j++)
		{
		meshV.row(index * 30 + j) = mesh.points[j];
		meshF.row(index * 30 + j) = index * 30 + mesh.triangles[j];
		}*/
	}
	for (const auto &p : mesh.points)
		calcV.row(vertexIndex++) << p[0], p[1], p[2];
	for (const auto &t : mesh.triangles)
		calcF.row(faceIndex++) << t[0], t[1], t[2];
	//std::cout << calcF;
	//std::cout << calcV;

	
	return;
	/*
	for (unsigned i = 0; i < F.size(); ++i) {
		calcV.row(i * 4 + 0) = V.row(i);
		calcF.row(i * 27 + 0) << (i * 27) + 0, (i * 27) + 1, (i * 27) + 3;
		calcF.row(i * 27 + 1) << (i * 27) + 0, (i * 27) + 2, (i * 27) + 1;
		calcF.row(i * 27 + 2) << (i * 27) + 3, (i * 27) + 2, (i * 27) + 0;
		calcF.row(i * 27 + 3) << (i * 27) + 1, (i * 27) + 2, (i * 27) + 3;
	}*/
}
/*
Eigen::VectorXf CloughTocher::calcPoint(unsigned pointIndex, Eigen::MatrixXd calcPoint) {
	Eigen::VectorXf re(3);
	float dx = -N.coeff(pointIndex, 0) / N.coeff(pointIndex, 2);
	float dy = -N.coeff(pointIndex, 1) / N.coeff(pointIndex, 2);
	//float calcPointZ = (calcPoint.coeff(1, 0) - V.coeff(pointIndex, 0)) * dx + (calcPoint.coeff(1, 1) - V.coeff(pointIndex, 1)) * dy;
	re[0] = calcPoint.coeff(0, 0);
	re[1] = calcPoint.coeff(0, 1);
	re[2] = (calcPoint.coeff(0, 0) - V.coeff(pointIndex, 0)) * dx + (calcPoint.coeff(0, 1) - V.coeff(pointIndex, 1)) * dy + V.coeff(pointIndex, 2);
	return re;
}

Eigen::VectorXf CloughTocher::calcPoint(unsigned pointIndex, Eigen::MatrixXd calcPoint, Eigen::VectorXd normal) {
	Eigen::VectorXf re(3);
	float dx = -normal[0] / normal[2];
	float dy = -normal[1] / normal[2];
	//float calcPointZ = (calcPoint.coeff(1, 0) - V.coeff(pointIndex, 0)) * dx + (calcPoint.coeff(1, 1) - V.coeff(pointIndex, 1)) * dy;
	re[0] = calcPoint.coeff(0, 0);
	re[1] = calcPoint.coeff(0, 1);
	re[2] = (calcPoint.coeff(0, 0) - V.coeff(pointIndex, 0)) * dx + (calcPoint.coeff(0, 1) - V.coeff(pointIndex, 1)) * dy + V.coeff(pointIndex, 2);
	return re;
}

Eigen::VectorXf CloughTocher::calcPoint(Eigen::VectorXd point, Eigen::VectorXd calcPoint, Eigen::VectorXd normal) {
	Eigen::VectorXf re(3);
	float dx = -normal[0] / normal[2];
	float dy = -normal[1] / normal[2];
	//float calcPointZ = (calcPoint.coeff(1, 0) - V.coeff(pointIndex, 0)) * dx + (calcPoint.coeff(1, 1) - V.coeff(pointIndex, 1)) * dy;
	re[0] = calcPoint[0];
	re[1] = calcPoint[1];
	re[2] = (calcPoint[0] - point[0]) * dx + (calcPoint[1] - point[1]) * dy + point[2];
	return re;
}
*/
/*unsigned CloughTocher::searchPointIndex(unsigned parent1, unsigned parent2, unsigned index) {
	std::vector<unsigned> seged = { parent1, parent2, index };
	tempPoint[V.size()];
	return index;
}*/
//void CloughTocher::addPoint(double u, double v);