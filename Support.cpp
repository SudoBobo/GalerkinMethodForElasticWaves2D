#include <Support.h>
#include <exception>
#include <cmath>
#include <vector>


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>



using boost::numeric::ublas::matrix;
using std::sqrt;

std::vector <Triangle> createRegularTriangelMesh(double xSize, double ySize,
												 double spatialStep,
												 double lambda, double mu,
												 double rho,
												 int polynomialOrder,
												 int uSize)
{
	if ((xSize < spatialStep) || (ySize < spatialStep))
		throw std::range_error("xSize or ySize is less than spatialStep");

	const double fullSquare = xSize * ySize;
	const double rectangleSquare = spatialStep * spatialStep;
	// one rectangle -> four triangles




	if (std::fmod(fullSquare,rectangleSquare) != 0)
		throw std::range_error("fullSquare % rectangelSquare != 0");

	const int numberOfRectangles = fullSquare / rectangleSquare;

	if(xSize != ySize)
		throw std::range_error("Only squre case is implemented");

	const int Nmax = (xSize / spatialStep) - 1;
	const int Mmax = (ySize / spatialStep) - 1;

	const int numberOfTriangles = 4 * numberOfRectangles;
	std::vector <Triangle> mesh (numberOfTriangles, Triangle(polynomialOrder,
															  uSize, lambda, mu,
															  rho ));
	int numberInRectangle = 0;
	int M = 0;
	int N = 0;

	for (int m = 0; m < mesh.size(); m++)
	{
		mesh[m].setMu(mu);
		mesh[m].setRho(rho);
		mesh[m].setLambda(lambda);

		mesh[m].setNumber(m);
		mesh[m].setNumberInRectangle(numberInRectangle);
		numberInRectangle++;

		mesh[m].setRectangleN(N);


		if (numberInRectangle == 4)
		{
				numberInRectangle = 0;
				N++;
		}

		mesh[m].setRectangleM(M);

		if(Nmax < N)
		{
			N = 0;
			M++;
		}

	}

	// in structered mesh there are only 12 different normal(to bound) vectors
	std::vector <pair <double, double> > n0(3);
	std::vector <pair <double, double> > n1(3);
	std::vector <pair <double, double> > n2(3);
	std::vector <pair <double, double> > n3(3);

	// for numberInRectangle == 0

	n0[0] = {1/sqrt(2), 1/sqrt(2)};
	n0[1] = {1/sqrt(2), -1/sqrt(2)};
	n0[2] = {-1, 0};

	// for numberInRectangle == 1

	n1[0] = {-1/sqrt(2), -1/sqrt(2)};
	n1[1] = {1/sqrt(2), -1/sqrt(2)};
	n1[2] = {0, 1};

	n2[0] = {-1/sqrt(2), 1/sqrt(2)};
	n2[1] = {-1/sqrt(2), -1/sqrt(2)};
	n2[2] = {1, 0};

	n3[0] = {-1/sqrt(2), 1/sqrt(2)};
	n3[1] = {1/sqrt(2), 1/sqrt(2)};
	n3[2] = {0, -1};


	for (int m = 0; m < mesh.size(); m++)
	{
		static double h = spatialStep;

		static int M;
		static int N;

		M = mesh[m].getRectangleM();
		N = mesh[m].getRectangleN();

		static double rectangleX;
		static double rectangleY;

		rectangleX = spatialStep * (N + 0.5);
		rectangleY = spatialStep * (M + 0.5);


		static std::vector <std::pair <double, double> > r (5);

		r[0] = {rectangleX - h/2, rectangleY - h/2};
		r[1] = {rectangleX - h/2, rectangleY + h/2};
		r[2] = {rectangleX + h/2, rectangleY + h/2};
		r[3] = {rectangleX + h/2, rectangleY - h/2};
		r[4] = {rectangleX,       rectangleY};

		static double xC;
		static double yC;
			switch (mesh[m].getNumberInRectangle())
			 {
				 case 0:
					 {
						xC = (r[0].first + r[1].first + r[4].first) / 3;
						yC = (r[0].second + r[1].second + r[4].second) / 3;
						mesh[m].setCentreCoordinates({xC, yC});

						mesh[m].setFirstBoundaryTriangle (&mesh[m+1], r[1],
																	  r[4], n0[0]);
						mesh[m].setSecondBoundaryTriangle(&mesh[m+3], r[4],
																	  r[0], n0[1]);
						if (N == 0)
							mesh[m].setThirdBoundaryTriangle(&mesh[m+Nmax*4+2],
									r[0], r[1], n0[2]);
						else
							mesh[m].setThirdBoundaryTriangle (&mesh[m-2],r[0],
																		 r[1], n0[2]);
						break;
					 }
				 case 1:
					 {
						xC = (r[1].first + r[2].first + r[4].first)/3;
						yC = (r[1].second + r[2].second + r[4].second)/3;
						mesh[m].setCentreCoordinates({xC, yC});

						mesh[m].setFirstBoundaryTriangle (&mesh[m-1], r[4], r[1], n1[0]);
						mesh[m].setSecondBoundaryTriangle(&mesh[m+1], r[2], r[4], n1[1]);
						if (M == Mmax)
							mesh[m].setThirdBoundaryTriangle (&mesh[m-Mmax*4-2],
									r[1], r[2], n1[2]);
						else
							mesh[m].setThirdBoundaryTriangle (&mesh[m+3+(Nmax+1)*4-1],
									r[1], r[2], n1[2]);
						break;
					 }

				case 2:
					{
						xC = (r[2].first + r[4].first +r[3].first)/3;
						yC = (r[2].second + r[4].second + r[3].second)/3;
						mesh[m].setCentreCoordinates({xC, yC});

						mesh[m].setFirstBoundaryTriangle (&mesh[m-1], r[4], r[2], n2[0]);
						mesh[m].setSecondBoundaryTriangle(&mesh[m+1], r[3], r[4], n2[1]);
						if (N == Nmax)
							mesh[m].setThirdBoundaryTriangle (&mesh[m-Nmax*4-2],
									r[2], r[3], n2[2]);
						else
							mesh[m].setThirdBoundaryTriangle (&mesh[m+2], r[2], r[3], n2[2]);
						break;
					}

				case 3:
					{
						xC = (r[0].first + r[3].first + r[4].first)/3;
						yC = (r[0].second + r[3].second + r[4].second)/3;
						mesh[m].setCentreCoordinates({xC, yC});

						mesh[m].setFirstBoundaryTriangle (&mesh[m-3], r[0], r[4], n3[0]);
						mesh[m].setSecondBoundaryTriangle(&mesh[m-1], r[4], r[3], n3[1]);
						if (M == 0)
							mesh[m].setThirdBoundaryTriangle (&mesh[m+Mmax*4+2], r[3], r[0], n3[2]);
						else
							mesh[m].setThirdBoundaryTriangle (&mesh[m-(3+(Nmax+1)*4-1)], r[3], r[0], n3[2]);
						break;
					}

			 }
	}

			// calculate M, Fj0,Fji, Kxi, Kete
		if (polynomialOrder == 0)
		{
			const double Mkl  = 1;
			const double Fj0  = 1;
			const double Fji  = 1;
			const double Kxi  = 0;
			const double Keta = 0;

			for (int m = 0; m < mesh.size(); m++)
			{
				mesh[m].setM   (Mkl);
				mesh[m].setFj0 (Fj0);
				mesh[m].setFji (Fji);
				mesh[m].setKxi (Kxi);
				mesh[m].setKeta(Keta);
			}

			static double nx = 1;
			static double ny = 1;
			static double cs = 1;

			static matrix <double> temp (uSize, polynomialOrder + 1);

			temp(0,0) = -2 * mu * nx * ny;
			temp(1,0) = 2 * mu * nx * ny;
			temp(2,0) = mu * (nx*nx - ny*ny);
			temp(3,0) = -ny * cs;
			temp(4,0) = nx * cs;

			static double x;
			static double y;

			for (int m = 0; m < mesh.size(); m++)
			{
				x = mesh[m].getCentreCoordinates().first;
				y = mesh[m].getCentreCoordinates().second;

				// в общем случае есть разница между численным значением U
				// и временным коэффициентом разложения
				// но в случае l = 0 разницы нет
				// код нижен верн только для этого случая
				// следует явно написать, где коэффициенты, а где численное
				// значение

				matrix <double> sinM(uSize, polynomialOrder + 1);
				sinM(0,0) = std::sin(((2*M_PI)/25) * (x + y));
				sinM(1,0) = sinM(0,0);
				sinM(2,0) = sinM(0,0);
				sinM(3,0) = sinM(0,0);
				sinM(4,0) = sinM(0,0);

				mesh[m].getU().resize(uSize, polynomialOrder + 1);
				mesh[m].getU() = temp + sinM;

//				std::cout << m << " " << mesh[m].getU()(0,0) + 2 << std::endl;
			}
		}
		else
			throw
			std::range_error(R"("polynomialOrder > 0" is not implemented)");

	return mesh;
}
