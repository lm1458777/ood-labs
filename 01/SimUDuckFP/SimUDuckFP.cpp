#include <functional>
#include <iostream>

using namespace std;

using DanceBehavior = function<void()>;

const DanceBehavior WaltzDanceBehavior = []() {
	cout << "Dancing waltz" << endl;
};

const DanceBehavior MinuetDanceBehavior = []() {
	cout << "Dancing minuet" << endl;
};

const DanceBehavior NoDanceBehavior = []() {
	cout << "Men don't dance" << endl;
};

using FlyBehavior = function<int(int flyCounter)>;

const FlyBehavior FlyWithWings = [](int flyCounter) {
	++flyCounter;
	cout << "I'm flying with wings!! Flight number: " << flyCounter << endl;
	return flyCounter;
};

const FlyBehavior FlyWithRocketEngine = [](int flyCounter) {
	++flyCounter;
	cout << "I'm flying with rocket engine!! Flight number: " << flyCounter << endl;
	return flyCounter;
};

const FlyBehavior FlyNoWay = [](int flyCounter) {
	return flyCounter;
};

using QuackBehavior = function<void()>;

const QuackBehavior QuackQuackBehavior = []() {
	cout << "Quack Quack!!!" << endl;
};

const QuackBehavior SqueakBehavior = []() {
	cout << "Squeek!!!" << endl;
};

const QuackBehavior MuteQuackBehavior = []() {};

class Duck final
{
public:
	Duck(
		FlyBehavior flyBehavior,
		QuackBehavior quackBehavior,
		DanceBehavior danceBehavior,
		string displayString)
		: m_displayString{ move(displayString) }
		, m_flyBehavior{ move(flyBehavior) }
		, m_quackBehavior{ move(quackBehavior) }
		, m_danceBehavior{ move(danceBehavior) }
	{
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyCounter = m_flyBehavior(m_flyCounter);
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(FlyBehavior flyBehavior)
	{
		m_flyBehavior = move(flyBehavior);
	}
	void Display() const
	{
		cout << m_displayString.c_str() << endl;
	}

private:
	string m_displayString;
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
	int m_flyCounter = 0;
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
	Duck mallardDuck{ FlyWithWings, QuackQuackBehavior, WaltzDanceBehavior, "I'm mallard duck" };
	PlayWithDuck(mallardDuck);

	Duck redheadDuck{ FlyWithWings, QuackQuackBehavior, MinuetDanceBehavior, "I'm redhead duck" };
	PlayWithDuck(redheadDuck);

	Duck rubberDuck{ FlyNoWay, SqueakBehavior, NoDanceBehavior, "I'm rubber duck" };
	PlayWithDuck(rubberDuck);

	Duck deckoyDuck{ FlyNoWay, MuteQuackBehavior, NoDanceBehavior, "I'm decoy duck" };
	PlayWithDuck(deckoyDuck);

	Duck modelDuck{ FlyNoWay, QuackQuackBehavior, NoDanceBehavior, "I'm model duck" };
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyNoWay);
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithRocketEngine);
	PlayWithDuck(modelDuck);
}
