#include "stdafx.h"
#include "DocumentItemRange.h"
#include "IDocument.h"
#include "IDocumentItem.h"
#include "IDocumentItemVisitor.h"
#include "IImage.h"
#include "IParagraph.h"

namespace
{

class Quoted
{
public:
	explicit Quoted(const std::string& s)
		: m_s(s)
	{
	}

	void Print(std::ostream& out) const
	{
		out << '\'' << m_s << '\'';
	}

private:
	const std::string& m_s;
};

std::ostream& operator<<(std::ostream& out, const Quoted& s)
{
	s.Print(out);
	return out;
}

class Printer : public IDocumentItemVisitor
{
public:
	explicit Printer(std::ostream& out)
		: m_out(out)
	{
	}

	void PrintTitle(const std::string& title)
	{
		m_out << "Title: " << Quoted(title) << std::endl;
	}

	void VisitParagraph(const IParagraph& paragraph) override
	{
		m_out << m_index << ". Paragraph: " << Quoted(paragraph.GetText()) << std::endl;
		++m_index;
	}

	void VisitImage(const IImage& image) override
	{
		m_out << m_index << ". Image: "
			  << image.GetWidth() << "x" << image.GetHeight()
			  << ", " << Quoted(image.GetPath().generic_string())
			  << std::endl;
		++m_index;
	}

private:
	std::ostream& m_out;
	int m_index = 0;
};

} // namespace

void ListDocument(const IDocument& doc, std::ostream& out)
{
	Printer p{ out };
	p.PrintTitle(doc.GetTitle());
	VisitItems(doc, p);
}
