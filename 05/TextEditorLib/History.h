#pragma once
#include "IHistory.h"

class History final : public IHistory
{
public:
	explicit History(size_t maxSize);
	~History();

	bool CanUndo() const;
	void Undo();

	bool CanRedo() const;
	void Redo();

	void AddAndExecuteCommand(ICommandUniquePtr command) override;

private:
	std::deque<ICommandUniquePtr> m_commands;
	size_t m_nextCommandIndex = 0;
	const size_t m_maxSize = UINT_MAX;
};
