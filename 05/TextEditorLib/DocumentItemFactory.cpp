#include "stdafx.h"
#include "DocumentItemFactory.h"
#include "DocumentItem.h"

IDocumentItemPtr CreateDocumentItem(const IParagraphPtr& paragraph)
{
	return std::make_shared<ParagraphDocumentItem>(paragraph);
}

IDocumentItemPtr CreateDocumentItem(const IImagePtr& image)
{
	return std::make_shared<ImageDocumentItem>(image);
}
