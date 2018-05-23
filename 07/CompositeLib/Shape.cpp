#include "stdafx.h"
#include "Shape.h"
#include "ICanvas.h"

CShape::CShape(const RectD& frame, IStylePtr fillStyle, IStylePtr lineStyle)
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

IStylePtr CShape::GetLineStyle() const
{
	return m_lineStyle;
}

void CShape::SetLineStyle(const IStylePtr& style)
{
	m_lineStyle = style;
}

IStylePtr CShape::GetFillStyle() const
{
	return m_fillStyle;
}

void CShape::SetFillStyle(const IStylePtr& style)
{
	m_fillStyle = style;
}

IGroupPtr CShape::GetGroup()
{
	return nullptr;
}

void CShape::Draw(ICanvas& canvas) const
{
	const bool fillEnabled = m_fillStyle && m_fillStyle->IsEnabled();

	if (fillEnabled)
	{
		canvas.BeginFill(m_fillStyle->GetColor());
	}

	const auto lineColor = m_lineStyle && m_lineStyle->IsEnabled() ? m_lineStyle->GetColor() : 0;
	canvas.SetLineColor(lineColor);

	DrawBehavior(canvas);

	if (fillEnabled)
	{
		canvas.EndFill();
	}
}
