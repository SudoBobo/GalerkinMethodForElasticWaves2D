#include "Triangle.h"
#include <iostream>
#include <vector>
#include "MyMath.h"

using std::vector;

Triangle::Triangle(int polynomialOrder, int uSize, double lambda, double mu,
                   double rho) :
        polynomialOrder(polynomialOrder), uSize(uSize),
        A(uSize, uSize), B(uSize, uSize), U(uSize, 1) {
    A(3, 0) = -(1 / rho);
    A(4, 2) = -(1 / rho);
    A(0, 3) = -(lambda + 2 * mu);
    A(1, 3) = -lambda;
    A(2, 4) = -mu;

    B(4, 1) = -(1 / rho);
    B(3, 2) = -(1 / rho);
    B(2, 3) = -mu;
    B(1, 4) = -(lambda + 2 * mu);
    B(0, 4) = -lambda;
}


// plz rewrite into one function with number of the number as an argument

void Triangle::setFirstBoundaryTriangle(Triangle *triangle, pair<double, double> r1,
                                        pair<double, double> r2,
                                        pair<double, double> n) {
    static int numberOfCalls = 0;
    if (numberOfCalls != 0)
        std::range_error("an attempt to change boundaryTriangle1");
    numberOfCalls++;

    if (triangle == nullptr)
        throw std::range_error("an attempt to assign nullptr!");

    bounds[0].boundaryTriangle = triangle;

    bounds[0].x1 = r1.first;
    bounds[0].y1 = r1.second;

    bounds[0].x2 = r2.first;
    bounds[0].y2 = r2.second;

    bounds[0].nx = n.first;
    bounds[0].ny = n.second;
}

void Triangle::setSecondBoundaryTriangle(Triangle *triangle, pair<double, double> r1,
                                         pair<double, double> r2,
                                         pair<double, double> n) {
    static int numberOfCalls = 0;
    if (numberOfCalls != 0)
        std::range_error("an attempt to change boundaryTriangle2");
    numberOfCalls++;

    if (triangle == nullptr)
        throw std::range_error("an attempt to assign nullptr!");

    bounds[1].boundaryTriangle = triangle;

    bounds[1].x1 = r1.first;
    bounds[1].y1 = r1.second;

    bounds[1].x2 = r2.first;
    bounds[1].y2 = r2.second;

    bounds[1].nx = n.first;
    bounds[1].ny = n.second;
}

void Triangle::setThirdBoundaryTriangle(Triangle *triangle, pair<double, double> r1,
                                        pair<double, double> r2,
                                        pair<double, double> n) {
    static int numberOfCalls = 0;
    if (numberOfCalls != 0)
        std::range_error("an attempt to change boundaryTriangle3");
    numberOfCalls++;

    if (triangle == nullptr)
        throw std::range_error("an attempt to assign nullptr!");

    bounds[2].boundaryTriangle = triangle;

    bounds[2].x1 = r1.first;
    bounds[2].y1 = r1.second;

    bounds[2].x2 = r2.first;
    bounds[2].y2 = r2.second;

    bounds[2].nx = n.first;
    bounds[2].ny = n.second;
}


matrix<double> Triangle::getA() const {
    return A;
}

matrix<double> Triangle::getStarA() const{
  //note formula n. 23
    matrix <double> StarA;
    double edx = (this->getY(3) - this->getY(1)) / this-> getJ();
    double edy = (this->getX(1) - this->getX(3)) / this->getJ();
    StarA = this->getA() * edx + this->getB() * edy;
    return StarA;
}

matrix<double> Triangle::getAbsoluteA(Bound bound) const{
    matrix <double> AbsoluteA;
    matrix<double> R = this->getR(bound);
    matrix<double> speedMatrix = this->getSpeedMatrix();

    matrix <double> first = prod(R, speedMatrix);
//    matrix <double> first = prod(this->getR(bound), this->getSpeedMatrix());
    matrix <double> invertableR = makeInvertible(this->getR(bound));
    AbsoluteA = prod(first, invertableR);
    return AbsoluteA;
}

matrix <double> Triangle::getSpeedMatrix() const {
  matrix <double> sM(5,5);
  sM(0,0) = this->getS(1);
  sM(1,1) = this->getS(2);
  sM(2,2) = this->getS(3);
  sM(3,3) = this->getS(4);
  sM(4,4) = this->getS(5);
  return sM;
}
matrix<double> Triangle::getR (Bound bound)const{
    matrix<double> R(5,5);
    double nX = bound.nx;
    double nY = bound.ny;
    double mu = this->getMu();
    double rho = this->getRho();
    double lbd = this->getLambda();
    double CP = this->getCP();
    double CS = this->getCS();

    R(0, 0) = lbd + 2 * mu * nX * nX;
    R(0, 1) = -2 * mu * nX * nY;
    R(0, 2) = nY * nY;
    R(0, 3) = -2 * mu * nX * nY;
    R(0, 4) = lbd + 2 * mu * nX * nX;

    R(1, 0) = lbd + 2 * mu * nY * nY;
    R(1, 1) = 2 * mu * nX * nY;
    R(1, 2) = nX * nX;
    R(1, 3) = 2 * mu * nX * nY;
    R(1, 4) = lbd + 2 * mu * nY * nY;

    R(2, 0) = 2 * mu * nX * nY;
    R(2, 1) = mu * (nX * nX - nY * nY);
    R(2, 2) = - nX * nY;
    R(2, 3) = mu * (nX * nX - nY * nY);
    R(2, 4) = 2 * mu * nX * nY;

    R(3, 0) = nX * CP;
    R(3, 1) = -1 * nY * CS;
    R(3, 2) = 0;
    R(3, 3) = nY * CS;
    R(3, 4) = -nX * CP;

    R(4, 0) = nY * CP;
    R(4, 1) = nX * CS;
    R(4, 2) = 0;
    R(4, 3) = -1 * nX * CS;
    R(4, 4) = -1 * nY * CP;

    return R;
};



matrix<double> Triangle::getStarB() const{
  //note formula n. 23
  matrix <double> StarB;
  double ndx = (this->getY(1) - this->getY(2)) / this->getJ();
  double ndy = (this->getX(2) - this->getX(1)) / this->getJ();
  StarB = this->getA() * ndx + this->getB() * ndy;
  return StarB;
}


matrix<double> Triangle::getB() const {
    return B;
}

void Triangle::setNumber(int number) {
    this->number = number;
}

void Triangle::setNumberInRectangle(int number) {
    this->numberInRectangle = number;
}


int Triangle::getNumber() const {
    return number;
}

int Triangle::getNumberInRectangle() const {
    return numberInRectangle;
}

void Triangle::setRectangleN(int N) {
    this->rectangleN = N;
}

void Triangle::setRectangleM(int M) {
    this->rectangleM = M;
}

int Triangle::getRectangleN() const {
    return rectangleN;
}

int Triangle::getRectangleM() const {
    return rectangleM;
}

Triangle *Triangle::getFirstBoundaryTriangle() const {
    return bounds[0].boundaryTriangle;
}

Triangle *Triangle::getSecondBoundaryTriangle() const {
    return bounds[1].boundaryTriangle;
}


Triangle *Triangle::getThirdBoundaryTriangle() const {
    return bounds[2].boundaryTriangle;
}


void Triangle::writeBoundaries() const {
    std::cout << "m = " << number << "  m1 =" <<
              this->getFirstBoundaryTriangle()->getNumber() << "  m2 =" <<
              this->getSecondBoundaryTriangle()->getNumber() << "  m3 =" <<
               this->getThirdBoundaryTriangle()->getNumber() << std::endl;
}

void Triangle::setCentreCoordinates(std::pair<double, double> centreCoordinates) {
    this->centreCoordinates = centreCoordinates;
}

std::pair<double, double> Triangle::getCentreCoordinates() const {
    return centreCoordinates;
}

double Triangle::getJ() const {

    // boundary triangles
  //	// x1y1 -> x2y2
  //	Triangle * firstBoundaryTriangle;
  //	// x1y1 -> x3y3
  //	Triangle * secondBoundaryTriangle;
  //	//x2y2 -> x3y3
  //	Triangle * thirdBoundaryTriangle;

  //(x2 - x1)(y3 - y1) - (x3 - x1)(y2 - y1)
    double x1, x2, x3, y1, y2, y3;

    x1 = this->getX(1);
    x2 = this->getX(2);
    x3 = this->getX(3);

    y1 = this->getY(1);
    y2 = this->getY(2);
    y3 = this->getY(3);
    double J = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    return J;
}


double Triangle::getX(int i) const{
  std::array<double, 3> x;
  x[0] = this->getBound(0).x1;
  x[1] = this->getBound(0).x2;
  x[2] = this->getBound(1).x2;

  int numberInArray = i - 1;
  return x[numberInArray];
}


double Triangle::getY(int i) const{
  std::array<double, 3> y;
  y[0] = this->getBound(0).x1;
  y[1] = this->getBound(0).y2;
  y[2] = this->getBound(1).y2;

  int numberInArray = i - 1;
  return y[numberInArray];
}

void Triangle::setM(double nM) {
    this->nM = nM;
}

void Triangle::setFj0(double nFj0) {
    this->nFj0 = nFj0;
}

void Triangle::setFji(double nFji) {
    this->nFji = nFji;
}

void Triangle::setKxi(double nKxi) {
    this->nKxi = nKxi;
}

void Triangle::setKeta(double nKeta) {
    this->nKeta = nKeta;
}

double Triangle::getM() const {
    return nM;
}

double Triangle::getFj0() const {
    return nFj0;
}

double Triangle::getFji() const {
    return nFji;
}

double Triangle::getKxi() const {
    return nKxi;
}

double Triangle::getKeta() const {
    return nKeta;
}

matrix<double> &Triangle::getU() {
    return U;
}

matrix<double> Triangle::getU() const {
    return U;
}

void Triangle::setU(matrix<double> newU) {
    U = newU;
}

int Triangle::getPolynomialOrder() const {
    return polynomialOrder;
}

//matrix<double> Triangle::getT(int j) const {
//    static matrix<double> zero(5, 5);
//    static vector<matrix<double>> T(3, zero);
//
//    static double nX;
//    static double nY;
//
//    static bool isCalculated = 0;
//
//    if (isCalculated)
//        return T[j - 1];
//    else {
//        // first border triangle
//        for (int j = 1; j <= 3; j++) {
//            nX = getBound(j).nx;
//            nY = getBound(j).ny;
//
//            T[j - 1](0, 0) = nX * nX;
//            T[j - 1](0, 1) = nY * nY;
//            T[j - 1](0, 2) = -2 * nX * nY;
//            T[j - 1](0, 3) = 0;
//            T[j - 1](0, 4) = 0;
//
//            T[j - 1](1, 0) = nY * nY;
//            T[j - 1](1, 1) = nX * nX;
//            T[j - 1](1, 2) = 2 * nX * nY;
//            T[j - 1](1, 3) = 0;
//            T[j - 1](1, 4) = 0;
//
//            T[j - 1](2, 0) = nX * nX;
//            T[j - 1](2, 1) = -nX * nY;
//            T[j - 1](2, 2) = nX * nX - nY * nY;
//            T[j - 1](2, 3) = 0;
//            T[j - 1](2, 4) = 0;
//
//            T[j - 1](3, 0) = 0;
//            T[j - 1](3, 1) = 0;
//            T[j - 1](3, 2) = 0;
//            T[j - 1](3, 3) = nX;
//            T[j - 1](3, 4) = -nY;
//
//            T[j - 1](4, 0) = 0;
//            T[j - 1](4, 1) = 0;
//            T[j - 1](4, 2) = 0;
//            T[j - 1](4, 3) = nY;
//            T[j - 1](4, 4) = nX;
//        }
//        isCalculated = true;
//        return T[j - 1];
//    }
//}

matrix<double> Triangle::getT(Bound bound) const {

      matrix<double> T(5,5);

      double nX = bound.nx;
      double nY = bound.ny;

      T(0, 0) = nX * nX;
      T(0, 1) = nY * nY;
      T(0, 2) = -2 * nX * nY;
      T(0, 3) = 0;
      T(0, 4) = 0;

      T(1, 0) = nY * nY;
      T(1, 1) = nX * nX;
      T(1, 2) = 2 * nX * nY;
      T(1, 3) = 0;
      T(1, 4) = 0;

      T(2, 0) = nX * nX;
      T(2, 1) = -nX * nY;
      T(2, 2) = nX * nX - nY * nY;
      T(2, 3) = 0;
      T(2, 4) = 0;

      T(3, 0) = 0;
      T(3, 1) = 0;
      T(3, 2) = 0;
      T(3, 3) = nX;
      T(3, 4) = -nY;

      T(4, 0) = 0;
      T(4, 1) = 0;
      T(4, 2) = 0;
      T(4, 3) = nY;
      T(4, 4) = nX;

      return T;
}
double Triangle::getMu() const {
  return mu;
}
double Triangle::getLambda() const {
  return lambda;
}
double Triangle::getRho() const {
  return rho;
}
void Triangle::setMu(double mu) {
  Triangle::mu = mu;
}
void Triangle::setLambda(double lambda) {
  Triangle::lambda = lambda;
}
void Triangle::setRho(double rho) {
  Triangle::rho = rho;
}

double Triangle::getCP() const {
  return sqrt((this->getLambda()  + 2 * this->getMu())/(this->getRho()));
}

double Triangle::getCS() const{
  return sqrt((this->getMu()) / (this->getRho()));
}

double Triangle::getS(int number) const
{
  int numberInArray = number - 1;
  static std::array<double, 5> s;
  s[0] = -1 * this->getCP();
  s[1] = -1 * this->getCS();
  s[2] = 0;
  s[3] = this->getCS();
  s[4] = this->getCP();

  return s[numberInArray];
}
