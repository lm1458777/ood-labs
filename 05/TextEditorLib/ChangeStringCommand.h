#pragma once
#include "AbstractCommand.h"

class ChangeStringCommand final : public AbstractCommand
{
public:
	ChangeStringCommand(gsl::not_null<std::string*> target, std::string newValue);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::string& m_target;
	std::string m_newValue;
};
