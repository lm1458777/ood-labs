#pragma once
#include "CommonTypes.h"
#include "IGroup_fwd.h"
#include "IShape_fwd.h"

class FillStyle;
class LineStyle;

IShapePtr CreateRectangle(const RectD& frame, const FillStyle& fillStyle, const LineStyle& lineStyle);
IShapePtr CreateTriangle(const RectD& frame, const FillStyle& fillStyle, const LineStyle& lineStyle);
IShapePtr CreateEllipse(const RectD& frame, const FillStyle& fillStyle, const LineStyle& lineStyle);

IGroupPtr CreateGroup();
