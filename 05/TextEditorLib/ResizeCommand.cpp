#include "stdafx.h"
#include "ResizeCommand.h"

ResizeCommand::ResizeCommand(gsl::not_null<Size*> currentSize, Size newSize)
	: m_currentSize(*currentSize)
	, m_newSize(newSize)
{
}

void ResizeCommand::DoExecute()
{
	SwapValues();
}

void ResizeCommand::DoUnexecute()
{
	SwapValues();
}

void ResizeCommand::SwapValues()
{
	std::swap(m_currentSize, m_newSize);
}
