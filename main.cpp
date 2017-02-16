#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>



#include "Triangle.h"
#include "TriangleMesh.h"
#include "Rectangle.h"
#include "RectangleMesh.h"

#include "Support.h"
#include "FileWriter.h"




int main()
{
	double fullTime = 100 * std::sqrt(2.0);
	double timeStep = 1;
	// omega (rectangle sizes)
	double xSize  = 100;
	double ySize  = 100;
	double rectangleSide = 25;
	double lambda = 2;
	double mu     = 1;
	double rho    = 1;
	// 0 - u = a0, 1 - u = a1 * x + a0, etc
	int polynomialOrder = 0;
	int uSize = 5;

	// was not tested with spatialStep != 25 or 50
	// хорошо ли хранить в простом векторе?
	TriangleMesh triangleMesh(xSize, ySize,
							  rectangleSide,
							  lambda, mu, rho,
							  polynomialOrder,
							  uSize);
	RectangleMesh rectangleMesh(triangleMesh);
	auto wrappedSource = rectangleMesh.makeSourceWrapper();
	auto source = wrappedSource.getSource();
	int xGrid = (xSize / 25) * 3;
	int yGrid = (ySize / 25) * 3;

	std::vector <int> gridSize = {xGrid, yGrid, 0};

	FileWriter fileWriter(source, "part0_","file",
							  "/home/bobo/aData/", 6, gridSize);
	fileWriter.clean();
	fileWriter.write(1);
	// ProblemSolver problemSolver (SystemMaker ..., SystemSolver ...)
	// problemSolver.Solve(fullTime, triangleMesh)
	return 0;
}

