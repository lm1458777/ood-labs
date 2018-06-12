#pragma once
#include "IDocumentItem_fwd.h"
#include "IImage_fwd.h"
#include "IParagraph_fwd.h"

class IDocumentItemVisitor;

class IDocumentItem
{
public:
	virtual ~IDocumentItem() = default;

	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	virtual IParagraphPtr GetParagraph() = 0;
	virtual IConstParagraphPtr GetParagraph() const = 0;

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	virtual IImagePtr GetImage() = 0;
	virtual IConstImagePtr GetImage() const = 0;

	virtual void AcceptVisitor(IDocumentItemVisitor& visitor) const = 0;
};
