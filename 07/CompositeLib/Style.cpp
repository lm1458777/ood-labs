#include "stdafx.h"
#include "Style.h"

FillStyle::FillStyle(RGBAColor color, bool enable)
	: IBaseStyleImpl(color, enable)
{
}

IFillStylePtr FillStyle::Clone() const
{
	return std::make_unique<FillStyle>(*this);
}

LineStyle::LineStyle(RGBAColor color, float width, bool enable)
	: IBaseStyleImpl(color, enable)
	, m_width(width)
{
}

float LineStyle::GetWidth() const
{
	return m_width;
}

void LineStyle::SetWidth(float width)
{
	m_width = width;
}

ILineStyleUniquePtr LineStyle::Clone() const
{
	return std::make_unique<LineStyle>(*this);
}

bool operator==(const IFillStyle& style1, const IFillStyle& style2)
{
	return style1.IsEnabled() == style2.IsEnabled()
		&& style1.GetColor() == style2.GetColor();
}

bool operator==(const ILineStyle& style1, const ILineStyle& style2)
{
	return style1.IsEnabled() == style2.IsEnabled()
		&& style1.GetColor() == style2.GetColor()
		&& style1.GetWidth() == style2.GetWidth();
}
