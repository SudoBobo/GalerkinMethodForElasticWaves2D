#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include "FileWriter.h"

FileWriter::FileWriter()
{
	m_source = nullptr;
}

FileWriter::FileWriter(const std::vector <double> * source,
			   std::__cxx11::string generalFileName,
			   std::__cxx11::string generalHeaderName,
			   std::__cxx11::string path,
			   const int precision, std::vector <int> gridSize) :
			m_generalFileName(generalFileName),
			m_generalHeaderName (generalHeaderName), m_path(path)
{
	m_source = source;
	m_precision = precision;
	m_gridSize = gridSize;
}

void FileWriter:: clean () const
{
	std::string command = "rm";
	command += " ";
	command += m_path;
	command += m_directory;
	command += R"(/)";
	command += "*.vtr";
	int ifCommandExecuted = std::system(command.c_str());

	command = "rm";
	command += " ";
	command += m_path;
	command += m_directory;
	command += R"(/)";
	command += "*.pvtr";
	ifCommandExecuted = std::system(command.c_str());
}

const std::string rangeString(int range)
{
	std::string rangeString;
	for (int i = 0; i <= range; i++)
	{
	 rangeString += std::to_string(i);
	 rangeString += " ";
	}
	return rangeString;
}

void FileWriter::write(const int stepNumber) const
{
	std::string fName  = m_generalFileName;
			fName += std::to_string(stepNumber);
			fName += ".vtr";

			std::string pName = m_generalHeaderName;
			pName += std::to_string(stepNumber);
			pName += ".pvtr";

			std::ofstream foutP(m_path + m_directory +  "/" + pName);
			foutP  << "<?xml version=\"1.0\"?>\n" <<
			"<VTKFile type=\"PRectilinearGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n" <<
			"<PRectilinearGrid WholeExtent=\"0 " << m_gridSize[0]  <<" 0 " << m_gridSize[1]  <<  " 0 " << m_gridSize[2] << "\" GhostLevel=\"0\">\n" <<
			"<PPointData></PPointData>\n" <<
			"<PCellData>\n" <<
				"\t<PDataArray Name=\"p\" NumberOfComponents=\"5\" type=\"Float32\"/> \n" <<
			"</PCellData>\n" <<
			"<PCoordinates>\n" <<
				"\t<PDataArray NumberOfComponents=\"1\" type=\"Float32\"/>\n" <<
				"\t<PDataArray NumberOfComponents=\"1\" type=\"Float32\"/>\n" <<
				"\t<PDataArray NumberOfComponents=\"1\" type=\"Float32\"/>\n" <<
			"</PCoordinates>\n" <<
			"<Piece Extent=\"0 " << m_gridSize[0]  << " 0 " << m_gridSize[1] << " 0 " << m_gridSize[2] << "\" Source=\"" << fName << "\" />\n" <<
			"</PRectilinearGrid>\n" <<
			"</VTKFile>";
			foutP.close();

			std::ofstream foutN(m_path + m_directory + "/" + fName);
			foutN.precision(m_precision);
			foutN  << "<?xml version=\"1.0\"?>\n" <<
			"<VTKFile type=\"RectilinearGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n" <<
			"<RectilinearGrid WholeExtent=\" 0 " << m_gridSize[0]  << " 0 " << m_gridSize[1]  << " 0 " << m_gridSize[2]  << "\">\n" <<
			"<Piece Extent=\"0 " << m_gridSize[0] << " 0 " << m_gridSize[1] << " 0 " << m_gridSize[2] << "\">\n" <<
			"<PointData>\n" <<
			 "</PointData>\n" <<
			"<CellData>\n" <<
				"\t<DataArray Name=\"p\" NumberOfComponents=\"5\" type=\"Float32\">\n"
			 << "\t\t";
			for (int i = 0; i < m_source->size(); i++)
			{
			 foutN << std::scientific << m_source->operator [](i) << " "; /*<< " " << m_source->operator [](i) << " " << m_source->operator [](i) << " ";*/
			}
			foutN << "\n";
			foutN << "</DataArray>\n" << "</CellData>\n"<<
			"<Coordinates>\n" <<
				"\t<DataArray NumberOfComponents=\"1\" type=\"Float32\">\n" <<
					"\t\t" << rangeString(m_gridSize[0]) << "\n" <<
			"</DataArray>\n"
			"\t<DataArray NumberOfComponents=\"1\" type=\"Float32\">\n" <<
					"\t\t" << rangeString(m_gridSize[1]) << "\n" <<
			"</DataArray>\n" <<
				"\t<DataArray NumberOfComponents=\"1\" type=\"Float32\">" << rangeString(m_gridSize[2]) << "</DataArray>\n" <<
			"</Coordinates>\n" <<
			"</Piece>\n" <<
			"</RectilinearGrid>\n" <<
			"</VTKFile>\n";
			foutN.close();
}


void FileWriter::setPath(std::string newPath)
{
	m_path = newPath;
}

std::string FileWriter::getPath() const
{
	return m_path;
}
void FileWriter::setDirectory(std::string newDirectory)
{
	m_directory = newDirectory;
}

void FileWriter::setGeneralFileName(std::string newGeneralFileName)
{
	m_generalFileName = newGeneralFileName;
}

void FileWriter::setGeneralHeaderName(std::string newGeneralHeaderName)
{
	m_generalHeaderName = newGeneralHeaderName;
}

void FileWriter::setPrecision (const int newPrecision)
{
	m_precision = newPrecision;
}

void FileWriter::setGridSize(std::vector <int> newGridSize)
{
	m_gridSize = newGridSize;
}

void FileWriter::setSource(std::vector<double> newSource)
{
	m_source = &newSource;
}

void FileWriter::setSource(std::vector<double> * newSource)
{
	m_source = newSource;
}
