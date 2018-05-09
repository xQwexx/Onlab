#include "CTTriangle.h"
#include "btriangle.hh"


Point calcPoint(Point point, Point calcPoint, Point normal) {
	Point re;
	float dx = -normal[0] / normal[2];
	float dy = -normal[1] / normal[2];
	//float calcPointZ = (calcPoint.coeff(1, 0) - V.coeff(pointIndex, 0)) * dx + (calcPoint.coeff(1, 1) - V.coeff(pointIndex, 1)) * dy;
	re.data[0] = calcPoint[0];
	re.data[1] = calcPoint[1];
	re.data[2] = (calcPoint[0] - point[0]) * dx + (calcPoint[1] - point[1]) * dy + point[2];
	return re;
}

CTTriangle::CTTriangle(Point v[3], Point n[3])
{
	Point A = v[0];
	Point B = v[1];
	Point C = v[2];
	Point weightPoint = (A + B + C) / 3;
	vertices[3] = A;
	vertices[9] = B;
	vertices[15] = C;
	/*
	vertices[5] = calcPoint(A, (A * 2 + B) / 3, (n[0] + n[1]) / 2);
	vertices[6] = calcPoint(B, (B * 2 + A) / 3, (n[1] + n[0]) / 2);
	vertices[11] = calcPoint(B, (B * 2 + C) / 3, (n[1] + n[2]) / 2);
	vertices[12] = calcPoint(C, (C * 2 + B) / 3, (n[2] + n[1]) / 2);
	vertices[17] = calcPoint(C, (C * 2 + A) / 3, (n[2] + n[0]) / 2);
	vertices[18] = calcPoint(A, (A * 2 + C) / 3, (n[0] + n[2]) / 2);

	vertices[2] = calcPoint(A, (A * 2 + weightPoint) / 3, (n[0] * 2 + n[1] + n[2]) / 4);// n[0];
	vertices[4] = calcPoint((A + B) / 2, (A + B + weightPoint) / 3, (n[0] + n[1]) / 2);
	vertices[8] = calcPoint(B, (B * 2 + weightPoint) / 3, (n[0] + n[1] * 2 + n[2]) / 4);// n[1];
	vertices[10] = calcPoint((B + C) / 2, (B + C + weightPoint) / 3, (n[1] + n[2]) / 2);
	vertices[14] = calcPoint(C, (C * 2 + weightPoint) / 3, (n[0] + n[1] + n[2] * 2) / 4);// n[2];
	vertices[16] = calcPoint((C + A) / 2, (C + A + weightPoint) / 3, (n[2] + n[0]) / 2);
	vertices[1] = (vertices[2] + vertices[4] + vertices[16]) / 3;
	vertices[7] = (vertices[8] + vertices[4] + vertices[10]) / 3;
	vertices[13] = (vertices[14] + vertices[10] + vertices[16]) / 3;
	vertices[0] = (vertices[1] + vertices[7] + vertices[13]) / 3;
	*/
	vertices[5] = calcPoint(A, (A * 2 + B) / 3, n[0]);
	vertices[6] = calcPoint(B, (B * 2 + A) / 3, n[1]);
	vertices[11] = calcPoint(B, (B * 2 + C) / 3, n[1]);
	vertices[12] = calcPoint(C, (C * 2 + B) / 3, n[2]);
	vertices[17] = calcPoint(C, (C * 2 + A) / 3, n[2]);
	vertices[18] = calcPoint(A, (A * 2 + C) / 3, n[0]);

	vertices[2] = calcPoint(A, (A * 2 + weightPoint) / 3, n[0]);// n[0];
	vertices[4] = calcPoint((A + B) / 2, (A + B + weightPoint) / 3, (n[0] + n[1]) / 2);
	vertices[8] = calcPoint(B, (B * 2 + weightPoint) / 3, n[1]);// n[1];
	vertices[10] = calcPoint((B + C) / 2, (B + C + weightPoint) / 3, (n[1] + n[2]) / 2);
	vertices[14] = calcPoint(C, (C * 2 + weightPoint) / 3, n[2]);// n[2];
	vertices[16] = calcPoint((C + A) / 2, (C + A + weightPoint) / 3, (n[2] + n[0]) / 2);
	vertices[1] = (vertices[2] + vertices[4] + vertices[16]) / 3;
	vertices[7] = (vertices[8] + vertices[4] + vertices[10]) / 3;
	vertices[13] = (vertices[14] + vertices[10] + vertices[16]) / 3;
	vertices[0] = (vertices[1] + vertices[7] + vertices[13]) / 3;
}


CTTriangle::~CTTriangle()
{
}

Mesh CTTriangle::evalMesh() const {
	BTriangle ba(3, { vertices[9], vertices[6], vertices[5], vertices[3],
		vertices[8], vertices[4], vertices[2],
		vertices[7], vertices[1],
		vertices[0] });
	BTriangle cb(3, { vertices[15], vertices[12], vertices[11], vertices[9],
		vertices[14], vertices[10], vertices[8],
		vertices[13], vertices[7],
		vertices[0] });
	BTriangle ac(3, { vertices[3], vertices[18], vertices[17], vertices[15],
		vertices[2], vertices[16], vertices[14],
		vertices[1], vertices[13],
		vertices[0] });

	return ba.evalMesh(30) + cb.evalMesh(30) + ac.evalMesh(30);
}
