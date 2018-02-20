#include "WeatherData.h"

int main()
{
	using namespace observer;
	using Registration = ObserverRegistration<SWeatherInfo>;

	CWeatherData wdExternal{ "External" };
	CWeatherData wdInternal{ "Internal" };

	CDisplay display;
	Registration regExtDisplay{ wdExternal, display };
	Registration regIntDisplay{ wdInternal, display };

	CStatsDisplay statsDisplay;
	Registration regExtStat{ wdExternal, statsDisplay };
	Registration regIntStat{ wdInternal, statsDisplay };

	wdInternal.SetMeasurements(20, 0.45, 758);

	wdExternal.SetMeasurements(3, 0.7, 760);
	wdExternal.SetMeasurements(4, 0.8, 761);

	regExtStat.CancelRegistration();

	wdExternal.SetMeasurements(10, 0.8, 761);
	wdExternal.SetMeasurements(-10, 0.8, 761);

	wdInternal.SetMeasurements(21, 0.42, 756);

	return 0;
}