/**
 * @file RacerHandler.cpp
 * @author Romain GOUPIL - maleikdev
 * @brief File for the Race handling part.
 *
 * Declaration of the class for the counting table, and loading of the plates database for checking errors during the counting.
 *
 */

#include "RaceHandler.hpp"

RaceHandler::RaceHandler()
{
	m_runnersNumber  = 0;
	m_countedRunners = 0;
	m_raceIsRunning    = false;
	m_startTime      = 0;
	m_endTime        = 0;
}

RaceHandler::RaceHandler(const char* baseFileName)
{
	m_runnersNumber  = 0;
	m_countedRunners = 0;
	m_raceIsRunning    = false;
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

	m_startTime = GetActualTimeMilisecond();
	m_raceIsRunning = true;

	///TODO : Find a safe equivalent for localtime().
	//clockFormatTime = localtime(&m_startTime);

	//std::cout << "Race started at " << clockFormatTime->tm_hour << ":" << clockFormatTime->tm_min << ":" << clockFormatTime->tm_sec << std::endl;

}

void RaceHandler::endRace()
{
	struct tm* clockFormatTime;

	m_endTime = GetActualTimeMilisecond();
	m_raceIsRunning = false;

	///TODO : Find a safe equivalent for localtime().
	//clockFormatTime = localtime(&m_startTime);

	//std::cout << "Race ended at " << clockFormatTime->tm_hour << ":" << clockFormatTime->tm_min << ":" << clockFormatTime->tm_sec << std::endl;
}

void RaceHandler::runnerPassing(const int plate)
{
	if (!m_raceIsRunning)
	{
		std::cout << "Race is not running, impossible to count the racers !" << std::endl;
		return;
	}

	m_passedPlates.push_back(plate);
	m_passedTimes.push_back(GetActualTimeMilisecond());
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

int RaceHandler::getRunnersNumber() const
{
	return m_runnersNumber;
}

int RaceHandler::getCountedRunners() const
{
	return m_countedRunners;
}

int RaceHandler::getPlateInVector(const int i) const
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

int RaceHandler::isInPreRanking(const int plate)
{
	for (unsigned int i = 0 ; i < m_preRanking.size() ; i++)
	{
		if (m_preRanking[i].m_plate == plate)
			return i;
	}

	return -1;
}

void RaceHandler::generatePreRanking()
{
	int i = 0;
	int countingTableIndicator = 0;
	Racer tempRacerBeforePushBack;

	for (i = 0 ; i < m_countedRunners ; i++)
	{
		countingTableIndicator = isInPreRanking(m_passedPlates[i]);
		if (countingTableIndicator > -1)
		{
			m_preRanking[countingTableIndicator].m_passingTimes.push_back(m_passedTimes[i]);
		}
		else
		{
			tempRacerBeforePushBack.m_plate = m_passedPlates[i];
			tempRacerBeforePushBack.m_passingTimes.push_back(m_passedTimes[i]);
			m_preRanking.push_back(tempRacerBeforePushBack);

			tempRacerBeforePushBack.m_plate = 0;
			tempRacerBeforePushBack.m_passingTimes.clear();
		}
	}
}

void RaceHandler::displayPreRanking() const
{
	int i = 0, j = 0;

	for (i = 0 ; i < m_preRanking.size() ; i++)
	{
		std::cout << "Racer no " << m_preRanking[i].m_plate << " Passages : ";
		for (j = 0 ; j < m_preRanking[i].m_passingTimes.size() ; j++)
		{
			std::cout << " # " << m_preRanking[i].m_passingTimes[j];
		}
		std::cout << std::endl;
	}
}

void RaceHandler::generateRanking()
{
	Racer tempForTransfer;
	m_Ranking.assign(m_preRanking.begin(), m_preRanking.end());


	//Sort by the number of laps done
	for (unsigned int i = 0 ; i < m_preRanking.size() ; i++)
	{
		for (unsigned int j = 0 ; j < m_preRanking.size() - 1; j++)
		{
			if (m_Ranking[j + 1].m_passingTimes.size() > m_Ranking[j].m_passingTimes.size())
			{
				tempForTransfer = m_Ranking[j];
				m_Ranking[j] = m_Ranking[j + 1];
				m_Ranking[j + 1] = tempForTransfer;
			}
		}
	}

	for (unsigned int i = 0; i < m_preRanking.size(); i++)
	{
		for (unsigned int j = 0; j < m_preRanking.size() - 1; j++)
		{
			if (m_Ranking[j + 1].m_passingTimes.size() != m_Ranking[j].m_passingTimes.size())
				continue;;

			if (m_Ranking[j + 1].m_passingTimes.back() < m_Ranking[j].m_passingTimes.back())
			{
				tempForTransfer = m_Ranking[j];
				m_Ranking[j] = m_Ranking[j + 1];
				m_Ranking[j + 1] = tempForTransfer;
			}
		}
	}
}

void RaceHandler::displayRanking() const
{
	///TODO: Convert former time format in the new time format (GetACtualTime)
	ClockWatch* clock;
	long long tempPassTime;

	///TODO: Find a safe equivalent to localtime

	std::cout << "Ranking";
	for (unsigned int i = 0; i < m_Ranking[0].m_passingTimes.size(); i++)
		std::cout << " # LAP No " << i;

	std::cout << std::endl;

	for (unsigned int i = 0 ; i < m_Ranking.size() ; i++)
	{
		std::cout << "Racer no " << m_Ranking[i].m_plate << " Passages : ";
		for (unsigned int j = 0; j < m_Ranking[i].m_passingTimes.size(); j++)
		{
			tempPassTime = m_Ranking[i].m_passingTimes[j] - m_startTime;


			clock = convertTimeMilisecondsInUsual(tempPassTime);
			std::cout << " # " << clock->m_hours << ":" << clock->m_minutes << ":" << clock->m_seconds << ":" << clock->m_miliseconds;

			delete clock;
		}
		std::cout << std::endl;
	}
}
