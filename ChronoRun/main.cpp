#include "RaceHandler.hpp"

#include <iostream>

int main(int argc, char** argv)
{
	int i = 0;
	int enteredPlate = 0;
	std::cout << "Hello World" << std::endl;

	RaceHandler countingTable("base.csv");

	countingTable.startRace();

	countingTable.runnerPassing(125);
	countingTable.runnerPassing(123);

	for (i = 0; i < countingTable.getCountedRunners(); i++)
		std::cout << "Passage number " << i << " : " << countingTable.getPlateInVector(i) << std::endl;

	countingTable.endRace();

	
	RaceHandler test;

	test.startRace();
	/*
	do
	{
		
	}while (enteredPlate != -1)
	*/
	
	return EXIT_SUCCESS;
}