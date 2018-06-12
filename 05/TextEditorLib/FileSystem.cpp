#include "stdafx.h"
#include "FileSystem.h"
#include <boost\filesystem\operations.hpp>

using namespace boost::filesystem;

void FileSystem::CreateDirectories(const Path& dir)
{
	create_directories(dir);
}

void FileSystem::CopyFile(const Path& src, const Path& dest, CopyOption option)
{
	copy_file(src, dest, option);
}

void FileSystem::DeleteFile(const Path& filePath)
{
	remove(filePath);
}

OutputStreamPtr FileSystem::CreateOutputFileStream(const Path& path)
{
	auto file = std::make_shared<std::ofstream>(path.generic_string());
	if (!file->is_open())
	{
		throw std::runtime_error("Cannot open file ''" + path.generic_string() + "'");
	}
	return file;
}
