#include "stdafx.h"
#include "CopyFiles.h"
#include "IFileSystem.h"

PathMap CopyFiles(const PathSet& srcFiles, const Path& destDir, IFileSystem& fs)
{
	PathMap oldToNewPathMap;
	if (srcFiles.empty())
	{
		return oldToNewPathMap;
	}

	fs.CreateDirectories(destDir);

	bool commit = false;
	auto deleteCopies = gsl::finally([&]() {
		if (!commit)
		{
			for (const auto& p : oldToNewPathMap)
			{
				fs.DeleteFile(p.second);
			}
		}
	});

	for (const auto& srcPath : srcFiles)
	{
		auto newPath = destDir / srcPath.filename();
		fs.CopyFile(srcPath, newPath, CopyOption::overwrite_if_exists);
		oldToNewPathMap.emplace(srcPath, std::move(newPath));
	}

	commit = true;
	return oldToNewPathMap;
}
