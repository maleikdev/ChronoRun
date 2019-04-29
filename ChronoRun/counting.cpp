#include "counting.hpp"

Counting::Counting()
{
	m_runnersNumber = 0;
}

Counting::Counting(const char* baseFileName)
{
	m_runnersNumber = 0;

	std::cout << "ok1" << std::endl;

	if (!baseFileName)
		return;

	std::cout << "ok2" << std::endl;

	int tempPlate = 0;
	std::ifstream baseFile(baseFileName, std::ios::in);
	std::string fileLine;


	if (!baseFile.is_open())
	{
		std::cout << "Unable to open the base file." << std::endl;
		return;
	}

	std::cout << "ok3" << std::endl;
	std::getline(baseFile, fileLine);

	while (!baseFile.eof())
	{
		///TODO split the line, to get the plate number
		std::cout << "ok4" << std::endl;
		baseFile >> tempPlate;

		baseFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n')

		std::cout << tempPlate << std::endl;
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
