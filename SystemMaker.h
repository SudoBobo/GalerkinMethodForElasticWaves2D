#ifndef SYSTEMMAKER_H
#define SYSTEMMAKER_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "Triangle.h"
using boost::numeric::ublas::matrix;

class SystemMaker
{
public:
	SystemMaker();
	matrix <double> dU (Triangle & triangle) const;
};

#endif // SYSTEMMAKER_H
