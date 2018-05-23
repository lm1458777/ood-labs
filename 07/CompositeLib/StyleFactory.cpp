#include "stdafx.h"
#include "StyleFactory.h"
#include "Style.h"

IFillStylePtr CreateFillStyle(RGBAColor color, bool enable)
{
	return std::make_shared<FillStyle>(color, enable);
}

ILineStylePtr CreateLineStyle(RGBAColor color, float width, bool enable)
{
	return std::make_shared<LineStyle>(color, width, enable);
}
