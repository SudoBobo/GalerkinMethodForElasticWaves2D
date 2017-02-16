#ifndef SOURCEWRAPPER_H
#define SOURCEWRAPPER_H

#include <vector>

class SourceWrapper
{
public:
	SourceWrapper(int uSize, int xSize, int ySize, int zSize,
				  std::vector<double> source);
	int getUSize() const;
	int getXSize() const;
	int getYSize() const;
	int getZSize() const;
	const std::vector <double> * getSource() const{
		return &source;
	}
private:
	int uSize;
	int xSize;
	int ySize;
	int zSize;
	std::vector <double> source;
};

#endif // SOURCEWRAPPER_H
