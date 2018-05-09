#include "stdafx.h"
#include "app.h"
#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"
#include <boost/optional.hpp>
#include <iostream>

namespace app
{

class CanvasAdapter : public graphics_lib::ICanvas
{
public:
	CanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
		: m_renderer(renderer)
	{
	}

	void MoveTo(int x, int y) override
	{
		m_currentPos.emplace(x, y);
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint ptEnd{ x, y };
		m_renderer.DrawLine(m_currentPos.value(), ptEnd);
		m_currentPos = ptEnd;
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	boost::optional<modern_graphics_lib::CPoint> m_currentPos;
};

void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	CRectangle rectangle({ 30, 40 }, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
	CanvasAdapter canvasAdapter(renderer);
	shape_drawing_lib::CCanvasPainter painter(canvasAdapter);
	renderer.BeginDraw();
	PaintPicture(painter);
}

} // namespace app
