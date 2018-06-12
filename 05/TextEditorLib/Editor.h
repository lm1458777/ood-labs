#pragma once
#include "MayBeEndPosition.h"

class IDocument;

class IErrorReporter
{
public:
	virtual ~IErrorReporter() = default;

	virtual void InvalidPosition() = 0;
	virtual void InvalidSize() = 0;
	virtual void PositionOutOfRange() = 0;
	virtual void ReportError(const std::string& errorMsg) = 0;
	virtual void CantUndo() = 0;
	virtual void CantRedo() = 0;
};

class Editor
{
public:
	explicit Editor(IDocument& doc, IErrorReporter& errorReporter, std::ostream& out);

	void SetTitle(std::istream& in);

	void InsertParagraph(std::istream& in);
	void ReplaceText(std::istream& in);

	void InsertImage(std::istream& in);
	void ResizeImage(std::istream& in);

	void DeleteItem(std::istream& in);

	void List() const;

	void Undo();
	void Redo();

	void Save(std::istream& in) const;

private:
	bool IsValidPosition(size_t pos) const;
	bool IsValidMayBeEndPosition(MayBeEndPosition pos) const;

	IDocument& m_document;
	IErrorReporter& m_errors;
	std::ostream& m_out;
};
