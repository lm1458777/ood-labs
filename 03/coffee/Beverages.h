#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription() const override
	{
		return m_description;
	}

private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	static std::string GetName()
	{
		return "Coffee";
	}

	CCoffee(const std::string& description = GetName())
		: CBeverage(description)
	{
	}

	double GetCost() const override
	{
		return 60;
	}
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	static std::string GetName()
	{
		return "Cappuccino";
	}

	CCappuccino(const std::string& description = GetName())
		: CCoffee(description)
	{
	}

	double GetCost() const override
	{
		return 80;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	static std::string GetName()
	{
		return "Latte";
	}

	CLatte(const std::string& description = GetName())
		: CCoffee(description)
	{
	}

	double GetCost() const override
	{
		return 90;
	}
};

// Чай
class CTea : public CBeverage
{
public:
	static std::string GetName()
	{
		return "Tea";
	}

	CTea()
		: CBeverage(GetName())
	{
	}

	double GetCost() const override
	{
		return 30;
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	static std::string GetName()
	{
		return "Milkshake";
	}

	CMilkshake()
		: CBeverage(GetName())
	{
	}

	double GetCost() const override
	{
		return 80;
	}
};
