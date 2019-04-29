#include "counting.hpp"

#include <iostream>

int main(int argc, char** argv)
{
	int i = 0;
	std::cout << "Hello World" << std::endl;

	Counting countingTable("base.csv");

	countingTable.runnerPassing(125);
	countingTable.runnerPassing(123);

	for (i = 0; i < countingTable.getCountedRunners(); i++)
		std::cout << "Passage numero " << i << " : " << countingTable.getPlateInVector(i) << std::endl;
	
	return EXIT_SUCCESS;
}