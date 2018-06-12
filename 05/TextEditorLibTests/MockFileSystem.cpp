#include "stdafx.h"
#include "MockFileSystem.h"

static auto EmptyDeleter = [](auto&&) {
	// do nothing
};

OutputStreamPtr MockFileSystem::CreateOutputFileStream(const Path& path)
{
	std::shared_ptr<std::ostringstream> stream{ &out, EmptyDeleter };
	createdStreams.push_back(path);
	return stream;
}
