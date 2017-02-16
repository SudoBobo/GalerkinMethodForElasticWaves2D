#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <array>
#include <vector>



using boost::numeric::ublas::matrix;
using std::pair;

class Triangle;

struct Bound
{
	double x1;
	double y1;

	double x2;
	double y2;

	double nx;
	double ny;

	Triangle *  boundaryTriangle;
};

class Triangle
{
public:
	// rule of five???
	//	Деструктор
	//	Конструктор копирования
	//	Оператор присваивания копированием
	//	Конструктор перемещения
	//	Оператор присваивания перемещением
//	Triangle (int polynomialOrder, int uSize, double lambda, double mu, double rho,
//			  std::array <double, 3> x, std::array <double, 3> y,
//			  std::array <double, 3> z);
	Triangle (int polynomialOrder, int uSize, double lambda, double mu,
			  double rho);
	Triangle() = default;

	void setFirstBoundaryTriangle (Triangle * triangle, pair <double, double> r1,
								   pair <double, double> r2,
								   pair <double, double> n);
	void setSecondBoundaryTriangle (Triangle * triangle, pair <double, double> r1,
									pair <double, double> r2,
									pair <double, double> n);
	void setThirdBoundaryTriangle (Triangle * triangle, pair <double, double> r1,
								   pair <double, double> r2,
								   pair <double, double> n);

	// x1y1 -> x2y2

//	void setVertexCoordinateX (std::array <double, 3> x);
//	void setVertexCoordinateY (std::array <double, 3> y);

	void setNumber(int number);
	void setNumberInRectangle(int number);

	void setRectangleN(int N);
	void setRectangleM(int M);

	void setCentreCoordinates(std::pair<double,double> centreCoordinates);

	void setM (double nM);
	void setFj0 (double nFj0);
	void setFji (double nFji);
	void setKxi (double nKxi);
	void setKeta (double nKeta);

	int getPolynomialOrder() const;

	int getNumber() const;
	int getNumberInRectangle() const;

	int getRectangleN () const;
	int getRectangleM () const;

	matrix <double> getA() const;
	matrix <double> getAbsoluteA() const;
	matrix <double> getStarA() const;
	matrix <double> getStarB() const;
	matrix <double> getAbsoluteB() const;

	matrix <double> getB() const;

	Triangle * getFirstBoundaryTriangle() const;
	Triangle * getSecondBoundaryTriangle() const;
	Triangle * getThirdBoundaryTriangle() const;

	matrix <double> getT(int j) const;
	std::pair <double, double> getCentreCoordinates() const;

	double getJ() const;
	double getM () const;
	double getFj0 () const;
	double getFji () const;
	double getKxi () const;
	double getKeta () const;

	const Bound & getBound (int j) const
	{
		return bounds[j-1];
	}


	matrix<double> & getU();
	matrix<double> getU() const;

	void setU(matrix<double> newU);

	void writeBoundaries() const;

private:

	// свойство полинома - общее, как и размер решения
	int polynomialOrder;
	int uSize;

	int number;
	//only for regular mesh case
	int numberInRectangle;

	//coordinates of rectangle
	int rectangleN;
	int rectangleM;
	//vertex coordinates
//	std::array <double, 3> x;
//	std::array <double, 3> y;
//	std::array <double, 3> z;

	// (2), (3) and (4), pg. 3
	matrix <double> A;
	matrix <double> B;
	matrix <double> U;
	// (24), (25) ... (28) pg. 6
	// currently they are all the same, because triangle are the same
	// calculations of this matrix takes place in makeTriangleMesh()
	matrix <double> M;
	matrix <double> Fj0;
	matrix <double> Fji;
	matrix <double> Kxi;
	matrix <double> Keta;

	double nM;
	double nFj0;
	double nFji;
	double nKxi;
	double nKeta;

	// boundary triangles
//	// x1y1 -> x2y2
//	Triangle * firstBoundaryTriangle;
//	// x1y1 -> x3y3
//	Triangle * secondBoundaryTriangle;
//	//x2y2 -> x3y3
//	Triangle * thirdBoundaryTriangle;

	// vertex coordinates and boundary triangles
	std::array <Bound, 3> bounds;
	std::pair <double, double> centreCoordinates;



};


#endif // TRIANGLE_H
