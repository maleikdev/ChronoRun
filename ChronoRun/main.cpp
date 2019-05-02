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
	
	do
	{
		std::cout << "Pointage, entrez la plaque ou sinon entrez -1 pour quitter le pointage." << std::endl;
		std::cin >> enteredPlate;

		if (enteredPlate > -1)
			test.runnerPassing(enteredPlate);
	} while (enteredPlate != -1);

	test.endRace();

	for (i = 0; i < test.getCountedRunners(); i++)
		std::cout << "Passage number " << i << " : " << test.getPlateInVector(i) << std::endl;

	
	
	
	return EXIT_SUCCESS;
}