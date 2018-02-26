#pragma once
#include "Observer.h"
#include "StatsData.h"
#include "Wind.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	Wind wind;
};

class CDisplay : public observer::IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind: speed =  " << data.wind.GetSpeed()
			<< ", direction = " << data.wind.GetDirectionInDegrees() << "deg" << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public observer::IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperature.Accumulate(data.temperature);
		m_humidity.Accumulate(data.humidity);
		m_pressure.Accumulate(data.pressure);
		m_wind.Accumulate(data.wind);

		Display(std::cout, "Temp    ", m_temperature);
		Display(std::cout, "Humidity", m_humidity);
		Display(std::cout, "Pressure", m_pressure);
		DisplayWind(std::cout, m_wind);
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
		out << "Wind    " << ": "
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
};

class CWeatherData : public observer::CObservable<SWeatherInfo>
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
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_wind = wind;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.wind = GetWind();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	Wind m_wind;
};
