#pragma once
#include "DocumentItems.h"
#include "FileStorage.h"
#include "History.h"
#include "IDocument.h"

class Document final : public IDocument
{
public:
	explicit Document(const IFileSystemPtr& fs);

	IParagraphPtr InsertParagraph(const std::string& text, MayBeEndPosition position = EndPos) override;
	IImagePtr InsertImage(const Path& path, Size imageSize, MayBeEndPosition position = EndPos) override;

	size_t GetItemsCount() const override;
	IDocumentItemPtr GetItem(size_t index) override;
	IConstDocumentItemPtr GetItem(size_t index) const override;

	void DeleteItem(size_t index) override;

	void SetTitle(const std::string& title) override;
	std::string GetTitle() const override;

	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

	void Save(const Path& path) const override;

private:
	void InsertItem(IDocumentItemPtr&& item, MayBeEndPosition position);

	const IFileSystemPtr m_fs;
	FileStorage m_storage;
	History m_history{ 10 };
	std::string m_title;
	DocumentItems m_items;
};
