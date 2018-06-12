#pragma once
#include "ICommand_fwd.h"

class IHistory
{
public:
	virtual ~IHistory() = default;

	virtual void AddAndExecuteCommand(ICommandUniquePtr command) = 0;
};
