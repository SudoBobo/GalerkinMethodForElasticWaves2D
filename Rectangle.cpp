#include "Rectangle.h"

Rectangle::Rectangle(std::vector <Triangle> & triangles)
{

		if (triangles.size() != 4){
			throw(std::range_error("One rectangle is maid of 4 triangles"));
		}

		if  (true) /*((triangles[0].getNumberInRectangle() == 0) &&
			 (triangles[1].getNumberInRectangle() == 1) &&
			 (triangles[2].getNumberInRectangle() == 2) &&
			 (triangles[3].getNumberInRectangle() == 3))*/
		{
			// algorithm down here described in document pic 2
			matrix<matrix<double>> meshForRectangle(3,3);
			matrix<matrix<double>> & m = meshForRectangle;


			auto t0 = triangles[0].getU();
			auto t1 = triangles[1].getU();
			auto t2 = triangles[2].getU();
			auto t3 = triangles[3].getU();

			/*
			 * don't miss orientation
			 * m(2,0) m(2,1) m(2,2)
			 * m(1,0) m(1,1) m(1,2)
			 * m(0,0) m(0,1) m(0,2)
			 */

			m(2,0) = (t0 + t1) * 0.5;
			m(2,1) = t1;
			m(2,2) = (t1 + t2) * 0.5;

			m(1,0) = t0;
			m(1,1) = (t0 + t1 + t2 + t3) * 0.25;
			m(1,2) = t2;

			m(0,0) = (t0 + t3) * 0.5;
			m(0,1) = t3;
			m(0,2) = (t3 + t2) * 0.5;

			mesh = meshForRectangle;
			rectangleN = triangles[0].getRectangleN();
			rectangleM = triangles[0].getRectangleM();
		}

		else
		{
			throw(std::range_error("Mistake in createRectangleFromFourTriangles"));
		}
}

const matrix<matrix<double> > &Rectangle::getMesh() const
{
	return mesh;
}


//int				number;
//int				rectangleN;
//int				rectangleM;

///*
// * (2,0) (2,1) (2,2)
// * (1,0) (1,1) (1,2)
// * (0,0) (0,1) (0,2)
// *
// * this way it goes into the source file
// */

//matrix <double> mesh;
