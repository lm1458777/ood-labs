#include "stdafx.h"
#include "Shape.h"
#include "ColorUtils.h"
#include "ICanvas.h"

CShape::CShape(const RectD& frame, IFillStylePtr fillStyle, ILineStylePtr lineStyle)
	: m_frame(frame)
	, m_lineStyle{ std::move(lineStyle) }
	, m_fillStyle{ std::move(fillStyle) }
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

	const auto lineColor = m_lineStyle && m_lineStyle->IsEnabled() ? m_lineStyle->GetColor() : TRANSPARENT_COLOR;
	canvas.SetLineColor(lineColor);

	DrawBehavior(canvas);

	if (fillEnabled)
	{
		canvas.EndFill();
	}
}
