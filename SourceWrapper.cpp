#include "SourceWrapper.h"

SourceWrapper::SourceWrapper(int uSize, int xSize, int ySize, int zSize,
			  std::vector<double> source)
	: uSize(uSize), xSize(xSize), ySize(ySize), zSize(zSize)
{
	this->source = source;
}

int SourceWrapper::getUSize() const
{
	return uSize;
}
int SourceWrapper::getXSize() const
{
	return xSize;
}
int SourceWrapper::getYSize() const
{
	return ySize;
}
int SourceWrapper::getZSize() const
{
	return zSize;
}
