#pragma once
#include "CObservable.h"
#include "Observer.h"
#include "SWeatherInfo.h"
#include "StatsData.h"
#include "Wind.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class CDisplay : public weather_info_observer::IWeatherInfoObserver
{
public:
	CDisplay(std::string name)
		: m_name{ std::move(name) }
	{
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, Parameters changes) override
	{
		std::cout << m_name.c_str() << std::endl;

		if (IsAnyFlagSet(changes, Parameters::Temperature))
		{
			std::cout << "Current Temp " << data.temperature << std::endl;
		}

		if (IsAnyFlagSet(changes, Parameters::Humidity))
		{
			std::cout << "Current Hum " << data.humidity << std::endl;
		}

		if (IsAnyFlagSet(changes, Parameters::Pressure))
		{
			std::cout << "Current Pressure " << data.pressure << std::endl;
		}

		if (IsAnyFlagSet(changes, Parameters::Wind))
		{
			std::cout << "Current Wind: speed =  " << data.wind.GetSpeed()
					  << ", direction = " << data.wind.GetDirectionInDegrees() << "deg" << std::endl;
		}

		std::cout << "----------------" << std::endl;
	}

private:
	std::string m_name;
};

class CStatsDisplay : public weather_info_observer::IWeatherInfoObserver
{
public:
	CStatsDisplay(std::string name)
		: m_name{ std::move(name) }
	{
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, Parameters changes) override
	{
		std::cout << m_name.c_str() << std::endl;

		if (IsAnyFlagSet(changes, Parameters::Temperature))
		{
			m_temperature.Accumulate(data.temperature);
			Display(std::cout, "Temp    ", m_temperature);
		}

		if (IsAnyFlagSet(changes, Parameters::Humidity))
		{
			m_humidity.Accumulate(data.humidity);
			Display(std::cout, "Humidity", m_humidity);
		}

		if (IsAnyFlagSet(changes, Parameters::Pressure))
		{
			m_pressure.Accumulate(data.pressure);
			Display(std::cout, "Pressure", m_pressure);
		}

		if (IsAnyFlagSet(changes, Parameters::Wind))
		{
			m_wind.Accumulate(data.wind);
			DisplayWind(std::cout, m_wind);
		}

		std::cout << "----------------" << std::endl;
	}

	static void Display(std::ostream& out, const char* name, const StatsData& data)
	{
		out << name << ": "
			<< "Average = " << data.GetAverageValue()
			<< "; Min = " << data.GetMinValue()
			<< "; Max = " << data.GetMaxValue()
			<< "." << std::endl;
	}

	static void DisplayWind(std::ostream& out, const WindStatsData& data)
	{
		const auto averageWind = data.GetAverageWind();
		out << "Wind    "
			<< ": "
			<< "Average = (speed: " << averageWind.GetSpeed()
			<< ", direction: " << averageWind.GetDirectionInDegrees() << "deg)"
			<< "; Min speed = " << data.GetMinSpeed()
			<< "; Max speed = " << data.GetMaxSpeed()
			<< "." << std::endl;
	}

	StatsData m_temperature;
	StatsData m_humidity;
	StatsData m_pressure;
	WindStatsData m_wind;

	std::string m_name;
};

class CWeatherData : public weather_info_observer::CObservable
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	Wind GetWind() const
	{
		return m_wind;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, Wind wind)
	{
		m_lastChanges = Parameters::None;

		UpdateValue(m_humidity, humidity, Parameters::Humidity);
		UpdateValue(m_temperature, temp, Parameters::Temperature);
		UpdateValue(m_pressure, pressure, Parameters::Pressure);

		if (m_wind != wind)
		{
			m_wind = wind;
			m_lastChanges |= Parameters::Wind;
		}

		MeasurementsChanged();
	}

protected:
	std::pair<SWeatherInfo, Parameters> GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.wind = GetWind();

		return make_pair(info, m_lastChanges);
	}

private:
	void UpdateValue(double& current, double newValue, Parameters parameter)
	{
		if (current != newValue)
		{
			current = newValue;
			m_lastChanges |= parameter;
		}
	}

	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 0.0;
	Wind m_wind;

	Parameters m_lastChanges = Parameters::None;
};
