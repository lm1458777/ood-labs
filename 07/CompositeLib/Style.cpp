#include "stdafx.h"
#include "Style.h"

FillStyle::FillStyle(RGBAColor color, bool enable)
	: IBaseStyleImpl(color, enable)
{
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
