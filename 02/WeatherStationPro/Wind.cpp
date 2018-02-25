#include "Wind.h"
#include <algorithm>
#include <stdexcept>

#define _USE_MATH_DEFINES
#include <math.h>

namespace
{

double NormalizeAngle(double angle, double maxAngle)
{
	angle = fmod(angle, maxAngle);
	return (angle < 0) ? maxAngle + angle : angle;
}

bool NearlyEqual(double a, double b)
{
	return std::abs(a - b) <= 0.0001;
}

bool NearlyEqualZero(double d)
{
	return NearlyEqual(d, 0);
}

} // namespace

double NormalizeRadians(double rad)
{
	return NormalizeAngle(rad, 2 * M_PI);
}

double DegreesToRadians(double deg)
{
	return NormalizeAngle(deg, 360) * M_PI / 180.0;
}

double RadiansToDegrees(double rad)
{
	return NormalizeRadians(rad) * 180 / M_PI;
}

Wind operator+(Wind a, Wind b)
{
	auto aX = a.speed * cos(a.direction);
	auto aY = a.speed * sin(a.direction);

	auto bX = b.speed * cos(b.direction);
	auto bY = b.speed * sin(b.direction);

	auto cX = aX + bX;
	auto cY = aY + bY;
	if (NearlyEqualZero(cX) && NearlyEqualZero(cY))
	{
		return Wind{};
	}

	auto len = sqrt(cX * cX + cY * cY);

	if (NearlyEqualZero(cX))
	{
		return Wind{ abs(cY), cY < 0 ? (M_PI + M_PI_2) : M_PI_2 };
	}

	if (NearlyEqualZero(cY))
	{
		return Wind{ abs(cX), cX < 0 ? M_PI : 0 };
	}

	return Wind{ len, NormalizeRadians(atan2(cY, cX)) };
}

void WindStatsData::Accumulate(Wind newValue)
{
	if (m_countAcc == std::numeric_limits<decltype(m_countAcc)>::max())
	{
		throw std::runtime_error("Too many data");
	}

	m_min = std::min(m_min, newValue.speed);

	m_max = std::max(m_max, newValue.speed);

	m_acc = m_acc + newValue;
	++m_countAcc;
}

Wind::Speed WindStatsData::GetMinSpeed() const
{
	return m_min;
}

Wind::Speed WindStatsData::GetMaxSpeed() const
{
	return m_max;
}

Wind WindStatsData::GetAverageWind() const
{
	return !HasData()
		? Wind{}
		: Wind{ m_acc.speed / m_countAcc, m_acc.direction };
}

bool WindStatsData::HasData() const
{
	return m_countAcc > 0;
}
