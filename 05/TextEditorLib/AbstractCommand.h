#pragma once
#include "ICommand.h"

class AbstractCommand : public ICommand
{
public:
	void Execute() final;
	void Unexecute() final;

protected:
	virtual void DoExecute() = 0;
	virtual void DoUnexecute() = 0;

private:
	bool m_executed = false;
};
