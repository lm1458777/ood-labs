#pragma once

#include <algorithm>
#include <vector>

namespace observer_with_priority
{

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	using Priority = int;

	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, Priority priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer, Priority priority) override
	{
		bool alreadyRegistered = std::any_of(m_observers.begin(), m_observers.end(), ObserverEqualTo(&observer));
		if (alreadyRegistered)
		{
			throw std::logic_error("An observer must be registered only once");
		}

		m_observers.emplace_back(&observer, priority);
		m_sorted = false;
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observers = GetObserversSortedByPriority();
		for (auto& observer : observers)
		{
			observer.first->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto it = std::find_if(m_observers.begin(), m_observers.end(), ObserverEqualTo(&observer));
		m_observers.erase(it);
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	auto GetObserversSortedByPriority()
	{
		if (!m_sorted)
		{
			sort(m_observers.begin(), m_observers.end(), [](auto p1, auto p2) {
				return p1.second > p2.second;
			});

			m_sorted = true;
		}

		return m_observers;
	}

	static auto ObserverEqualTo(ObserverType* observer)
	{
		return [observer](auto p) {
			return p.first == observer;
		};
	}

	using ObserverWithPriority = std::pair<ObserverType*, Priority>;

	std::vector<ObserverWithPriority> m_observers;
	bool m_sorted = true;
};

template <typename T>
struct ObserverRegistration
{
	using Observable = IObservable<T>;
	using Observer = IObserver<T>;

	ObserverRegistration(Observable& subject, Observer& observer, typename Observable::Priority priority)
		: m_subject(subject)
		, m_observer(observer)
	{
		m_subject.RegisterObserver(observer, priority);
	}

	~ObserverRegistration()
	{
		CancelRegistration();
	}

	void CancelRegistration()
	{
		if (m_observerRegistered)
		{
			m_subject.RemoveObserver(m_observer);
			m_observerRegistered = false;
		}
	}

private:
	ObserverRegistration(const ObserverRegistration&) = delete;
	ObserverRegistration& operator=(const ObserverRegistration&) = delete;

	Observable& m_subject;
	Observer& m_observer;
	bool m_observerRegistered = true;
};

} // namespace observer_with_priority
