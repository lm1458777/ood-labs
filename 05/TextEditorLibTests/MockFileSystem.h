#pragma once
#include "../TextEditorLib/IFileSystem.h"

struct MockFileSystem : public IFileSystem
{
	using PathVector = std::vector<Path>;

	PathVector createdDirectories;
	void CreateDirectories(const Path& dir) override
	{
		createdDirectories.push_back(dir);
	}

	struct PathPair
	{
		Path source;
		Path dest;
	};
	std::vector<PathPair> copiedFiles;
	void CopyFile(const Path& src, const Path& dest, CopyOption /*option*/) override
	{
		copiedFiles.push_back(PathPair{ src, dest });
	}

	PathVector deletedFiles;
	void DeleteFile(const Path& filePath) override
	{
		deletedFiles.push_back(filePath);
	}

	PathVector createdStreams;
	std::ostringstream out;
	OutputStreamPtr CreateOutputFileStream(const Path& path) override;
};
