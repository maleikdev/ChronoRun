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
	
	void runnerPassing(const int plate);
	void cancelPreviousPassing();

	int getRunnersNumber();
	int getPlateInVector(const int i);

private:
	std::vector<int> m_tabPlate;
	std::vector<int> m_basePlate;
	int m_runnersNumber;
	int m_countedRunners;
};

#endif // !COUNTING_HPP