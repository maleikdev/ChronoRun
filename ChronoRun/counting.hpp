#ifndef COUNTING_HPP
#define COUNTING_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <string>


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