#include "SystemMaker.h"
#include "MyMath.h"
#include <boost/numeric/ublas/operation.hpp>


using boost::numeric::ublas::matrix;
using boost::numeric::ublas::prod;

SystemMaker::SystemMaker()
{

}

// for one triangle
matrix<double> SystemMaker::dU(Triangle &triangle) const
{
	assert(triangle.getPolynomialOrder() == 0);

	Triangle & t = triangle;

	matrix <double> T(5,5);
	matrix <double> A(5,5);
	matrix <double> AbsoluteA(5,5);
	matrix <double> U(5,1);
	matrix <double> dU(5,1);



	// make first big component in formula 21
	matrix<double> zero(5,1);
	std::vector<matrix<double>> component(3, zero);

	for (int j = 1; j <= 3; j++)
	{
		// проверь эту секцию с дебагом
		Bound bound = t.getBound(j);
		T = t.getT(bound);
		A = t.getA();
		U = t.getU();

		AbsoluteA = t.getAbsoluteA(bound);
		matrix<double> first = prod(T, A + AbsoluteA);
		matrix<double> invertibleT = makeInvertible(T);
		matrix<double> second = prod (invertibleT, U);

		double SModule = t.getSModule(bound);
		component[j-1] = prod(first,second);
		component[j-1] *= -0.5 * t.getFj0() * SModule;
	}


	// make second big component in formula 21
	std::vector<matrix<double>> secondComponent(3, zero);
	for (int j = 1; j <= 3; j++)
	{
		// проверь эту секцию с дебагом
		//T = t.getT(j);
        Bound currentBound = t.getBound(j);
        T = t.getT(currentBound);
		A = t.getA();
		AbsoluteA = t.getAbsoluteA(currentBound);
        matrix <double> mU = currentBound.boundaryTriangle->getU();

		// hardly unfinished
		matrix<double>first = prod(T, A - AbsoluteA);
		// не T, а обратная к T
		matrix<double>invertibleT = makeInvertible(T);
		matrix<double> second = prod (invertibleT, mU);

		double SModule = t.getSModule(currentBound);

		secondComponent[j-1] = prod(first,second);
		secondComponent[j-1] *= -0.5 * t.getFji() * SModule;
	}

	double J = t.getJ();
	U = t.getU();

	// make third and fourth big component in form. 21

	static matrix <double> starA(5,5);
	static matrix <double> starB(5,5);

	starA = t.getStarA();
	starB = t.getStarB();

	auto Mkl = t.getM();

	matrix<double> thirdComponent  = prod(starA, U); //* J * t.getKxi();
	thirdComponent *= J * t.getKxi();
	matrix<double> fourthComponent = prod(starB, U);// * J * t.getKeta();
	fourthComponent *= J * t.getKeta();

	dU += component[0] + component[1] + component[2] + secondComponent[0] + secondComponent[1] + secondComponent[2]
		  + thirdComponent + fourthComponent;
	dU /= (Mkl * J);

	return dU;
}
