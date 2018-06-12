#pragma once
#include "IParagraph_fwd.h"

class IParagraph
{
public:
	virtual ~IParagraph() = default;

	virtual std::string GetText() const = 0;
	virtual void SetText(const std::string& text) = 0;
};
