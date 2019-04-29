#ifndef COUNTING_HPP
#define COUNTING_HPP

/**
* @file		counting.hpp
*
* @author	Romain GOUPIL - maleikdev
*
* @version	1.0
*
* @brief	File for the counting part.
*
* @details	Declaration of the class for the counting table, and loading of the plates database for checking errors during the counting.
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

/**
* @class	Counting
*
* @brief	Class for the pointing table.
*/
class Counting
{
public:
	Counting();
	Counting(std::string baseFileName);
	
	void runnerPassing(const int plate);
	void cancelPreviousPassing();

	int getRunnersNumber();
	int getPlateInVector(const int i);

private:
	std::vector<int> m_tabPlate;
	std::vector<int> m_basePlate;
	int m_runnersNumber;
};

#endif // !COUNTING_HPP