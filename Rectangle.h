#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "Triangle.h"

class Rectangle
{
public:
	Rectangle(std::vector <Triangle> & triangles);
	const matrix <matrix<double>> & getMesh() const;

private:

	int				number;
	int				rectangleN;
	int				rectangleM;

	/*
	 * (2,0) (2,1) (2,2)
	 * (1,0) (1,1) (1,2)
	 * (0,0) (0,1) (0,2)
	 *
	 * this way it goes into the source file
	 */

	matrix <matrix<double>> mesh;
};

#endif // RECTANGLE_H
