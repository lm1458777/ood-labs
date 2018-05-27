#pragma once
#include "CommonTypes.h"
#include "Style.h"

FillStyle CreateFillStyle(RGBAColor color, bool enable = true);
FillStyle CreateNoFillStyle();

LineStyle CreateLineStyle(RGBAColor color, float width = 1.f, bool enable = true);
LineStyle CreateNoLineStyle();
