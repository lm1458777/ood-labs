#pragma once
#include <limits>

double DegreesToRadians(double deg);
double RadiansToDegrees(double rad);

class Wind
{
public:
	using Speed = double;
	using Radians = double;
	using Degrees = double;

	Wind() = default;

	Wind(Speed spd, Radians dir);

	static Wind FromSpeedAndDegrees(Speed speed, Degrees direction)
	{
		return Wind{ speed, DegreesToRadians(direction) };
	}

	Speed GetSpeed() const
	{
		return m_speed;
	}

	Radians GetDirection() const
	{
		return m_direction;
	}

	Degrees GetDirectionInDegrees() const
	{
		return RadiansToDegrees(m_direction);
	}

private:
	Speed m_speed = 0;
	Radians m_direction = 0;
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
