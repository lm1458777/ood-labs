#include "stdafx.h"
#include "HtmlExporter.h"
#include "CopyFiles.h"
#include "DocumentItemRange.h"
#include "IDocument.h"
#include "IDocumentItem.h"
#include "IDocumentItemVisitor.h"
#include "IFileSystem.h"
#include "IImage.h"
#include "IParagraph.h"

using namespace std;

namespace
{

string EncodeHtmlStr(const string& str)
{
	// http://www.htmlhelp.com/reference/html40/entities/special.html
	const unordered_map<char, const char*> HTML_SPECIAL_ENTITIES = {
		{ '<', "&lt;" },
		{ '>', "&gt;" },
		{ '&', "&amp;" },
		{ '"', "&quot;" },
	};

	string encodedStr;
	encodedStr.reserve(str.size());
	for (auto ch : str)
	{
		auto itSpecial = HTML_SPECIAL_ENTITIES.find(ch);
		if (itSpecial == HTML_SPECIAL_ENTITIES.end())
		{
			encodedStr += ch;
		}
		else
		{
			encodedStr += itSpecial->second;
		}
	}

	return encodedStr;
}

using PathProvider = std::function<Path(const Path&)>;

class Exporter : public IDocumentItemVisitor
{
public:
	Exporter(ostream& out, PathProvider destPathProvider)
		: m_out(out)
		, m_destPathProvider(move(destPathProvider))
	{
	}

	void VisitParagraph(const IParagraph& paragraph) override
	{
		m_out << "\t<p>" << EncodeHtmlStr(paragraph.GetText()) << "</p>\n";
	}

	void VisitImage(const IImage& image) override
	{
		auto imgPath = m_destPathProvider(image.GetPath());
		m_out << "\t<img src='" << EncodeHtmlStr(imgPath.generic_string()) << "'"
			  << " width=" << image.GetWidth()
			  << " height=" << image.GetHeight()
			  << ">\n";
	}

private:
	ostream& m_out;
	const PathProvider m_destPathProvider;
};

void ExportDocumentToHtml(const IDocument& doc, ostream& htmlOut, PathProvider pathProvider)
{
	htmlOut << "<!DOCTYPE html>\n"
			   "<html>\n";

	htmlOut << "<head>\n"
			<< "\t<title>" + EncodeHtmlStr(doc.GetTitle()) + "</title>\n"
			<< "</head>\n";

	htmlOut << "<body>\n";
	VisitItems(doc, Exporter{ htmlOut, move(pathProvider) });
	htmlOut << "</body>\n";

	htmlOut << "</html>";
}

struct ImageCollector : IDocumentItemVisitor
{
	PathSet images;

	void VisitParagraph(const IParagraph& /*paragraph*/) override
	{
		// do nothing
	}

	void VisitImage(const IImage& image) override
	{
		bool inserted;
		tie(ignore, inserted) = images.emplace(image.GetPath());
		assert(inserted);
	}
};

PathSet GetImageFiles(const IDocument& doc)
{
	ImageCollector collector;
	VisitItems(doc, collector);
	return collector.images;
}

} // namespace

HtmlExporter::HtmlExporter(IFileSystemPtr fs, Path imagesDir)
	: m_imagesDir(move(imagesDir))
	, m_fs(move(fs))
{
	Expects(m_fs);
}

void HtmlExporter::Export(const IDocument& doc, const Path& htmlFile)
{
	if (htmlFile.empty())
	{
		throw runtime_error("Path must not be empty");
	}

	m_fs->CreateDirectories(htmlFile.parent_path());

	auto file = m_fs->CreateOutputFileStream(htmlFile);
	auto imagesRemap = CopyFiles(GetImageFiles(doc), htmlFile.parent_path() / m_imagesDir, *m_fs);
	auto imageMapper = [imagesDir = m_imagesDir, &imagesRemap](const Path& srcPath) {
		return imagesDir / imagesRemap.at(srcPath).filename();
	};
	ExportDocumentToHtml(doc, *file, move(imageMapper));
}
