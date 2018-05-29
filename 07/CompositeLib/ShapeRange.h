#pragma once
#include "IShapes.h"

inline auto GetShapeRange(const IShapes& shapes)
{
	auto getShape = [&shapes](auto i) {
		return shapes.GetShapeAtIndex(i);
	};

	return boost::irange(static_cast<size_t>(0), shapes.GetShapesCount()) | boost::adaptors::transformed(getShape);
}
