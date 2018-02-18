#include "stdafx.h"
#include "../WeatherStation/ObserverWithPriority.h"

using dropbox::oxygen::nn;
using namespace observer_with_priority;

namespace
{

using Observer = IObserver<int>;
using Observable = CObservable<int>;
using Registration = ObserverRegistration<int>;
using ObserverVector = std::vector<nn<Observer*>>;

struct MockObserver : Observer
{
	explicit MockObserver(Observable& subject, Observable::Priority priority, ObserverVector& updateOrder)
		: m_reg(subject, *this, priority)
		, m_updateOrder(updateOrder)
	{
	}

	void Update(int const& /*data*/) override
	{
		m_updateOrder.push_back(NN_CHECK_ASSERT(this));
	}

private:
	Registration m_reg;

	ObserverVector& m_updateOrder;
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

SCENARIO("The observer with higher priority is notified before the observer with lower priority")
{
	GIVEN("A subject with some observers")
	{
		ObserverVector updateOrder;

		TestObservable subject;

		MockObserver obs1{ subject, 3, updateOrder };
		MockObserver obs2{ subject, 1, updateOrder };
		MockObserver obs3{ subject, 2, updateOrder };

		WHEN("the subject notifies observers")
		{
			subject.NotifyObservers();

			THEN("observers are notified in their priority order")
			{
				ObserverVector expectedOrder{
					NN_CHECK_ASSERT(&obs1),
					NN_CHECK_ASSERT(&obs3),
					NN_CHECK_ASSERT(&obs2),
				};

				CHECK(updateOrder == expectedOrder);
			}
		}
	}
}
