#include "stdafx.h"
#include "Shape.h"
#include "ColorUtils.h"
#include "ICanvas.h"
#include "IStyle.h"

CSimpleShape::CSimpleShape(const RectD& frame, IFillStylePtr fillStyle, ILineStylePtr lineStyle, DrawBehavior drawBehavior)
	: m_frame(frame)
	, m_lineStyle{ std::move(lineStyle) }
	, m_fillStyle{ std::move(fillStyle) }
	, m_drawBehavior{ std::move(drawBehavior) }
{
}

CSimpleShape::CSimpleShape(const CSimpleShape& other)
	: m_frame(other.m_frame)
	, m_fillStyle(other.m_fillStyle->Clone())
	, m_lineStyle(other.m_lineStyle->Clone())
	, m_drawBehavior(other.m_drawBehavior)
{
}

RectD CSimpleShape::GetFrame() const
{
	return m_frame;
}

void CSimpleShape::SetFrame(const RectD& rect)
{
	m_frame = rect;
}

ILineStylePtr CSimpleShape::GetLineStyle() const
{
	return m_lineStyle;
}

void CSimpleShape::SetLineStyle(const ILineStylePtr& style)
{
	m_lineStyle = style;
}

IFillStylePtr CSimpleShape::GetFillStyle() const
{
	return m_fillStyle;
}

void CSimpleShape::SetFillStyle(const IFillStylePtr& style)
{
	m_fillStyle = style;
}

IGroupPtr CSimpleShape::GetGroup()
{
	return nullptr;
}

void CSimpleShape::Draw(ICanvas& canvas) const
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

	m_drawBehavior(m_frame, canvas);

	if (fillEnabled)
	{
		canvas.EndFill();
	}
}

IShapePtr CSimpleShape::Clone() const
{
	return std::make_shared<CSimpleShape>(*this);
}
