#pragma once
#include "Wind.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	Wind wind;
};

enum class Parameters
{
	None = 0,

	Temperature = (1u << 0),
	Humidity = (1u << 1),
	Pressure = (1u << 2),
	Wind = (1u << 3),

	All = Temperature | Humidity | Pressure | Wind,
};

inline Parameters operator|(Parameters a, Parameters b)
{
	return static_cast<Parameters>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
}

inline Parameters operator|=(Parameters& a, Parameters b)
{
	a = a | b;
	return a;
}

inline Parameters operator&(Parameters a, Parameters b)
{
	return static_cast<Parameters>(static_cast<unsigned>(a) & static_cast<unsigned>(b));
}

inline Parameters operator&=(Parameters& a, Parameters b)
{
	a = a & b;
	return a;
}

inline Parameters operator~(Parameters a)
{
	return static_cast<Parameters>(~static_cast<unsigned>(a));
}

inline bool IsAnyFlagSet(Parameters value, Parameters flags)
{
	return Parameters::None != (value & flags);
}
