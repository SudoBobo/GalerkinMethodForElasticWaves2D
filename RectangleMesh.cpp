#include "RectangleMesh.h"
#include "Rectangle.h"
#include "SourceWrapper.h"

RectangleMesh::RectangleMesh(const TriangleMesh & triangleMesh)
{

	maxM = triangleMesh.getMaxM();
	maxN = triangleMesh.getMaxN();

	auto triangleInnerMesh = triangleMesh.getMesh();

	for (auto t0 = triangleInnerMesh.begin();
		 (t0+4) <= triangleInnerMesh.end(); t0 = t0+4)
	{
		// не было пустого конструктора
		std::vector <Triangle> triangles;
		triangles.push_back(* t0);
		triangles.push_back(* (t0+1));
		triangles.push_back(* (t0+2));
		triangles.push_back(* (t0+3));


		Rectangle rectangle(triangles);
		mesh.push_back(rectangle);
	}
}


int RectangleMesh::getMaxN() const
{
	return maxN;
}

int RectangleMesh::getMaxM() const
{
	return maxM;
}
std::vector<double> RectangleMesh:: makeSource() const
{
	std::vector <double> source;
	int numberOfLines = 3;
	int numberOfColumns = 3;
	for (int M = 0; M <= maxM; M++)
	{
		for (int nLine = 0; nLine < numberOfLines; nLine++)
		{
			for (int N = 0; N <= maxN; N++)
			{
				for (int nColumn = 0; nColumn < numberOfColumns; nColumn++)
				{
					for (int p = 0; p < 5; p++)
					{
					double vectorComponent = mesh[M+N].getMesh()(nLine, nColumn)(p,0);
					source.push_back(vectorComponent);
					}
				}
			}
		}
	}
	return source;
}

SourceWrapper RectangleMesh::makeSourceWrapper() const
{
	// каждому прямоугольнику соответствует по пять цифр
	int uSize = 5;
	auto source = makeSource();
	SourceWrapper sourceWrapper(uSize, this->getMaxN(), this->getMaxM(), 0,
							   source);
	return sourceWrapper;
}

//std::vector <double> RectangleMesh::RectangleMesh() const
//{

//}
