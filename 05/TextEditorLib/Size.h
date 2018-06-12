#pragma once

struct Size
{
	unsigned width = 0u;
	unsigned height = 0u;

	constexpr Size() = default;
	constexpr Size(unsigned w, unsigned h)
		: width(w)
		, height(h)
	{
	}
};
