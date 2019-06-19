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

	time_t t = 0;
	
	struct tm* cl = localtime(&t);

	std::cout << "hour " << cl->tm_hour << ":" << cl->tm_min << ":" << cl->tm_sec << std::endl;

	std::cout << "actual time ms : " << GetActualTimeMilisecond() << std::endl;
	
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

	test.generatePreRanking();

	test.displayPreRanking();

	test.generateRanking();

	test.displayRanking();
	
	
	return EXIT_SUCCESS;
}