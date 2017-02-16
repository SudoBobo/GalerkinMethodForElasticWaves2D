//#ifndef FILEWRITER_H
//#define FILEWRITER_H

//#include <string>
//#include <vector>

//using std::pair;

//class FileWriter
//{
//public:
//	FileWriter();
//	FileWriter(std::vector <pair<double, double>> * source, std::string generalFileName,
//		   std::string generalHeaderName, std::string path,
//		   const int precision, std::vector <int> gridSize);
//	void write(const int stepNumber) const;
//	void clean() const;
//	void setPath(std::string newPath);
//	std::string getPath() const;
//	void setDirectory(std::string newDirectory);
//	void setGeneralFileName(std::string newGeneralFileName);
//	void setGeneralHeaderName(std::string newGeneralHeadeName);
//	void setPrecision (const int newPrecision);
//	void setGridSize(std::vector <int> newGridSize);
//	void setSource(std::vector <pair<double, double>> newSource);
////	void setSource(std::vector <double> * newSource);

//private:
//	std::vector <pair<double, double>> * m_source;
//	std::string m_generalFileName;
//	std::string m_generalHeaderName;
//	std::string m_directory;
//	std::string m_path;
//	int               m_precision;
//	std::vector <int> m_gridSize;
//};

//#endif // FILEWRITER_H


#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>
#include <vector>

class FileWriter
{
public:
	FileWriter();
	FileWriter(const std::vector <double> * source, std::string generalFileName,
		   std::string generalHeaderName, std::string path,
		   const int precision, std::vector <int> gridSize);
	void write(const int stepNumber) const;
	void clean() const;
	void setPath(std::string newPath);
	std::string getPath() const;
	void setDirectory(std::string newDirectory);
	void setGeneralFileName(std::string newGeneralFileName);
	void setGeneralHeaderName(std::string newGeneralHeadeName);
	void setPrecision (const int newPrecision);
	void setGridSize(std::vector <int> newGridSize);
	void setSource(std::vector <double> newSource);
	void setSource(std::vector <double> * newSource);

private:
	const std::vector <double> * m_source;
	std::string m_generalFileName;
	std::string m_generalHeaderName;
	std::string m_directory;
	std::string m_path;
	int               m_precision;
	std::vector <int> m_gridSize;
};

#endif // FILEWRITER_H
