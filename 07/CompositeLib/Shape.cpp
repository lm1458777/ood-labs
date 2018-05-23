#include "stdafx.h"
#include "Shape.h"
#include "ColorUtils.h"
#include "ICanvas.h"
#include "IStyle.h"

CShape::CShape(const RectD& frame, IFillStylePtr fillStyle, ILineStylePtr lineStyle)
	: m_frame(frame)
	, m_lineStyle{ std::move(lineStyle) }
	, m_fillStyle{ std::move(fillStyle) }
{
}

CShape::CShape(const CShape& other)
	: m_frame(other.m_frame)
	, m_fillStyle(other.m_fillStyle->Clone())
	, m_lineStyle(other.m_lineStyle->Clone())
{
}

RectD CShape::GetFrame() const
{
	return m_frame;
}

void CShape::SetFrame(const RectD& rect)
{
	m_frame = rect;
}

ILineStylePtr CShape::GetLineStyle() const
{
	return m_lineStyle;
}

void CShape::SetLineStyle(const ILineStylePtr& style)
{
	m_lineStyle = style;
}

IFillStylePtr CShape::GetFillStyle() const
{
	return m_fillStyle;
}

void CShape::SetFillStyle(const IFillStylePtr& style)
{
	m_fillStyle = style;
}

IGroupPtr CShape::GetGroup()
{
	return nullptr;
}

void CShape::Draw(ICanvas& canvas) const
{
	constexpr auto TRANSPARENT_COLOR = MakeColorRGBA(0, 0, 0, 0);

	const bool fillEnabled = m_fillStyle && m_fillStyle->IsEnabled();

	if (fillEnabled)
	{
		canvas.BeginFill(m_fillStyle->GetColor());
	}

	if (m_lineStyle && m_lineStyle->IsEnabled())
	{
		canvas.SetLineColor(m_lineStyle->GetColor());
		canvas.SetLineWidth(m_lineStyle->GetWidth());
	}
	else
	{
		canvas.SetLineColor(TRANSPARENT_COLOR);
		canvas.SetLineWidth(0.f);
	}

	DrawBehavior(canvas);

	if (fillEnabled)
	{
		canvas.EndFill();
	}
}
