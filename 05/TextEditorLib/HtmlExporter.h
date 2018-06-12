#pragma once
#include "IFileSystem_fwd.h"
#include "Path.h"

class IDocument;

class HtmlExporter
{
public:
	explicit HtmlExporter(IFileSystemPtr fs, Path imagesDir);

	void Export(const IDocument& doc, const Path& htmlFile);

private:
	const IFileSystemPtr m_fs;
	const Path m_imagesDir;
};
