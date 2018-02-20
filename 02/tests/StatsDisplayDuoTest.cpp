#include "stdafx.h"
#include "../WeatherStationDuo/WeatherData.h"

using Registration = observer::ObserverRegistration<SWeatherInfo>;

static void ValidateStats(const StatsData& stats,
	StatsData::Value avgValue, StatsData::Value minValue, StatsData::Value maxValue)
{
	CHECK(stats.HasData());
	CHECK(stats.GetAverageValue() == doctest::Approx(avgValue));
	CHECK(stats.GetMinValue() == doctest::Approx(minValue));
	CHECK(stats.GetMaxValue() == doctest::Approx(maxValue));
}

SCENARIO("The observer can receive notifications from different subjects.")
{
	GIVEN("the stats display and two subjects")
	{
		CStatsDisplay statistics;
		CWeatherData subject1{ "subject 1" };
		CWeatherData subject2{ "subject 2" };

		Registration r1{ subject1, statistics };
		Registration r2{ subject2, statistics };

		WHEN("the first subject sends notifications")
		{
			subject1.SetMeasurements(1, 2, 3);
			subject1.SetMeasurements(2, 3, 4);

			THEN("the stats for the first subject is updated")
			{
				auto stats = statistics.GetStatistics(NN_CHECK_ASSERT(&subject1));
				ValidateStats(stats.temperature, 1.5, 1, 2);
				ValidateStats(stats.humidity, 2.5, 2, 3);
				ValidateStats(stats.pressure, 3.5, 3, 4);
			}
			AND_THEN("the stats for the second subject does not change")
			{
				auto stats = statistics.GetStatistics(NN_CHECK_ASSERT(&subject2));
				CHECK(!stats.temperature.HasData());
				CHECK(!stats.humidity.HasData());
				CHECK(!stats.pressure.HasData());
			}
		}
		WHEN("the second subject sends notifications")
		{
			subject2.SetMeasurements(3, 4, 5);
			subject2.SetMeasurements(6, 7, 8);

			THEN("the stats for the second subject is updated")
			{
				auto stats = statistics.GetStatistics(NN_CHECK_ASSERT(&subject2));
				ValidateStats(stats.temperature, 4.5, 3, 6);
				ValidateStats(stats.humidity, 5.5, 4, 7);
				ValidateStats(stats.pressure, 6.5, 5, 8);
			}
			AND_THEN("the stats for the first subject does not change")
			{
				auto stats = statistics.GetStatistics(NN_CHECK_ASSERT(&subject1));
				CHECK(!stats.temperature.HasData());
				CHECK(!stats.humidity.HasData());
				CHECK(!stats.pressure.HasData());
			}
		}
	}
};
