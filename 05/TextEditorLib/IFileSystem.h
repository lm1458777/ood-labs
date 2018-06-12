#pragma once
#include "IFileSystem_fwd.h"
#include "Path.h"
#include <boost/filesystem/operations.hpp>

using OutputStreamPtr = std::shared_ptr<std::ostream>;
using CopyOption = boost::filesystem::copy_option;

class IFileSystem
{
public:
	virtual ~IFileSystem() = default;

	virtual void CreateDirectories(const Path& dir) = 0;
	virtual void CopyFile(const Path& src, const Path& dest, CopyOption option) = 0;
	virtual void DeleteFile(const Path& filePath) = 0;

	virtual OutputStreamPtr CreateOutputFileStream(const Path& path) = 0;
};
