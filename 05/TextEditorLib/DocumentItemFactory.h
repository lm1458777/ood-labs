#pragma once
#include "IDocumentItem_fwd.h"
#include "IImage_fwd.h"
#include "IParagraph_fwd.h"

IDocumentItemPtr CreateDocumentItem(const IParagraphPtr& paragraph);
IDocumentItemPtr CreateDocumentItem(const IImagePtr& image);
