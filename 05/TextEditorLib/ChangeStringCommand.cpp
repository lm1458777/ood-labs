#include "stdafx.h"
#include "ChangeStringCommand.h"

ChangeStringCommand::ChangeStringCommand(gsl::not_null<std::string*> target, std::string newValue)
	: m_target(*target)
	, m_newValue(std::move(newValue))
{
}

void ChangeStringCommand::DoExecute()
{
	m_newValue.swap(m_target);
}

void ChangeStringCommand::DoUnexecute()
{
	m_newValue.swap(m_target);
}
