#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "DeleteItemCommand.h"
#include "DocumentItemFactory.h"
#include "HtmlExporter.h"
#include "IDocumentItem.h"
#include "Image.h"
#include "InsertItemCommand.h"
#include "Paragraph.h"

namespace
{

IDocumentItemPtr GetItemImpl(const DocumentItems& items, size_t pos)
{
	Expects(pos < items.size());
	auto item = *std::next(items.begin(), pos);
	Ensures(item);
	return item;
}

} // namespace

Document::Document(const IFileSystemPtr& fs)
	: m_fs(fs)
	, m_storage(fs)
{
}

IParagraphPtr Document::InsertParagraph(const std::string& text, MayBeEndPosition position)
{
	auto paragraph = std::make_shared<CParagraph>(text, m_history);
	InsertItem(CreateDocumentItem(paragraph), position);
	return paragraph;
}

IImagePtr Document::InsertImage(const Path& path, Size imageSize, MayBeEndPosition position)
{
	auto newFile = m_storage.AddFile(path);
	auto image = std::make_shared<CImage>(move(newFile), imageSize, m_history);
	InsertItem(CreateDocumentItem(image), position);
	return image;
}

void Document::InsertItem(IDocumentItemPtr&& item, MayBeEndPosition position)
{
	m_history.AddAndExecuteCommand(std::make_unique<InsertItemCommand>(m_items, std::move(item), position));
}

size_t Document::GetItemsCount() const
{
	return m_items.size();
}

IDocumentItemPtr Document::GetItem(size_t index)
{
	return GetItemImpl(m_items, index);
}

IConstDocumentItemPtr Document::GetItem(size_t index) const
{
	return GetItemImpl(m_items, index);
}

void Document::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<DeleteItemCommand>(m_items, index));
}

void Document::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<ChangeStringCommand>(&m_title, title));
}

std::string Document::GetTitle() const
{
	return m_title;
}

bool Document::CanUndo() const
{
	return m_history.CanUndo();
}

void Document::Undo()
{
	m_history.Undo();
}

bool Document::CanRedo() const
{
	return m_history.CanRedo();
}

void Document::Redo()
{
	m_history.Redo();
}

void Document::Save(const Path& path) const
{
	HtmlExporter exporter(m_fs, "images");
	exporter.Export(*this, path);
}

IParagraphPtr GetParagraph(IDocument& doc, size_t index)
{
	auto item = doc.GetItem(index);
	return item->GetParagraph();
}

IImagePtr GetImage(IDocument& doc, size_t index)
{
	auto item = doc.GetItem(index);
	return item->GetImage();
}
