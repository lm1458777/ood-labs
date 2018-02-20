#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

using Observer = observer::IObserver<SWeatherInfo>;
using Observable = observer::IObservable<SWeatherInfo>;
using ObservableNotNull = observer::not_null<Observable*>;

class CDisplay : public Observer
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(ObservableNotNull subject, SWeatherInfo const& data) override
	{
		std::cout
			<< "[" << subject->GetLocation().c_str() << "]"
			<< " Current:"
			<< " Temp = " << data.temperature
			<< "; Hum = " << data.humidity
			<< "; Pressure = " << data.pressure
			<< "." << std::endl;

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

class CStatsDisplay : public Observer
{
public:
	struct SubjectStats
	{
		StatsData temperature;
		StatsData humidity;
		StatsData pressure;
	};

	SubjectStats GetStatistics(ObservableNotNull subject) const
	{
		auto it = m_stats.find(subject);
		return it == m_stats.end() ? SubjectStats{} : it->second;
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(ObservableNotNull subject, SWeatherInfo const& data) override
	{
		auto& stats = m_stats[subject];

		Accumulate(stats, data);

		std::cout << "[" << subject->GetLocation().c_str() << "]" << std::endl;
		Display(std::cout, stats);
		std::cout << "----------------" << std::endl;
	}

private:
	static void Accumulate(SubjectStats& stats, const SWeatherInfo& newData)
	{
		stats.temperature.Accumulate(newData.temperature);
		stats.humidity.Accumulate(newData.humidity);
		stats.pressure.Accumulate(newData.pressure);
	}

	static void Display(std::ostream& out, const SubjectStats& stats)
	{
		DisplayParameter(out, "Temp    ", stats.temperature);
		DisplayParameter(out, "Humidity", stats.humidity);
		DisplayParameter(out, "Pressure", stats.pressure);
	}

	static void DisplayParameter(std::ostream& out, const char* name, const StatsData& data)
	{
		out << name << ": "
			<< "Average = " << data.GetAverageValue()
			<< "; Min = " << data.GetMinValue()
			<< "; Max = " << data.GetMaxValue()
			<< "." << std::endl;
	}

	std::unordered_map<ObservableNotNull, SubjectStats> m_stats;
};

class CWeatherData : public observer::CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string location)
		: m_location{ std::move(location) }
	{
	}

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

	std::string GetLocation() const override
	{
		return m_location;
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

	std::string m_location;
};
