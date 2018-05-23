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
