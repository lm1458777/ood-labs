#include "nn.hpp"
#include <iostream>
#include <memory>

using namespace std;
using namespace dropbox::oxygen;

struct IDanceBehavior
{
	virtual ~IDanceBehavior() = default;
	virtual void Dance() = 0;
};

class WaltzDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Dancing waltz" << endl;
	}
};

class MinuetDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Dancing minuet" << endl;
	}
};

class NoDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Men don't dance" << endl;
	}
};

struct IFlyBehavior
{
	virtual ~IFlyBehavior() = default;
	virtual int Fly(int flyCounter) = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	int Fly(int flyCounter) override
	{
		++flyCounter;
		cout << "I'm flying with wings!! Flight number: " << flyCounter << endl;
		return flyCounter;
	}
};

class FlyWithRocketEngine : public IFlyBehavior
{
public:
	int Fly(int flyCounter) override
	{
		++flyCounter;
		cout << "I'm flying with rocket engine!! Flight number: " << flyCounter << endl;
		return flyCounter;
	}
};

class FlyNoWay : public IFlyBehavior
{
public:
	int Fly(int flyCounter) override
	{
		return flyCounter;
	}
};

struct IQuackBehavior
{
	virtual ~IQuackBehavior() = default;
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};

class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeek!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior>&& flyBehavior,
		unique_ptr<IQuackBehavior>&& quackBehavior,
		unique_ptr<IDanceBehavior>&& danceBehavior)
		: m_quackBehavior{ NN_CHECK_THROW(move(quackBehavior)) }
		, m_danceBehavior{ NN_CHECK_THROW(move(danceBehavior)) }
		, m_flyBehavior{ NN_CHECK_THROW(move(flyBehavior)) }
	{
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyCounter = m_flyBehavior->Fly(m_flyCounter);
	}
	void Dance()
	{
		m_danceBehavior->Dance();
	}
	void SetFlyBehavior(unique_ptr<IFlyBehavior> flyBehavior)
	{
		m_flyBehavior = NN_CHECK_THROW(move(flyBehavior));
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	nn_unique_ptr<IFlyBehavior> m_flyBehavior;
	nn_unique_ptr<IQuackBehavior> m_quackBehavior;
	nn_unique_ptr<IDanceBehavior> m_danceBehavior;
	int m_flyCounter = 0;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(make_unique<FlyWithWings>(),
			  make_unique<QuackBehavior>(),
			  make_unique<WaltzDanceBehavior>())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(make_unique<FlyWithWings>(),
			  make_unique<QuackBehavior>(),
			  make_unique<MinuetDanceBehavior>())
	{
	}

	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(make_unique<FlyNoWay>(),
			  make_unique<MuteQuackBehavior>(),
			  make_unique<NoDanceBehavior>())
	{
	}

	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(),
			  make_unique<SqueakBehavior>(),
			  make_unique<NoDanceBehavior>())
	{
	}

	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(),
			  make_unique<QuackBehavior>(),
			  make_unique<NoDanceBehavior>())
	{
	}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(make_unique<FlyWithWings>());
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(make_unique<FlyNoWay>());
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(make_unique<FlyWithRocketEngine>());
	PlayWithDuck(modelDuck);
}
