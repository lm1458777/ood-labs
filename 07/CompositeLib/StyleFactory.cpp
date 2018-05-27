#include "stdafx.h"
#include "StyleFactory.h"

FillStyle CreateFillStyle(RGBAColor color, bool enable)
{
	return FillStyle(color, enable);
}

FillStyle CreateNoFillStyle()
{
	return CreateFillStyle(0, false);
}

LineStyle CreateLineStyle(RGBAColor color, float width, bool enable)
{
	return LineStyle(color, width, enable);
}

LineStyle CreateNoLineStyle()
{
	return CreateLineStyle(0, 0, false);
}
