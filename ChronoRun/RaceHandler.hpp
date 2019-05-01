#define _CRT_SECURE_NO_WARNINGS

/**
* @file		raceEndler.hpp
* @author	Romain GOUPIL - maleikdev
*
* @brief	File for the counting part.
*
* @details	Declaration of the class for the counting table, and loading of the plates database for checking errors during the counting.
*/

#ifndef COUNTING_HPP
#define COUNTING_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>

#define SKIP_LINE(file) file.ignore(std::numeric_limits<std::streamsize>::max(), '\n')


struct Racer
{
	int m_plate;
	std::vector<time_t> m_passingTimes;
};

/**
* @class RaceHandler
*
* @brief	Class for the pointing table.
*/
class RaceHandler
{
public:
	RaceHandler();
	RaceHandler(const char* baseFileName);

	void startRace();
	void endRace();
	void runnerPassing(const int plate);
	void cancelPreviousPassing();

	int getRunnersNumber();
	int getCountedRunners();
	int getPlateInVector(const int i);

	bool isInDatabase(const int plate);
	int isInPreRanking(const int plate);

	void generatePreRanking();

private:
	std::vector<int> m_passedPlates;
	std::vector<int> m_basePlates;
	std::vector<time_t> m_passedTimes;
	std::vector<Racer> m_preRanking;
	int m_runnersNumber;
	int m_countedRunners;
	bool m_raceIsRunning;
	time_t m_startTime;
	time_t m_endTime;
};

#endif // !COUNTING_HPP