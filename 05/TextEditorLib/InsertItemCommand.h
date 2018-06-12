#pragma once
#include "AbstractCommand.h"
#include "DocumentItems.h"
#include "MayBeEndPosition.h"

class InsertItemCommand final : public AbstractCommand
{
public:
	InsertItemCommand(DocumentItems& items, IDocumentItemPtr item, MayBeEndPosition index);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	auto GetInsertionPos() const;
	auto GetErasurePos() const;

private:
	DocumentItems& m_items;
	const IDocumentItemPtr m_item;
	const MayBeEndPosition m_index;
};
