#include "stdafx.h"
#include "shape_drawing_lib.h"
#include "graphics_lib.h"

namespace shape_drawing_lib
{

static inline void MoveTo(graphics_lib::ICanvas& canvas, Point pt)
{
	canvas.MoveTo(pt.x, pt.y);
}

static inline void LineTo(graphics_lib::ICanvas& canvas, Point pt)
{
	canvas.LineTo(pt.x, pt.y);
}

static inline void Normalize(int& left, int& right)
{
	if (left > right)
	{
		std::swap(left, right);
	}
}

CTriangle::CTriangle(const Point& p1, const Point& p2, const Point& p3, Color color)
	: m_points{ p1, p2, p3 }
	, m_color(color)
{
}

void CTriangle::Draw(graphics_lib::ICanvas& canvas) const
{
	canvas.SetColor(m_color);

	MoveTo(canvas, m_points[0]);

	LineTo(canvas, m_points[1]);
	LineTo(canvas, m_points[2]);
	LineTo(canvas, m_points[0]);
}

CRectangle::CRectangle(const Point& leftTop, int width, int height, Color color)
	: m_leftTop(leftTop)
	, m_rightBottom{ leftTop.x + width, leftTop.y + height }
	, m_color(color)
{
	Normalize(m_leftTop.x, m_rightBottom.x);
	Normalize(m_leftTop.y, m_rightBottom.y);
}

void CRectangle::Draw(graphics_lib::ICanvas& canvas) const
{
	canvas.SetColor(m_color);

	MoveTo(canvas, m_leftTop);

	canvas.LineTo(m_rightBottom.x, m_leftTop.y);
	LineTo(canvas, m_rightBottom);
	canvas.LineTo(m_leftTop.x, m_rightBottom.y);
	LineTo(canvas, m_leftTop);
}

CCanvasPainter::CCanvasPainter(graphics_lib::ICanvas& canvas)
	: m_canvas(canvas)
{
}

void CCanvasPainter::Draw(const ICanvasDrawable& drawable)
{
	drawable.Draw(m_canvas);
}

} // namespace shape_drawing_lib
