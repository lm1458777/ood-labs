#pragma once

#include "SWeatherInfo.h"

namespace weather_info_observer
{

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
class IWeatherInfoObserver
{
public:
	virtual void Update(SWeatherInfo const& data, Parameters parameters) = 0;
	virtual ~IWeatherInfoObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
class IWeatherInfoObservable
{
public:
	virtual ~IWeatherInfoObservable() = default;
	virtual void RegisterObserver(IWeatherInfoObserver& observer, Parameters parameters) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IWeatherInfoObserver& observer, Parameters parameters) = 0;
};

} // namespace weather_info_observer
