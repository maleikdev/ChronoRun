#include "counting.hpp"

Counting::Counting()
{
	m_runnersNumber = 0;
}

Counting::Counting(std::string baseFileName)
{
	m_runnersNumber = 0;

	std::ifstream baseFile(baseFileName);
	std::string fileLine;


	if (!baseFile.is_open())
	{
		std::cout << "Unable to open the base file." << std::endl;
		return;
	}


	while (std::getline(baseFile, fileLine))
	{
		///TODO split the line, to get the plate number
	}

	baseFile.close();
}

void Counting::runnerPassing(const int plate)
{
	m_tabPlate.push_back(plate);
	m_runnersNumber++;
}

void Counting::cancelPreviousPassing()
{
	
	if (m_runnersNumber > 0)
	{
		m_tabPlate.pop_back();
		m_runnersNumber--;
	}
}

int Counting::getRunnersNumber()
{
	return m_runnersNumber;
}

int Counting::getPlateInVector(const int i)
{
	return m_tabPlate[i];
}
