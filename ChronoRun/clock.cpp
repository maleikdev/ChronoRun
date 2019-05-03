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
