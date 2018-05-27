#include "stdafx.h"
#include "Style.h"

namespace
{

void CopyBaseStyleValues(IBaseStyle& dest, const IBaseStyle& src)
{
	auto color = src.GetColor();
	if (color.is_initialized())
	{
		dest.SetColor(*color);
	}

	auto isEnabled = src.IsEnabled();
	if (isEnabled.is_initialized())
	{
		dest.Enable(*isEnabled);
	}
}

} // namespace

FillStyle::FillStyle(RGBAColor color, bool enable)
	: IBaseStyleImpl(color, enable)
{
}

LineStyle::LineStyle(RGBAColor color, float width, bool enable)
	: IBaseStyleImpl(color, enable)
	, m_width(width)
{
}

boost::optional<float> LineStyle::GetWidth() const
{
	return m_width;
}

void LineStyle::SetWidth(float width)
{
	m_width = width;
}

void CopyValues(IFillStyle& dest, const IFillStyle& src)
{
	CopyBaseStyleValues(dest, src);
}

void CopyValues(ILineStyle& dest, const ILineStyle& src)
{
	CopyBaseStyleValues(dest, src);

	auto width = src.GetWidth();
	if (width.is_initialized())
	{
		dest.SetWidth(*width);
	}
}
