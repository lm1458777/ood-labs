#pragma once
#include "CommonTypes.h"
#include "IStyle_fwd.h"

IFillStylePtr CreateFillStyle(RGBAColor color, bool enable = true);
IFillStylePtr CreateNoFillStyle();

ILineStylePtr CreateLineStyle(RGBAColor color, float width = 1.f, bool enable = true);
ILineStylePtr CreateNoLineStyle();
