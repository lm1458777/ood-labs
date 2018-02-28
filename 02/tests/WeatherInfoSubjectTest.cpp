#include "stdafx.h"
#include "../WeatherStationProSelectedEvents/CObservable.h"
#include "../WeatherStationProSelectedEvents/ObserverRegistration.h"

using namespace std;
using namespace weather_info_observer;

namespace
{

using ChangedData = pair<SWeatherInfo, Parameters>;

class TestSubject : public CObservable
{
public:
	ChangedData changedData;

protected:
	ChangedData GetChangedData() const override
	{
		return changedData;
	}
};

class MockObserver : public IWeatherInfoObserver
{
public:
	unique_ptr<ChangedData> changedData;

	void Update(SWeatherInfo const& data, Parameters parameters) override
	{
		changedData = make_unique<ChangedData>(data, parameters);
	}
};

} // namespace

SCENARIO("The observer subscribes to the changes that interest him")
{
	GIVEN("The subject and an unregistered observer")
	{
		TestSubject subject;
		MockObserver observer;

		WHEN("the subject notifies observers")
		{
			subject.changedData.first.pressure = 42;
			subject.changedData.second = Parameters::All;
			subject.NotifyObservers();

			THEN("an observer does not receive notification")
			{
				CHECK(!observer.changedData);
			}
		}
	}

	GIVEN("The subject and an observer")
	{
		TestSubject subject;
		MockObserver observer;

		WHEN("an observer subscribes to the pressure change")
		{
			ObserverRegistration reg{ subject, observer, Parameters::Pressure };

			AND_WHEN("the pressure is changed")
			{
				subject.changedData.first.pressure = 4;
				subject.changedData.second = Parameters::Pressure;
				subject.NotifyObservers();

				THEN("an observer is notified")
				{
					REQUIRE(observer.changedData);
					CHECK_EQ(observer.changedData->first.pressure, 4);
					CHECK_EQ(observer.changedData->second, Parameters::Pressure);
				}
			}

			AND_WHEN("all parameters are changed")
			{
				subject.changedData.first.pressure = 5;
				subject.changedData.second = Parameters::All;
				subject.NotifyObservers();

				THEN("an observer is notified")
				{
					REQUIRE(observer.changedData);
					CHECK_EQ(observer.changedData->first.pressure, 5);
					CHECK_EQ(observer.changedData->second, Parameters::Pressure);
				}
			}

			AND_WHEN("the humidity is changed")
			{
				subject.changedData.first.humidity = 6;
				subject.changedData.second = Parameters::Humidity;
				subject.NotifyObservers();

				THEN("an observer does not receive notification")
				{
					CHECK(!observer.changedData);
				}
			}

			AND_WHEN("registration is canceled")
			{
				reg.CancelRegistration();

				AND_WHEN("the pressure is changed")
				{
					subject.changedData.first.pressure = 4;
					subject.changedData.second = Parameters::Pressure;
					subject.NotifyObservers();

					THEN("an observer does not receive notification")
					{
						CHECK(!observer.changedData);
					}
				}
			}
		}

		WHEN("an observer subscribes to the temperature and the pressure change")
		{
			subject.RegisterObserver(observer, Parameters::Temperature | Parameters::Pressure);

			AND_WHEN("the pressure is changed")
			{
				subject.changedData.first.pressure = 8;
				subject.changedData.second = Parameters::Pressure;
				subject.NotifyObservers();

				THEN("an observer is notified")
				{
					REQUIRE(observer.changedData);
					CHECK_EQ(observer.changedData->first.pressure, 8);
				}
			}
			AND_WHEN("the temperature is changed")
			{
				subject.changedData.first.temperature = -273;
				subject.changedData.second = Parameters::Temperature;
				subject.NotifyObservers();

				THEN("an observer is notified")
				{
					REQUIRE(observer.changedData);
					CHECK_EQ(observer.changedData->first.temperature, -273);
				}
			}
			AND_WHEN("the registration for the temperature change is canceled")
			{
				subject.RemoveObserver(observer, Parameters::Temperature);

				AND_WHEN("the temperature is changed")
				{
					subject.changedData.first.temperature = -5;
					subject.changedData.second = Parameters::Temperature;
					subject.NotifyObservers();

					THEN("an observer does not receive notification")
					{
						CHECK(!observer.changedData);
					}
				}
				AND_WHEN("the pressure is changed")
				{
					subject.changedData.first.pressure = 760;
					subject.changedData.second = Parameters::Pressure;
					subject.NotifyObservers();

					THEN("an observer is notified")
					{
						REQUIRE(observer.changedData);
						CHECK_EQ(observer.changedData->first.pressure, 760);
					}
				}
			}
		}
	}
}
