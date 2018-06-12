#pragma once
#include "IImage_fwd.h"
#include "IParagraph_fwd.h"

class IDocumentItemVisitor
{
public:
	virtual void VisitParagraph(const IParagraph& paragraph) = 0;
	virtual void VisitImage(const IImage& image) = 0;

	virtual ~IDocumentItemVisitor() = default;
};
