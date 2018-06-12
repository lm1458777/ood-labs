#include "stdafx.h"
#include "Image.h"
#include "History.h"
#include "ResizeCommand.h"

using namespace std;

CImage::CImage(FileRef file, Size imageSize, IHistory& history)
	: m_file(move(file))
	, m_imageSize(imageSize)
	, m_history(history)
{
}

Path CImage::GetPath() const
{
	return m_file->GetPath();
}

unsigned CImage::GetWidth() const
{
	return m_imageSize.width;
}

unsigned CImage::GetHeight() const
{
	return m_imageSize.height;
}

void CImage::Resize(Size newSize)
{
	m_history.AddAndExecuteCommand(make_unique<ResizeCommand>(&m_imageSize, newSize));
}
