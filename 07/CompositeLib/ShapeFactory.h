#pragma once
#include "CommonTypes.h"
#include "IGroup_fwd.h"
#include "IShape_fwd.h"
#include "IStyle_fwd.h"

IShapePtr CreateRectangle(const RectD& frame, const IFillStylePtr& fillStyle, const ILineStylePtr& lineStyle);
IShapePtr CreateTriangle(const RectD& frame, const IFillStylePtr& fillStyle, const ILineStylePtr& lineStyle);
IShapePtr CreateEllipse(const RectD& frame, const IFillStylePtr& fillStyle, const ILineStylePtr& lineStyle);

IGroupPtr CreateGroup();
