#pragma once

class Menu
{
public:
	using Command = std::function<void(std::istream& args)>;

	explicit Menu(std::istream& in, std::ostream& out);

	void AddItem(const std::string& shortcut, const std::string& args, const std::string& description, const Command& command);
	void Run();

	void ShowInstructions() const;
	void Exit();

private:
	bool ExecuteCommand(const std::string& userInput);

	struct Item
	{
		std::string shortcut;
		std::string args;
		std::string description;
		Command command;
	};
	std::vector<Item> m_items;

	bool m_exit = false;

	std::istream& m_in;
	std::ostream& m_out;
};
