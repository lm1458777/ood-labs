#pragma once
#include "IImage.h"
#include "FileReference.h"

class IHistory;

class CImage : public IImage
{
public:
	CImage(FileRef file, Size imageSize, IHistory& history);

	Path GetPath() const override;
	unsigned GetWidth() const override;
	unsigned GetHeight() const override;
	void Resize(Size newSize) override;

private:
	const FileRef m_file;
	Size m_imageSize;
	IHistory& m_history;
};
