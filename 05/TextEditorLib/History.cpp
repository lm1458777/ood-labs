#include "stdafx.h"
#include "History.h"
#include "ICommand.h"
#include <gsl/gsl>

History::History(size_t maxSize)
	: m_maxSize(maxSize)
{
}

History::~History() = default;

bool History::CanUndo() const
{
	return m_nextCommandIndex != 0;
}

bool History::CanRedo() const
{
	return m_nextCommandIndex != m_commands.size();
}

void History::Undo()
{
	if (CanUndo())
	{
		m_commands[m_nextCommandIndex - 1]->Unexecute(); // может выбросить исключение
		--m_nextCommandIndex;
	}
}

void History::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute(); // может выбросить исключение
		++m_nextCommandIndex;
	}
}

void History::AddAndExecuteCommand(ICommandUniquePtr command)
{
	if (m_nextCommandIndex == m_maxSize)
	{
		m_commands.pop_front();
		--m_nextCommandIndex;
	}

	if (m_nextCommandIndex < m_commands.size()) // Не происходит расширения истории команд
	{
		command->Execute(); // может бросить исключение
		m_commands.push_back(move(command)); // исключение выброшено не будет, т.к. размер <= текущему
		++m_nextCommandIndex;
	}
	else // будет происходить расширение истории команд
	{
		assert(m_nextCommandIndex == m_commands.size());
		// резервируем место под добавляемую команду
		m_commands.emplace_back(); // может выбросить исключение, но мы еще ничего не трогали

		bool commit = false;
		// Блок кода, который выполнится при любом выходе из данного scope (исключение, return, обычный выход)
		auto removePlaceholder = gsl::finally([this, &commit]() {
			if (!commit)
			{
				m_commands.pop_back(); // удаляем из очереди команд команду-заглушку, т.к. команда зафейлилась
			}
		});
		command->Execute(); // может выбросить исключение
		commit = true; // все ок, можно утверждаем изменения
		m_commands.back() = move(command); // заменяем команду заглушку на исполненную (не бросает исключений)
		++m_nextCommandIndex;
	}
}
