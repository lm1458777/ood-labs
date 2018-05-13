#include "stdafx.h"
#include "CanvasAdapter.h"
#include "ColorUtils.h"

using namespace modern_graphics_lib;

namespace
{

CanvasAdapter::LinePainter CreateLinePainter(CModernGraphicsRenderer& renderer)
{
	return [&renderer](const CPoint& start, const CPoint& end, const CRGBAColor& color) {
		renderer.DrawLine(start, end, color);
	};
}

} // namespace

CanvasAdapter::CanvasAdapter(CModernGraphicsRenderer& renderer)
	: m_linePainter{ CreateLinePainter(renderer) }
{
}

CanvasAdapter::CanvasAdapter(LinePainter linePainter)
	: m_linePainter(std::move(linePainter))
{
}

void CanvasAdapter::SetColor(uint32_t rgbColor)
{
	auto r = GetRedValue(rgbColor) / 255.f;
	auto g = GetGreenValue(rgbColor) / 255.f;
	auto b = GetBlueValue(rgbColor) / 255.f;
	m_color.emplace(r, g, b, 1.f);
}

void CanvasAdapter::MoveTo(int x, int y)
{
	m_currentPos.emplace(x, y);
}

void CanvasAdapter::LineTo(int x, int y)
{
	CPoint ptEnd{ x, y };
	m_linePainter(m_currentPos.value(), ptEnd, m_color.value());
	m_currentPos = ptEnd;
}
