#include "stdafx.h"
#include "CanvasClassAdapter.h"

using namespace modern_graphics_lib;

CanvasClassAdapter::CanvasClassAdapter(std::ostream& strm)
	: CModernGraphicsRenderer(strm)
{
	BeginDraw();
}

void CanvasClassAdapter::MoveTo(int x, int y)
{
	m_currentPos.emplace(x, y);
}

void CanvasClassAdapter::LineTo(int x, int y)
{
	CPoint ptEnd{ x, y };
	DrawLine(m_currentPos.value(), ptEnd);
	m_currentPos = ptEnd;
}
