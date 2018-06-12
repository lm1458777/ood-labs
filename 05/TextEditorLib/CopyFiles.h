#pragma once
#include "IFileSystem_fwd.h"
#include "Path.h"

using PathSet = std::unordered_set<Path, PathHasher>;
using PathMap = std::unordered_map<Path, Path, PathHasher>;

PathMap CopyFiles(const PathSet& srcFiles, const Path& destDir, IFileSystem& fs);
