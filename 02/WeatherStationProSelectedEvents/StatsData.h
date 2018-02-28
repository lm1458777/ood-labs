#pragma once
#include <algorithm>

class StatsData
{
public:
	using Value = double;

	void Accumulate(Value newValue)
	{
		if (m_countAcc == std::numeric_limits<decltype(m_countAcc)>::max())
		{
			throw std::runtime_error("Too many data");
		}

		m_min = std::min(m_min, newValue);

		m_max = std::max(m_max, newValue);

		m_acc += newValue;
		++m_countAcc;
	}

	Value GetMinValue() const
	{
		return m_min;
	}

	Value GetMaxValue() const
	{
		return m_max;
	}

	Value GetAverageValue() const
	{
		return !HasData() ? 0 : (m_acc / m_countAcc);
	}

	bool HasData() const
	{
		return m_countAcc > 0;
	}

private:
	Value m_min = std::numeric_limits<double>::infinity();
	Value m_max = -std::numeric_limits<double>::infinity();
	Value m_acc = 0;
	unsigned m_countAcc = 0;
};
