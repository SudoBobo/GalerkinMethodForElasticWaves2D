#ifndef RECTANGLEMESH_H
#define RECTANGLEMESH_H

#include "Triangle.h"
#include "TriangleMesh.h"
#include "Rectangle.h"
#include "SourceWrapper.h"

#include <vector>

class RectangleMesh
{
public:
	RectangleMesh(const TriangleMesh &triangleMesh);
	SourceWrapper makeSourceWrapper() const;
	std::vector <double> makeSource() const;
	int getMaxN() const;
	int getMaxM() const;

private:
	/*
	 *	2	3
	 *	0	1
	 *
	 * also see pics in documentation
	 */

	std::vector <Rectangle> mesh;
	int maxN;
	int maxM;
};

#endif // RECTANGLEMESH_H
