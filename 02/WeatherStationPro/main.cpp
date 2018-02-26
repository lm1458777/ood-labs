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

	wd.SetMeasurements(3, 0.7, 760, Wind::FromSpeedAndDegrees(3, 180));
	wd.SetMeasurements(4, 0.8, 761, Wind::FromSpeedAndDegrees(4, -90));

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, Wind::FromSpeedAndDegrees(6, 0));
	wd.SetMeasurements(-10, 0.8, 761, Wind::FromSpeedAndDegrees(8, -180));

	return 0;
}
