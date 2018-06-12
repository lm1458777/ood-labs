#include "stdafx.h"
#include "Paragraph.h"
#include "ChangeStringCommand.h"
#include "IHistory.h"

CParagraph::CParagraph(std::string text, IHistory& history)
	: m_text(std::move(text))
	, m_history(history)
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string& text)
{
	m_history.AddAndExecuteCommand(std::make_unique<ChangeStringCommand>(&m_text, text));
}
