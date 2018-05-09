#include "stdafx.h"
#include "app.h"
#include "shape_drawing_lib.h"
#include <iostream>
#include "CanvasAdapter.h"

namespace app
{

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
