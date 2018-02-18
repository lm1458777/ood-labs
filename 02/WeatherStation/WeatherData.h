#pragma once
#include "Observer.h"
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
};

class CDisplay : public IObserver<SWeatherInfo>
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
		std::cout << "----------------" << std::endl;
	}
};

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

class CStatsDisplay : public IObserver<SWeatherInfo>
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

		Display(std::cout, "Temp    ", m_temperature);
		Display(std::cout, "Humidity", m_humidity);
		Display(std::cout, "Pressure", m_pressure);
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

	StatsData m_temperature;
	StatsData m_humidity;
	StatsData m_pressure;
};

class CWeatherData : public CObservable<SWeatherInfo>
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
