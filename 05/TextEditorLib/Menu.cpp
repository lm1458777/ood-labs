#include "stdafx.h"
#include "Menu.h"

using namespace std;

Menu::Menu(std::istream& in, std::ostream& out)
	: m_in(in)
	, m_out(out)
{
}

void Menu::AddItem(const string& shortcut, const string& args, const string& description, const Command& command)
{
	m_items.push_back(Item{ shortcut, args, description, command });
}

void Menu::Run()
{
	ShowInstructions();

	string userInput;
	while ((m_out << ">")
		&& getline(m_in, userInput)
		&& ExecuteCommand(userInput))
	{
	}
}

void Menu::ShowInstructions() const
{
	m_out << "Commands:\n";
	for (auto& item : m_items)
	{
		m_out << "  " << item.shortcut << " " << item.args << "\n\t" << item.description << "\n";
	}
}

void Menu::Exit()
{
	m_exit = true;
}

bool Menu::ExecuteCommand(const string& userInput)
{
	istringstream iss(userInput);
	iss.exceptions(ios_base::badbit);

	string name;
	iss >> name;

	auto it = find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == name;
	});
	if (it != m_items.end())
	{
		it->command(iss);
	}
	else
	{
		m_out << "Unknown command\n";
	}

	return !m_exit;
}
