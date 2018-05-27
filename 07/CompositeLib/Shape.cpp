#include "stdafx.h"
#include "Shape.h"
#include "ColorUtils.h"
#include "ICanvas.h"

namespace
{
constexpr auto TRANSPARENT_COLOR = MakeColorRGBA(0, 0, 0, 0);

std::pair<RGBAColor, float> GetCanvasLineStyle(const ILineStyle& lineStyle)
{
	if (lineStyle.IsEnabled() == true)
	{
		auto colorOpt = lineStyle.GetColor();
		if (colorOpt)
		{
			auto widthOpt = lineStyle.GetWidth();
			if (widthOpt)
			{
				return { *colorOpt, *widthOpt };
			}
		}
	}

	return { TRANSPARENT_COLOR, 0.f };
}

} // namespace

CSimpleShape::CSimpleShape(const RectD& frame, const FillStyle& fillStyle, const LineStyle& lineStyle, DrawBehavior drawBehavior)
	: m_frame(frame)
	, m_fillStyle(fillStyle)
	, m_lineStyle(lineStyle)
	, m_drawBehavior{ std::move(drawBehavior) }
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

ILineStyle& CSimpleShape::GetLineStyle()
{
	return m_lineStyle;
}

const ILineStyle& CSimpleShape::GetLineStyle() const
{
	return m_lineStyle;
}

IFillStyle& CSimpleShape::GetFillStyle()
{
	return m_fillStyle;
}

const IFillStyle& CSimpleShape::GetFillStyle() const
{
	return m_fillStyle;
}

IGroupPtr CSimpleShape::GetGroup()
{
	return nullptr;
}

void CSimpleShape::Draw(ICanvas& canvas) const
{
	const auto fillColorOpt = m_fillStyle.IsEnabled() == true ? m_fillStyle.GetColor() : boost::none;

	if (fillColorOpt)
	{
		canvas.BeginFill(*fillColorOpt);
	}

	{
		RGBAColor color;
		float width;
		std::tie(color, width) = GetCanvasLineStyle(m_lineStyle);
		canvas.SetLineColor(color);
		canvas.SetLineWidth(width);
	}

	m_drawBehavior(m_frame, canvas);

	if (fillColorOpt)
	{
		canvas.EndFill();
	}
}

IShapePtr CSimpleShape::Clone() const
{
	return std::make_shared<CSimpleShape>(*this);
}
