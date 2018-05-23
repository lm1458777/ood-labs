#include "stdafx.h"
#include "ShapeFactory.h"
#include "Group.h"
#include "Rectangle.h"

IShapePtr CreateRectangle(const RectD& frame, const IFillStylePtr& fillStyle, const ILineStylePtr& lineStyle)
{
	return std::make_shared<CRectangle>(frame, fillStyle, lineStyle);
}

IGroupPtr CreateGroup()
{
	return std::make_shared<CGroup>();
}
