#pragma once
#include "IDocumentItem_fwd.h"
#include "IImage_fwd.h"
#include "IParagraph_fwd.h"
#include "MayBeEndPosition.h"
#include "Path.h"
#include "Size.h"

class IDocument
{
public:
	virtual ~IDocument() = default;

	virtual IParagraphPtr InsertParagraph(const std::string& text, MayBeEndPosition position = EndPos) = 0;
	virtual IImagePtr InsertImage(const Path& path, Size imageSize, MayBeEndPosition position = EndPos) = 0;

	virtual size_t GetItemsCount() const = 0;
	virtual IDocumentItemPtr GetItem(size_t index) = 0;
	virtual IConstDocumentItemPtr GetItem(size_t index) const = 0;

	virtual void DeleteItem(size_t index) = 0;

	virtual std::string GetTitle() const = 0;
	virtual void SetTitle(const std::string& title) = 0;

	virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;
	virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;

	virtual void Save(const Path& path) const = 0;
};

void ListDocument(const IDocument& doc, std::ostream& out);

IParagraphPtr GetParagraph(IDocument& doc, size_t index);
IImagePtr GetImage(IDocument& doc, size_t index);
