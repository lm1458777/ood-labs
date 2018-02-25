#include "WeatherData.h"

#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, Wind{ 3, M_PI });
	wd.SetMeasurements(4, 0.8, 761, Wind{ 4, -M_PI_2 });

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, Wind{ 6, 0 });
	wd.SetMeasurements(-10, 0.8, 761, Wind{ 8, -M_PI });
	return 0;
}