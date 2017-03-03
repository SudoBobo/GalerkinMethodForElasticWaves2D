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
	static matrix <double> T(5,5);
	static matrix <double> A(5,5);
	static matrix <double> AbsoluteA(5,5);
	static matrix <double> U(5,1);
	static matrix <double> dU(5,1);

	// не уверен, что это так
	double Sj = 1.0;

	dU *= 0;
	T  *= 0;

{
//	int pMax = t.getU().size1();
//	int lMax = t.getPolynomialOrder();
//	int jMax = 3;

//	for (int p = 1; p <= pMax; p++)
//	{
//		for (int l = 0; l <= lMax; l++)
//		{
//			for (int j = 1; j <= jMax; j++)
//			{
//				dU += 1;
//			}
//			// + два последних слагаемых
//			// не забудь знаки поменять
//		}
//	}
}


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

		//TODO: сделать абсолют А, стар А/Б и получение J из треугольника
		AbsoluteA = t.getAbsoluteA(bound);
		// hardly unfinished
		// можно это всё в цикле сделать, чтоб наверняка
		matrix<double> first = prod(T, A + AbsoluteA);
		// не T, а обратная к T
		matrix<double> invertibleT = makeInvertible(T);
		matrix<double> second = prod (invertibleT, U);

		component[j-1] = prod(first,second);
		component[j-1] *= -0.5 * t.getFj0() * Sj;
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

		secondComponent[j-1] = prod(first,second);
		secondComponent[j-1] *= -0.5 * t.getFji() * Sj;
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
