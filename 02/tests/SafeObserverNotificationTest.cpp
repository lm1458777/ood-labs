#include "stdafx.h"
#include "../WeatherStation/Observer.h"

using namespace observer;

namespace
{

using Observer = IObserver<int>;
using Observable = CObservable<int>;
using Registration = ObserverRegistration<int>;

struct MockObserver : Observer
{
	int newData = 0;

	explicit MockObserver(Observable& subject, bool removeRegistrationOnUpdate = false)
		: m_reg(subject, *this)
		, m_removeRegistrationOnUpdate(removeRegistrationOnUpdate)
	{
	}

	void Update(int const& data) override
	{
		newData = data;

		if (m_removeRegistrationOnUpdate)
		{
			m_reg.CancelRegistration();
		}
	}

private:
	Registration m_reg;
	bool m_removeRegistrationOnUpdate = false;
};

class TestObservable : public Observable
{
public:
	int changedData = 0;

protected:
	int GetChangedData() const override
	{
		return changedData;
	}
};

} // namespace

SCENARIO("The observer can be deleted during the notification")
{
	GIVEN("A subject with some observers")
	{
		TestObservable subject;

		MockObserver obs1{ subject };
		MockObserver obs2{ subject, true };
		MockObserver obs3{ subject };

		WHEN("the subject notifies observers")
		{
			subject.changedData = 42;
			subject.NotifyObservers();

			THEN("all observers are notified")
			{
				CHECK_EQ(obs1.newData, 42);
				CHECK_EQ(obs2.newData, 42);
				CHECK_EQ(obs3.newData, 42);

				AND_THEN("one observer is removed and does not receive notifications anymore")
				{
					subject.changedData = 43;
					subject.NotifyObservers();

					CHECK_EQ(obs1.newData, 43);
					CHECK_EQ(obs3.newData, 43);

					CHECK_EQ(obs2.newData, 42);
				}
			}
		}
	}
}
