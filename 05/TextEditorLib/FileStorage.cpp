#include "stdafx.h"
#include "FileStorage.h"
#include "IFileSystem.h"

using namespace std;

namespace
{

Path GetTemporaryFileName()
{
	char buf[FILENAME_MAX];
	if (0 != tmpnam_s(buf))
	{
		throw runtime_error("Failed to get temporary file name");
	}

	return buf;
}

} // namespace

FileStorage::FileStorage(IFileSystemPtr fs)
	: m_fs(move(fs))
{
}

FileRef FileStorage::AddFile(const Path& filePath) const
{
	Path newPath = GetTemporaryFileName();
	newPath.replace_extension(filePath.extension());

	m_fs->CopyFile(filePath, newPath, CopyOption::fail_if_exists);

	return std::make_shared<FileReference>(std::move(newPath), m_fs);
}
