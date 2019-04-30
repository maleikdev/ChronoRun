#include "raceEndler.hpp"

RaceHandler::RaceHandler()
{
	m_runnersNumber  = 0;
	m_countedRunners = 0;
	raceIsRunning    = false;
	m_startTime      = 0;
	m_endTime        = 0;
}

RaceHandler::RaceHandler(const char* baseFileName)
{
	m_runnersNumber  = 0;
	m_countedRunners = 0;
	raceIsRunning    = false;
	m_startTime      = 0;
	m_endTime        = 0;

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
			if (!isdigit(gotChar))
				break;

			tempPlate = (tempPlate * 10) + (int)gotChar - 48;
		}

		if (tempPlate == 0)
			continue;

		m_basePlates.push_back(tempPlate);
		m_runnersNumber++;

		SKIP_LINE(baseFile);

	}

	baseFile.close();
}

void RaceHandler::startRace()
{
	struct tm* clockFormatTime;

	m_startTime = time(NULL);
	raceIsRunning = true;

	///TODO : Find a safe equivalent for localtime().
	clockFormatTime = localtime(&m_startTime);

	std::cout << "Race started at " << clockFormatTime->tm_hour << ":" << clockFormatTime->tm_min << ":" << clockFormatTime->tm_sec << std::endl;

}

void RaceHandler::endRace()
{
	struct tm* clockFormatTime;

	m_endTime = time(NULL);
	raceIsRunning = false;

	///TODO : Find a safe equivalent for localtime().
	clockFormatTime = localtime(&m_startTime);

	std::cout << "Race ended at " << clockFormatTime->tm_hour << ":" << clockFormatTime->tm_min << ":" << clockFormatTime->tm_sec << std::endl;
}

void RaceHandler::runnerPassing(const int plate)
{
	if (!raceIsRunning)
	{
		std::cout << "Race is not running, impossible to count the racers !" << std::endl;
		return;
	}

	m_passedPlates.push_back(plate);
	m_passedTimes.push_back(time(NULL));
	m_countedRunners++;

	if (!isInDatabase(plate))
		std::cout << "Warning ! " << plate << " is not in the database !" << std::endl;
}

void RaceHandler::cancelPreviousPassing()
{
	
	if (m_runnersNumber > 0)
	{
		m_passedPlates.pop_back();
		m_passedTimes.pop_back();
		m_countedRunners--;
	}
}

int RaceHandler::getRunnersNumber()
{
	return m_runnersNumber;
}

int RaceHandler::getCountedRunners()
{
	return m_countedRunners;
}

int RaceHandler::getPlateInVector(const int i)
{
	return m_passedPlates[i];
}

bool RaceHandler::isInDatabase(const int plate)
{
	int i    = 0;

	for (i = 0; i < m_runnersNumber; i++)
	{
		if (m_basePlates[i] == plate)
			return true;
	}
	
	return false;
}
