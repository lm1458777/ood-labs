#include "stdafx.h"
#include "../WeatherStationPro/Wind.h"

#define _USE_MATH_DEFINES
#include <math.h>

using doctest::Approx;

static void ExpectEqual(Wind a, Wind b)
{
	CHECK(a.speed == Approx(b.speed));
	CHECK(a.direction == Approx(b.direction));
}

TEST_CASE("the function DegreesToRadians returns normalized value in radians")
{
	CHECK(DegreesToRadians(360 + 45) == Approx(M_PI_4));
	CHECK(DegreesToRadians(-135) == Approx(M_PI + M_PI_4));
	CHECK(DegreesToRadians(0) == Approx(0));
	CHECK(DegreesToRadians(180) == Approx(M_PI));
	CHECK(DegreesToRadians(-270) == Approx(M_PI_2));
};

TEST_CASE("the function RadiansToDegrees returns normalized value in degrees")
{
	CHECK(RadiansToDegrees(-M_PI) == Approx(180));
	CHECK(RadiansToDegrees(-3 * M_PI_4) == Approx(225));
	CHECK(RadiansToDegrees(M_PI_2) == Approx(90));
};

TEST_CASE("the operator+ summarizes wind data and returns normalized direction")
{
	ExpectEqual(Wind{ 1, 0 } + Wind{ 2, 0 }, Wind{ 3, 0 });
	ExpectEqual(Wind{ 1, 0 } + Wind{ 1, -M_PI }, Wind{ 0, 0 });
	ExpectEqual(Wind{ 1, -M_PI_2 } + Wind{ 1, -M_PI }, Wind{ M_SQRT2, M_PI + M_PI_4 });
	ExpectEqual(Wind{ 10, -M_PI_4 } + Wind{ 10, M_PI_4 }, Wind{ 10 * M_SQRT2, 0 });
	ExpectEqual(Wind{ 10, 0 } + Wind{ 6, -M_PI }, Wind{ 4, 0 });
};

SCENARIO("The WindStatsData accumulates wind data")
{
	GIVEN("the WindStatsData")
	{
		WindStatsData stats;

		WHEN("created")
		{
			THEN("has no data")
			{
				CHECK(!stats.HasData());
			}
		}

		WHEN("the first measurement is added")
		{
			Wind measurement{ 10, -M_PI_4 };
			stats.Accumulate(measurement);

			THEN("has data")
			{
				CHECK(stats.HasData());
			}
			THEN("the min speed is equal to measurement speed")
			{
				CHECK(stats.GetMinSpeed() == Approx(10));
			}
			THEN("the max speed is equal to measurement speed")
			{
				CHECK(stats.GetMaxSpeed() == Approx(10));
			}
			THEN("the average wind is equal to normalized measurement")
			{
				ExpectEqual(
					stats.GetAverageWind(),
					Wind{ measurement.speed, NormalizeRadians(measurement.direction) });
			}
		}

		WHEN("some measurements are added")
		{
			stats.Accumulate(Wind{ 10, -M_PI_4 });
			stats.Accumulate(Wind{ 10, M_PI_4 });
			stats.Accumulate(Wind{ 5, -M_PI });

			THEN("the min speed is updated")
			{
				CHECK(stats.GetMinSpeed() == Approx(5));
			}
			THEN("the max speed is updated")
			{
				CHECK(stats.GetMaxSpeed() == Approx(10));
			}
			THEN("the max speed is updated")
			{
				auto averageSpeed = (10.0 * M_SQRT2 - 5) / 3;
				ExpectEqual(
					stats.GetAverageWind(),
					Wind(averageSpeed, 0));
			}
		}
	}
}
