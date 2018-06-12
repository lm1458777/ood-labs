#pragma once
#include "AbstractCommand.h"
#include "DocumentItems.h"

class DeleteItemCommand final : public AbstractCommand
{
public:
	DeleteItemCommand(DocumentItems& items, size_t index);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	DocumentItems& m_items;
	IDocumentItemPtr m_deletedItem;
	size_t m_index;
};
