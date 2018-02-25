#pragma once
#include <limits>

double NormalizeRadians(double rad);

double DegreesToRadians(double deg);
double RadiansToDegrees(double rad);

struct Wind
{
	using Speed = double;
	using Radians = double;

	Speed speed = 0;
	Radians direction = 0;

	Wind() = default;

	Wind(Speed spd, Radians dir)
		: speed(spd)
		, direction(dir)
	{
	}
};

Wind operator+(Wind a, Wind b);

class WindStatsData
{
public:
	void Accumulate(Wind newValue);

	Wind::Speed GetMinSpeed() const;
	Wind::Speed GetMaxSpeed() const;

	bool HasData() const;
	Wind GetAverageWind() const;

private:
	Wind::Speed m_min = std::numeric_limits<Wind::Speed>::infinity();
	Wind::Speed m_max = -std::numeric_limits<Wind::Speed>::infinity();
	Wind m_acc;
	unsigned m_countAcc = 0;
};
