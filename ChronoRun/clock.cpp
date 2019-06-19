/**
 * @file clock.cpp
 * @author DorianBDev, Romain GOUPIL - maleikdev
 * @brief File for the clock watch gestion.
 */

#include "clock.hpp"


long long GetActualTimeMilisecond()
{
	return static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

ClockWatch* convertTimeMilisecondsInUsual(long long timeMiliseconds)
{
	///TODO: Maybe we should make this function better... How ?

	ClockWatch* watch = new ClockWatch;

	watch->m_hours = timeMiliseconds / (long long unsigned int)3600000;
	timeMiliseconds -= watch->m_hours * 3600000;
	watch->m_minutes = timeMiliseconds / (unsigned int)60000;
	timeMiliseconds -= watch->m_minutes * 60000;
	watch->m_seconds = timeMiliseconds / (unsigned int)1000;
	timeMiliseconds -= watch->m_seconds * 1000;
	watch->m_miliseconds = timeMiliseconds;

	return watch;
}
