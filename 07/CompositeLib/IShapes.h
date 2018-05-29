#pragma once
#include "IShape_fwd.h"

class IShapes
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual IShapePtr GetShapeAtIndex(size_t index) const = 0;
	virtual void InsertShape(const IShapePtr& pShape, size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;
};

void AddShape(IShapes& shapes, const IShapePtr& shape);

