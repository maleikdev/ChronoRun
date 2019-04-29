#include "counting.hpp"

Counting::Counting()
{
	m_runnersNumber  = 0;
	m_countedRunners = 0;
}

Counting::Counting(const char* baseFileName)
{
	m_runnersNumber  = 0;
	m_countedRunners = 0;

	if (!baseFileName)
		return;
	
	int tempPlate = 0;
	char gotChar = 0;
	std::ifstream baseFile(baseFileName, std::ios::in);
	std::string fileLine;


	if (!baseFile.is_open())
	{
		std::cout << "Unable to open the base file." << std::endl;
		return;
	}

	std::getline(baseFile, fileLine);

	//Load the plates from the databse in a vector
	while (!baseFile.eof())
	{
		tempPlate = 0;
		
		while (true)
		{
			baseFile.get(gotChar);
			if (gotChar == ';' || gotChar < 48 || gotChar > 57)
				break;

			tempPlate = (tempPlate * 10) + (int)gotChar - 48;
		}

		if (tempPlate == 0)
			continue;

		m_basePlate.push_back(tempPlate);
		m_runnersNumber++;

		SKIP_LINE(baseFile);

	}

	baseFile.close();
}

void Counting::runnerPassing(const int plate)
{
	m_tabPlate.push_back(plate);
	m_countedRunners++;
}

void Counting::cancelPreviousPassing()
{
	
	if (m_runnersNumber > 0)
	{
		m_tabPlate.pop_back();
		m_countedRunners--;
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
