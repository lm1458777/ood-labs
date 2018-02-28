#pragma once
#include "Observer.h"

namespace weather_info_observer
{

struct ObserverRegistration
{
	using Observable = IWeatherInfoObservable;
	using Observer = IWeatherInfoObserver;

	ObserverRegistration(Observable& subject, Observer& observer, Parameters parameters)
		: m_subject(subject)
		, m_observer(observer)
		, m_parameters(parameters)
	{
		m_subject.RegisterObserver(observer, parameters);
	}

	~ObserverRegistration()
	{
		CancelRegistration();
	}

	void CancelRegistration()
	{
		if (m_observerRegistered)
		{
			m_subject.RemoveObserver(m_observer, m_parameters);
			m_observerRegistered = false;
		}
	}

private:
	ObserverRegistration(const ObserverRegistration&) = delete;
	ObserverRegistration& operator=(const ObserverRegistration&) = delete;

	Observable& m_subject;
	Observer& m_observer;
	bool m_observerRegistered = true;
	Parameters m_parameters;
};

} // namespace weather_info_observer
