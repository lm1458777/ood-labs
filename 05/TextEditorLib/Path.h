#pragma once
#include <boost/functional/hash.hpp>

using Path = boost::filesystem::path;

struct PathHasher
{
	auto operator()(const Path& p) const
	{
		return boost::filesystem::hash_value(p);
	}
};
