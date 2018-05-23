#pragma once
#include "IStyle_fwd.h"
#include "CommonTypes.h"

IFillStylePtr CreateFillStyle(RGBAColor color, bool enable = true);
ILineStylePtr CreateLineStyle(RGBAColor color, float width = 1.f, bool enable = true);

