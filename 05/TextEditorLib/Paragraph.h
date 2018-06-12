#pragma once
#include "IParagraph.h"

class IHistory;

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string text, IHistory& history);

	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
	IHistory& m_history;
};
