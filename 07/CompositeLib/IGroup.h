#pragma once
#include "IGroup_fwd.h"
#include "IShape.h"

class IGroup : public IShape
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual IShapePtr GetShapeAtIndex(size_t index) = 0;
	virtual void InsertShape(const IShapePtr& pShape, size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;
};

void AddShape(IGroup& group, const IShapePtr& shape);
