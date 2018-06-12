#pragma once
#include "FileReference.h"
#include "IFileSystem_fwd.h"

class FileStorage
{
public:
	explicit FileStorage(IFileSystemPtr fs);

	FileRef AddFile(const Path& filePath) const;

private:
	const IFileSystemPtr m_fs;
};
