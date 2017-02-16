#ifndef SUPPORT
#define SUPPORT

#include <Triangle.h>
#include <Rectangle.h>
#include <vector>

std::vector <Triangle> createRegularTriangelMesh(double xSize, double ySize,
												 double spatialStep,
												 double lambda, double mu,
												 double rho,
												 int polynomialOrder,
												 int uSize);

// spatial step == rectangleSide
//std::vector <double> createSource (std::vector <Rectangle> rectangles,
//								   double xSize, double ySize,
//								   double rectangleSide,
//								   double minorRectangleSide) const
//{

//	// 0,1,2 ... maxLineNumber - 1
//	int yGridSize = ySize / minorRectangleSide;
//	int xGridSize = xSize / minorRectangleSide;
//	std::vector <double> source;

//	for (int lineNumber = 0; lineNumber < yGridSize; lineNumber ++)
//	{
//		//!
//		for (int rectangleNumber = lineNumber * xGridSize;
//			 rectangleNumber < (lineNumber * xGridSize + xGridSize);
//			 rectangleNumber++)
//		{

//		}
//	}
//}

//Rectangle createRectangleFromFourTriangles(std::vector <Triangle> triangles)
//const
//{
//	if  ((triangles[0].getNumberInRectangle() == 0) &&
//		(triangles[1].getNumberInRectangle() == 1) &&
//		(triangles[2].getNumberInRectangle() == 2) &&
//		(triangles[3].getNumberInRectangle() == 3))
//	{

//	}

//	else
//	{
//		throw(std::range_error("Mistake in createRectangleFromFourTriangles"));
//	}
//}
#endif // SUPPORT

