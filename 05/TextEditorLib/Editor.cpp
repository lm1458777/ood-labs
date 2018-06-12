#include "stdafx.h"
#include "Editor.h"
#include "IDocument.h"
#include "IImage.h"
#include "IParagraph.h"

using namespace std;

namespace
{

template <class T>
boost::optional<T> ReadInt(istream& in)
{
	T n;
	in >> n;
	return !in.fail() ? boost::make_optional(n) : boost::none;
}

boost::optional<size_t> ReadPosition(istream& in)
{
	return ReadInt<size_t>(in);
}

boost::optional<MayBeEndPosition> ReadMayBeEndPosition(istream& in)
{
	if (auto pos = ReadPosition(in))
	{
		return boost::make_optional(MayBeEndPosition(pos));
	}

	in.clear();
	string s;
	in >> s;
	if (s == "end")
	{
		return boost::make_optional(MayBeEndPosition());
	}

	return boost::none;
}

boost::optional<Size> ReadSize(istream& in)
{
	if (auto width = ReadInt<unsigned>(in))
	{
		if (auto height = ReadInt<unsigned>(in))
		{
			return Size(*width, *height);
		}
	}

	return boost::none;
}

string ReadLine(istream& in)
{
	string s;
	getline(in, s);
	return s;
}

} // namespace

Editor::Editor(IDocument& doc, IErrorReporter& errorReporter, ostream& out)
	: m_document(doc)
	, m_errors(errorReporter)
	, m_out(out)
{
}

void Editor::InsertImage(istream& in)
{
	auto position = ReadMayBeEndPosition(in);
	if (!position)
	{
		m_errors.InvalidPosition();
		return;
	}

	auto size = ReadSize(in);
	if (!size)
	{
		m_errors.InvalidSize();
		return;
	}

	string path;
	in >> path;

	if (!IsValidMayBeEndPosition(*position))
	{
		m_errors.PositionOutOfRange();
		return;
	}

	try
	{
		m_document.InsertImage(path, *size, *position);
	}
	catch (const exception& e)
	{
		m_errors.ReportError(string("Error while inserting image: ") + e.what());
	}
}

void Editor::SetTitle(istream& in)
{
	auto title = ReadLine(in);
	m_document.SetTitle(title);
}

void Editor::InsertParagraph(istream& in)
{
	auto pos = ReadMayBeEndPosition(in);
	if (!pos)
	{
		m_errors.InvalidPosition();
		return;
	}

	auto text = ReadLine(in);

	if (!IsValidMayBeEndPosition(*pos))
	{
		m_errors.PositionOutOfRange();
		return;
	}

	m_document.InsertParagraph(text, *pos);
}

void Editor::List() const
{
	m_out << "-------------" << endl;
	ListDocument(m_document, m_out);
	m_out << "-------------" << endl;
}

void Editor::Undo()
{
	if (m_document.CanUndo())
	{
		m_document.Undo();
	}
	else
	{
		m_errors.CantUndo();
	}
}

void Editor::Redo()
{
	if (m_document.CanRedo())
	{
		m_document.Redo();
	}
	else
	{
		m_errors.CantRedo();
	}
}

void Editor::Save(istream& in) const
{
	try
	{
		string savePath;
		in >> savePath;
		m_document.Save(savePath);
	}
	catch (const exception& e)
	{
		m_errors.ReportError(e.what());
	}
}

bool Editor::IsValidPosition(size_t pos) const
{
	return pos <= m_document.GetItemsCount();
}

bool Editor::IsValidMayBeEndPosition(MayBeEndPosition pos) const
{
	return pos == EndPos || IsValidPosition(*pos);
}

void Editor::ResizeImage(istream& in)
{
	auto pos = ReadPosition(in);
	if (!pos)
	{
		m_errors.InvalidPosition();
		return;
	}
	if (!IsValidPosition(*pos))
	{
		m_errors.PositionOutOfRange();
		return;
	}

	auto newSize = ReadSize(in);
	if (!newSize)
	{
		m_errors.InvalidSize();
		return;
	}

	auto image = GetImage(m_document, *pos);
	if (!image)
	{
		m_errors.ReportError("The specified item is not an image");
		return;
	}

	image->Resize(*newSize);
}

void Editor::ReplaceText(istream& in)
{
	auto pos = ReadPosition(in);
	if (!pos)
	{
		m_errors.InvalidPosition();
		return;
	}
	if (!IsValidPosition(*pos))
	{
		m_errors.PositionOutOfRange();
		return;
	}

	auto text = ReadLine(in);

	auto paragraph = GetParagraph(m_document, *pos);
	if (!paragraph)
	{
		m_errors.ReportError("The specified item is not a paragraph");
		return;
	}

	paragraph->SetText(text);
}

void Editor::DeleteItem(istream& in)
{
	auto pos = ReadPosition(in);

	if (!pos)
	{
		m_errors.InvalidPosition();
	}
	else if (!IsValidPosition(*pos))
	{
		m_errors.PositionOutOfRange();
	}
	else
	{
		m_document.DeleteItem(*pos);
	}
}
