#pragma once
#include "IBeverage.h"

class Sort : public IBeverage
{
public:
	Sort(IBeveragePtr beverage, std::string sort)
		: m_beverage(std::move(beverage))
		, m_sort(sort)
	{
		if (!m_beverage)
		{
			throw std::invalid_argument("The beverage must not be null");
		}
	}

	std::string GetDescription() const override
	{
		return m_sort + " " + m_beverage->GetDescription();
	}

	double GetCost() const override
	{
		return m_beverage->GetCost();
	}

private:
	IBeveragePtr m_beverage;
	std::string m_sort;
};
