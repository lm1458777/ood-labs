#include "stdafx.h"
#include "DeleteItemCommand.h"

using namespace std;

DeleteItemCommand::DeleteItemCommand(DocumentItems& items, size_t index)
	: m_items(items)
	, m_index(index)
{
}

void DeleteItemCommand::DoExecute()
{
	Expects(m_index < m_items.size());
	auto eraseItemIt = next(m_items.begin(), m_index);
	m_deletedItem = *eraseItemIt;
	m_items.erase(eraseItemIt);
}

void DeleteItemCommand::DoUnexecute()
{
	Expects(m_index <= m_items.size());
	m_items.insert(next(m_items.begin(), m_index), m_deletedItem);
}
