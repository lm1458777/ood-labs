﻿#include "Beverages.h"
#include "Condiments.h"
#include "Portion.h"
#include "Sort.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity)
		: m_quantity(quantity)
	{
	}

	auto operator()(IBeveragePtr&& beverage) const
	{
		return make_unique<CLemon>(move(beverage), m_quantity);
	}

private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr&&)> MakeCinnamon()
{
	return [](IBeveragePtr&& b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона: 
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&... args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto&& b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
					<< MakeCondimentA(d, e, f)
					<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
	auto beverage = 
		make_unique<CConcreteBeverage>(a, b, c)
		<< MakeCondimentA(d, e, f)
		<< MakeCondimentB(g, h);
или даже так:
	auto beverage = 
		make_unique<CConcreteBeverage>
		<< MakeCondiment<CondimentA>(d, e, f)
		<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
	auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
	auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
	auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
	auto beverage = make_unique<CCondimentB>(
						make_unique<CCondimentA>(
							make_unique<CConcreteBeverage>(a, b, c), // Напиток
							d, e, f	// доп. параметы CondimentA
						),
						g, h		// доп. параметры CondimentB
					);

unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(forward<Component>(component));
}

void PrintMenuItem(int choice, const string& name)
{
	cout << "[" << choice << "] - " << name.c_str() << "\n";
}

constexpr auto ChoiceQuit = -1;
constexpr auto ChoiceCheckout = 0;

enum class BeverageChoice
{
	Coffee = 1,
	Latte,
	DoubleLatte,
	Cappuccino,
	DoubleCappuccino,
	BlackTea,
	GreenTea,
	RedTea,
	ChifirTea,
	SmallMilkshake,
	MiddleMilkshake,
	BigMilkshake,
};

IBeveragePtr CreateBeverage(BeverageChoice beverageChoice)
{
	switch (beverageChoice)
	{
	case BeverageChoice::Coffee:
		return make_unique<CCoffee>();

	case BeverageChoice::Latte:
		return make_unique<CLatte>();

	case BeverageChoice::DoubleLatte:
		return make_unique<Portion>(make_unique<CLatte>(), "Double", 130.0);

	case BeverageChoice::Cappuccino:
		return make_unique<CCappuccino>();

	case BeverageChoice::DoubleCappuccino:
		return make_unique<Portion>(make_unique<CCappuccino>(), "Double", 120.0);

	case BeverageChoice::BlackTea:
		return make_unique<Sort>(make_unique<CTea>(), "Black");

	case BeverageChoice::GreenTea:
		return make_unique<Sort>(make_unique<CTea>(), "Green");

	case BeverageChoice::RedTea:
		return make_unique<Sort>(make_unique<CTea>(), "Red");

	case BeverageChoice::ChifirTea:
		return make_unique<Sort>(make_unique<CTea>(), "Chifir");

	case BeverageChoice::SmallMilkshake:
		return make_unique<Portion>(make_unique<CMilkshake>(), "Small", 50.0);

	case BeverageChoice::MiddleMilkshake:
		return make_unique<Portion>(make_unique<CMilkshake>(), "Middle", 60.0);

	case BeverageChoice::BigMilkshake:
		return make_unique<Portion>(make_unique<CMilkshake>(), "Big", 80.0);
	}

	return nullptr;
}

void PrintBeverageMenuItem(BeverageChoice choice, const string& name)
{
	PrintMenuItem(static_cast<int>(choice), name);
}

BeverageChoice SelectBeverage()
{
	cout << "Select beverage:\n";
	PrintBeverageMenuItem(BeverageChoice::Coffee, CCoffee::GetName());
	PrintBeverageMenuItem(BeverageChoice::Latte, CLatte::GetName());
	PrintBeverageMenuItem(BeverageChoice::DoubleLatte, "Double " + CLatte::GetName());
	PrintBeverageMenuItem(BeverageChoice::Cappuccino, CCappuccino::GetName());
	PrintBeverageMenuItem(BeverageChoice::DoubleCappuccino, "Double " + CCappuccino::GetName());
	PrintBeverageMenuItem(BeverageChoice::BlackTea, "Black " + CTea::GetName());
	PrintBeverageMenuItem(BeverageChoice::GreenTea, "Green " + CTea::GetName());
	PrintBeverageMenuItem(BeverageChoice::RedTea, "Red " + CTea::GetName());
	PrintBeverageMenuItem(BeverageChoice::ChifirTea, "Chifir " + CTea::GetName());
	PrintBeverageMenuItem(BeverageChoice::SmallMilkshake, "Small " + CMilkshake::GetName());
	PrintBeverageMenuItem(BeverageChoice::MiddleMilkshake, "Middle " + CMilkshake::GetName());
	PrintBeverageMenuItem(BeverageChoice::BigMilkshake, "Big " + CMilkshake::GetName());

	int beverageChoice = 0;
	cin >> beverageChoice;

	return static_cast<BeverageChoice>(beverageChoice);
}

enum class CondimentChoice
{
	Lemon = 1,
	Cinnamon,
	Cream,
	Chocolate,
	Liquor,
};

void PrintCondimentMenuItem(CondimentChoice choice, const string& name)
{
	PrintMenuItem(static_cast<int>(choice), name);
}

CondimentChoice SelectCondiment()
{
	cout << "Select beverage:\n";
	PrintCondimentMenuItem(CondimentChoice::Lemon, "Lemon");
	PrintCondimentMenuItem(CondimentChoice::Cinnamon, "Cinnamon");
	PrintCondimentMenuItem(CondimentChoice::Cream, "Cream");
	PrintCondimentMenuItem(CondimentChoice::Chocolate, "Chocolate");
	PrintCondimentMenuItem(CondimentChoice::Liquor, "Liquor");
	PrintCondimentMenuItem(static_cast<CondimentChoice>(ChoiceCheckout), "Checkout");

	auto condimentChoice = ChoiceQuit;
	cin >> condimentChoice;

	return static_cast<CondimentChoice>(condimentChoice);
}

LiquorType SelectLiquorType()
{
	cout << "Select liquor:\n";
	PrintMenuItem(static_cast<int>(LiquorType::Nut), "Nut");
	PrintMenuItem(static_cast<int>(LiquorType::Chocolate), "Chocolate");

	auto liquorChoice = ChoiceQuit;
	cin >> liquorChoice;

	return static_cast<LiquorType>(liquorChoice);
}

int SelectChocolateQuantity()
{
	cout << "Select chocolate quantity [1..5]:\n";
	auto quantity = ChoiceQuit;
	cin >> quantity;
	return quantity > 0 ? std::min(quantity, 5) : quantity;
}

IBeveragePtr AddCondiment(IBeveragePtr beverage)
{
	auto condimentChoice = static_cast<CondimentChoice>(ChoiceQuit);
	for (;;)
	{
		cout << "\n";
		condimentChoice = SelectCondiment();

		if (static_cast<int>(condimentChoice) == ChoiceCheckout)
		{
			return beverage;
		}

		if (condimentChoice == CondimentChoice::Lemon)
		{
			beverage = move(beverage) << MakeCondiment<CLemon>(2);
		}
		else if (condimentChoice == CondimentChoice::Cinnamon)
		{
			beverage = move(beverage) << MakeCondiment<CCinnamon>();
		}
		else if (condimentChoice == CondimentChoice::Cream)
		{
			beverage = move(beverage) << MakeCondiment<Cream>();
		}
		else if (condimentChoice == CondimentChoice::Chocolate)
		{
			auto quantity = SelectChocolateQuantity();
			if (quantity == ChoiceCheckout)
			{
				return beverage;
			}
			if (quantity == ChoiceQuit)
			{
				return nullptr;
			}
			beverage = move(beverage) << MakeCondiment<Chocolate>(quantity);
		}
		else if (condimentChoice == CondimentChoice::Liquor)
		{
			auto liquorType = SelectLiquorType();
			if (static_cast<int>(liquorType) == ChoiceCheckout)
			{
				return beverage;
			}
			if (static_cast<int>(liquorType) == ChoiceQuit)
			{
				return nullptr;
			}
			beverage = move(beverage) << MakeCondiment<Liquor>(liquorType);
		}
		else
		{
			return nullptr;
		}
	}
}

void DialogWithUser()
{
	auto beverage = CreateBeverage(SelectBeverage());
	if (beverage)
	{
		beverage = AddCondiment(move(beverage));
		if (beverage)
		{
			cout << "\n";
			cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
		}
	}
}

int main()
{
	{
		// Наливаем чашечку латте
		auto latte = make_unique<CLatte>();
		// добавляем корицы
		auto cinnamon = make_unique<CCinnamon>(move(latte));
		// добавляем пару долек лимона
		auto lemon = make_unique<CLemon>(move(cinnamon), 2);
		// добавляем пару кубиков льда
		auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
		// добавляем 2 грамма шоколадной крошки
		auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = make_unique<CChocolateCrumbs>( // Внешний слой: шоколадная крошка
			make_unique<CIceCubes>( // | под нею - кубики льда
				make_unique<CLemon>( // | | еще ниже лимон
					make_unique<CCinnamon>( // | | | слоем ниже - корица
						make_unique<CLatte>()), // | | |   в самом сердце - Латте
					2), // | | 2 дольки лимона
				2, IceCubeType::Dry), // | 2 кубика сухого льда
			2); // 2 грамма шоколадной крошки

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	// Подробнее рассмотрим работу MakeCondiment и оператора <<
	{
		// lemon - функция, добавляющая "2 дольки лимона" к любому напитку
		auto lemon2 = MakeCondiment<CLemon>(2);
		// iceCubes - функция, добавляющая "3 кусочка льда" к любому напитку
		auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);

		auto tea = make_unique<CTea>();

		// декорируем чай двумя дольками лимона и тремя кусочками льда
		auto lemonIceTea = iceCubes3(lemon2(move(tea)));
		/* Предыдущая строка выполняет те же действия, что и следующий код:
		auto lemonIceTea = 
			make_unique<CIceCubes>(
				make_unique<CLemon>(
					move(tea), 
					2), 
				2, IceCubeType::Water);
		*/

		auto oneMoreLemonIceTea = make_unique<CTea>() // Берем чай
			<< MakeCondiment<CLemon>(2) // добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(3, IceCubeType::Water); // и 3 кубика льда
		/*
		Предыдущая конструкция делает то же самое, что и следующая:
		auto oneMoreLemonIceTea =
			MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
				MakeCondiment<CLemon>(2)(make_unique<CTea>())
				);
		*/
	}

	// Аналог предыдущего решения с добавкой синтаксического сахара
	// обеспечиваемого операторами << и функцией MakeCondiment
	{
		auto beverage = make_unique<CLatte>() // Наливаем чашечку латте,
			<< MakeCondiment<CCinnamon>() // оборачиваем корицей,
			<< MakeCondiment<CLemon>(2) // добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry) // брасаем пару кубиков сухого льда
			<< MakeCondiment<CChocolateCrumbs>(2); // посыпаем шоколадной крошкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = make_unique<CMilkshake>() // Наливаем молочный коктейль
			<< MakeCondiment<CSyrup>(SyrupType::Maple) // заливаем кленовым сиропом
			<< MakeCondiment<CCoconutFlakes>(8); // посыпаем кокосовой стружкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	cout << endl;
	DialogWithUser();
}
