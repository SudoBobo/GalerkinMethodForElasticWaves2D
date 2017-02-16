#include "TriangleMesh.h"
#include "RectangleMesh.h"
#include "Support.h"

TriangleMesh::TriangleMesh(double xSize, double ySize, double rectangleSide,
						   double lambda, double mu, double rho,
						   int polynomialOrder, int uSize)
{
	mesh = createRegularTriangelMesh(xSize, ySize, rectangleSide, lambda, mu,
									 rho, polynomialOrder, uSize);
	maxN = xSize / rectangleSide - 1;
	maxM = ySize / rectangleSide - 1;
}

TriangleMesh::TriangleMesh(const TriangleMesh & another):
	maxN(another.getMaxN()), maxM(another.getMaxM()), mesh(another.getMesh())
{

}


const std::vector <Triangle> & TriangleMesh::getMesh() const
{
	return mesh;
}

std::vector <Triangle> & TriangleMesh::getMesh()
{
	return mesh;
}



SourceWrapper TriangleMesh::makeSourceWrapper() const
{
	RectangleMesh rectangleMesh(*this);
	auto wrappedSource = rectangleMesh.makeSourceWrapper();
	return wrappedSource;

	/*
	 * better do like this
	 * static RectangleMesh rectangleMesh(triangleMesh);
	 * rectangleMesh.reFill(triangleMesh);
	 * auto wrappedSource = rectangleMesh.makeSourceWrapper();
	 * return wrappedSource;
	*/
}
