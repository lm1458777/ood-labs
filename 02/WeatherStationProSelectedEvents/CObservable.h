#pragma once
#include "Observer.h"
#include <nn.hpp>
#include <unordered_map>

namespace weather_info_observer
{

// Реализация интерфейса IObservable
class CObservable : public IWeatherInfoObservable
{
public:
	void RegisterObserver(IWeatherInfoObserver& observer, Parameters parameters) override
	{
		if (parameters == Parameters::None)
		{
			return;
		}

		auto observerPtr = NN_CHECK_ASSERT(&observer);
		auto it = m_observers.find(observerPtr);
		if (it == m_observers.end())
		{
			m_observers.emplace(observerPtr, parameters);
		}
		else
		{
			it->second |= parameters;
		}
	}

	void NotifyObservers() override
	{
		SWeatherInfo data;
		auto changedParameters = Parameters::None;
		std::tie(data, changedParameters) = GetChangedData();

		std::vector<std::pair<nn<IWeatherInfoObserver*>, Parameters>> observers;
		for (auto observerAndParameters : m_observers)
		{
			auto changes = observerAndParameters.second & changedParameters;
			if (Parameters::None != changes)
			{
				observers.emplace_back(observerAndParameters.first, changes);
			}
		}

		for (auto p : observers)
		{
			p.first->Update(data, p.second);
		}
	}

	void RemoveObserver(IWeatherInfoObserver& observer, Parameters parameters) override
	{
		auto observerPtr = NN_CHECK_ASSERT(&observer);
		auto it = m_observers.find(observerPtr);
		if (it != m_observers.end())
		{
			it->second &= ~parameters;
			if (Parameters::None == it->second)
			{
				m_observers.erase(it);
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual std::pair<SWeatherInfo, Parameters> GetChangedData() const = 0;

private:
	template <class T>
	using nn = dropbox::oxygen::nn<T>;

	std::unordered_map<nn<IWeatherInfoObserver*>, Parameters> m_observers;
};

} // namespace weather_info_observer
