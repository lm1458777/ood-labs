#pragma once
#include "IFileSystem_fwd.h"
#include "Path.h"

class FileReference
{
public:
	explicit FileReference(Path filePath, IFileSystemPtr fs);
	~FileReference();

	Path GetPath() const
	{
		return m_path;
	}

private:
	const Path m_path;
	const IFileSystemPtr m_fs;
};

using FileRef = std::shared_ptr<FileReference>;
