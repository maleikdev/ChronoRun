#define _CRT_SECURE_NO_WARNINGS

/**
* @file		counting.hpp
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

/**
* @class	Counting
*
* @brief	Class for the pointing table.
*/
class Counting
{
public:
	Counting();
	Counting(const char* baseFileName);

	void startRace();
	void runnerPassing(const int plate);
	void cancelPreviousPassing();

	int getRunnersNumber();
	int getCountedRunners();
	int getPlateInVector(const int i);

	bool isInDatabase(const int plate);

private:
	std::vector<int> m_tabPlate;
	std::vector<int> m_basePlate;
	int m_runnersNumber;
	int m_countedRunners;
	bool raceIsRunning;
	time_t m_startTime;
	time_t m_endTime;
};

#endif // !COUNTING_HPP