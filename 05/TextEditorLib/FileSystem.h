#pragma once
#include "IFileSystem.h"

class FileSystem : public IFileSystem
{
public:
	void CreateDirectories(const Path& dir) override;
	void CopyFile(const Path& src, const Path& dest, CopyOption option) override;
	void DeleteFile(const Path& filePath) override;

	OutputStreamPtr CreateOutputFileStream(const Path& path) override;
};
