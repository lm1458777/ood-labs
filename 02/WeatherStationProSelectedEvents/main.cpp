#include "WeatherData.h"
#include "ObserverRegistration.h"

using namespace weather_info_observer;

int main()
{
	CWeatherData wd;

	CDisplay displayAll{ "[All]" };
	ObserverRegistration displayAllRegistration{ wd, displayAll, Parameters::All };

	//CStatsDisplay statsDisplay{ "Stats" };
	//ObserverRegistration statsDisplayRegistration{ wd, statsDisplay, Parameters::All };

	CDisplay fisherDisplay{ "[Fisher]" };
	wd.RegisterObserver(fisherDisplay, Parameters::Temperature | Parameters::Pressure);

	wd.SetMeasurements(3, 0.7, 760, Wind::FromSpeedAndDegrees(3, 180));
	std::cout << std::endl;
	wd.SetMeasurements(3, 0.7, 761, Wind::FromSpeedAndDegrees(5, 180));
	std::cout << std::endl;
	wd.SetMeasurements(3, 0.8, 761, Wind::FromSpeedAndDegrees(4, -90));
	std::cout << std::endl;
	wd.SetMeasurements(4, 0.8, 761, Wind::FromSpeedAndDegrees(2, -90));
	std::cout << std::endl;

	std::cout << "\n***** Add wind" << std::endl;
	wd.RegisterObserver(fisherDisplay, Parameters::Wind);
	wd.SetMeasurements(4, 0.8, 761, Wind::FromSpeedAndDegrees(3, -90));
	std::cout << std::endl;

	std::cout << "\n***** Remove pressure" << std::endl;
	wd.RemoveObserver(fisherDisplay, Parameters::Pressure);
	wd.SetMeasurements(4, 0.8, 760, Wind::FromSpeedAndDegrees(1, -90));
	std::cout << std::endl;

	std::cout << "\n***** Remove all" << std::endl;
	wd.RemoveObserver(fisherDisplay, Parameters::All);
	wd.SetMeasurements(-1, 0.8, 760, Wind::FromSpeedAndDegrees(1, -90));

	return 0;
}
