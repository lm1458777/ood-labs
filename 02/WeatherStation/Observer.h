﻿#pragma once

#include <functional>
#include <set>

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
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer) override
	{
		m_observers.insert(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observers = m_observers;
		for (auto& observer : observers)
		{
			observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(&observer);
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::set<ObserverType*> m_observers;
};

template <typename T>
struct ObserverRegistration
{
	using Observable = IObservable<T>;
	using Observer = IObserver<T>;

	ObserverRegistration(Observable& subject, Observer& observer)
		: m_subject(subject)
		, m_observer(observer)
	{
		m_subject.RegisterObserver(observer);
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
