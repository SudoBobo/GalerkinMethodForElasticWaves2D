#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "Triangle.h"
#include "SourceWrapper.h"


class TriangleMesh
{
public:
	TriangleMesh(double xSize, double ySize,
				 double rectangleSide,
				 double lambda, double mu,
				 double rho,
				 int polynomialOrder,
				 int uSize);
	TriangleMesh(const TriangleMesh & another);
	const std::vector <Triangle> & getMesh() const;
	std::vector <Triangle> & getMesh();

	SourceWrapper makeSourceWrapper() const;

	int getMaxM () const{
		return maxM;
	}
	int getMaxN () const{
		return maxN;
	}

private:
	// располагаются линейно, слева направо, снизу вверх, по схеме
	/**
	 *		1		5
	 *	0		2		6
	 *		3		7
	 */

	std::vector <Triangle> mesh;
	int maxN;
	int maxM;
};

#endif // TRIANGLEMESH_H
