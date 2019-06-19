/**
 * @file clock.hpp
 * @author DorianBDev, Romain GOUPIL - maleikdev
 * @brief File for the clock watch gestion.
 */

#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

/**
 * @struct ClockWatch
 * @brief Struct used for the timing
 * 
 * Contains all the fiels of a clock watch like the seconds, the minutes, etc
 */
struct ClockWatch
{
	long long unsigned int m_hours;
	unsigned int m_minutes;
	unsigned int m_seconds;
	unsigned int m_miliseconds;
};

/**
 * @brief Returns the actual time in miliseconds.
 * 
 * @return Returns the actual time in miliseconds.
 */
long long GetActualTimeMilisecond();


/**
* @brief Converts a time given in miliseconds in a time in usual spelling (hours, min, etc).
*
* @param[in] timeMiliseconds
*	Time in miliseconds to be converted
*
* @return
*	Time converted in a struct ClockWatch.
*/
ClockWatch* convertTimeMilisecondsInUsual(long long timeMiliseconds);


#endif