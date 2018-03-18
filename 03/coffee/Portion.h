#pragma once
#include "IBeverage.h"

class Portion final : public IBeverage
{
public:
	Portion(IBeveragePtr beverage, std::string portion, double price)
		: m_beverage(std::move(beverage))
		, m_portion(std::move(portion))
		, m_price(price)
	{
		if (!m_beverage)
		{
			throw std::invalid_argument("The beverage must not be null");
		}
	}

	std::string GetDescription() const override
	{
		return m_portion + " " + m_beverage->GetDescription();
	}

	double GetCost() const override
	{
		return m_price;
	}

private:
	IBeveragePtr m_beverage;
	std::string m_portion;
	double m_price = 0;
};
