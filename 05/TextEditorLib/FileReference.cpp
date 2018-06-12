#include "stdafx.h"
#include "FileReference.h"
#include "IFileSystem.h"

FileReference::FileReference(Path filePath, IFileSystemPtr fs)
	: m_path(std::move(filePath))
	, m_fs(std::move(fs))
{
	Expects(m_fs);
}

FileReference::~FileReference()
{
	m_fs->DeleteFile(m_path);
}
