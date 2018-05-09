#include "stdafx.h"
#include "CanvasAdapter.h"

using namespace modern_graphics_lib;

namespace
{

CanvasAdapter::LinePainter CreateLinePainter(CModernGraphicsRenderer& renderer)
{
	return [&renderer](const CPoint& start, const CPoint& end) {
		renderer.DrawLine(start, end);
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

void CanvasAdapter::MoveTo(int x, int y)
{
	m_currentPos.emplace(x, y);
}

void CanvasAdapter::LineTo(int x, int y)
{
	CPoint ptEnd{ x, y };
	m_linePainter(m_currentPos.value(), ptEnd);
	m_currentPos = ptEnd;
}
