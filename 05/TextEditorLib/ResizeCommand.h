#pragma once
#include "AbstractCommand.h"
#include "Size.h"

class ResizeCommand final : public AbstractCommand
{
public:
	ResizeCommand(gsl::not_null<Size*> currentSize, Size newSize);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	void SwapValues();

	Size& m_currentSize;
	Size m_newSize;
};
