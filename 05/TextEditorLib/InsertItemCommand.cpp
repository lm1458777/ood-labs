#include "stdafx.h"
#include "InsertItemCommand.h"

using namespace std;

InsertItemCommand::InsertItemCommand(DocumentItems& items, IDocumentItemPtr item, MayBeEndPosition index)
	: m_items(items)
	, m_item(std::move(item))
	, m_index(index)
{
}

auto InsertItemCommand::GetInsertionPos() const
{
	if (m_index == EndPos)
	{
		return m_items.end();
	}

	Expects(*m_index <= m_items.size());
	return next(m_items.begin(), *m_index);
}

void InsertItemCommand::DoExecute()
{
	m_items.insert(GetInsertionPos(), m_item);
}

auto InsertItemCommand::GetErasurePos() const
{
	Expects(!m_items.empty());

	if (m_index == EndPos)
	{
		return prev(m_items.end());
	}

	Expects(*m_index < m_items.size());
	return next(m_items.begin(), *m_index);
}

void InsertItemCommand::DoUnexecute()
{
	m_items.erase(GetErasurePos());
}
