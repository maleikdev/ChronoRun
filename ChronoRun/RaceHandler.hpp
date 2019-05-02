#define _CRT_SECURE_NO_WARNINGS

/**
* @file		raceEndler.hpp
* @author	Romain GOUPIL - maleikdev
* @brief	File for the counting part.
*
* Declaration of the class for the counting table, and loading of the plates database for checking errors during the counting.
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
 * @struct Racer
 * @brief Struct used to build the previous ranking and the ranking.
 * 
 * It contains the plate of the racer and a vector for his/her passing times.
 */
struct Racer
{
	int m_plate;
	std::vector<time_t> m_passingTimes;
};

/**
* @class RaceHandler
* @brief Class for the pointing table.
*/
class RaceHandler
{
public:
	/**
	 * @brief Constructor, without the database loading.
	 */
	RaceHandler();

	/**
	 * @brief Constructor, with the database loading.
	 * 
	 * @param[in] baseFileName
	 *    Database file name.
	 */
	RaceHandler(const char* baseFileName);

	/**
	 * @brief Starts the race.
	 * 
	 * Initialize m_startTime to the actual time and set m_raceIsRunning to true.
	 */
	void startRace();

	/**
	 * @brief Ends the race.
	 * 
	 * Initialize m_endTime to the actual time and set m_raceIsRunning to false.
	 */
	void endRace();

	/**
	 * @brief The function of counting.
	 * 
	 * Pushes back the plate in m_passedPlates and the actual time in m_passedTimes.
	 * 
	 * @param[in] plate
	 *    Plate of the runner to count.
	 */
	void runnerPassing(const int plate);

	/**
	 * @brief Cancels the previous counting.
	 * 
	 * Popes back m_passedPlates and m_passedTimes.
	 */
	void cancelPreviousPassing();

	/**
	 * @brief Returns the number of racers in the database.
	 * 
	 * @return
	 *     Number of racers in the database.
	 */
	int getRunnersNumber();

	/**
	 * @brief Returns the number of countings.
	 * 
	 * @return
	 *     Number of counted racers.
	 */
	int getCountedRunners();

	/**
	 * @brief Return the value in the square i of m_passedPlates.
	 * 
	 * @param[in] i
	 *     Grade to seek.
	 * 
	 * @return
	 *     Value stored in the square i of m_passedPlates.
	 */
	int getPlateInVector(const int i);

	/**
	 * @brief Says if a plate is in the database.
	 * 
	 * @param[in] plate
	 *     Plate to seek.
	 *     
	 * @return
	 *    Return true or false if the plate has been found or not.
	 */
	bool isInDatabase(const int plate);

	/**
	 * @brief Says if a plate is in the preRanking
	 * 
	 * @param[in] plate.
	 *    Plate to seek.
	 *    
	 * @return
	 *    Return -1 if the plate is not in the preRanking or the grade if it is.
	 */
	int isInPreRanking(const int plate);

	/**
	 * @brief With m_passedPlates and m_passedTimes, generates a preRanking (which is a ranking, but not sorted).
	 */
	void generatePreRanking();

	/**
	 * @brief Displays the preRanking on the console.
	 */
	void displayPreRanking();

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