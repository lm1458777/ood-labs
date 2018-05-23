#include "stdafx.h"
#include "Rectangle.h"
#include "ICanvas.h"

CRectangle::CRectangle(const RectD& frame, const IStylePtr& fillStyle, const IStylePtr& lineStyle)
	: CShape(frame, fillStyle, lineStyle)
{
}

void CRectangle::DrawBehavior(ICanvas& canvas) const
{
	auto frame = GetFrame();
	auto right = frame.GetRight();
	auto bottom = frame.GetBottom();
	const PointD vertices[] = {
		{ frame.left, frame.top },
		{ right, frame.top },
		{ right, bottom },
		{ frame.left, bottom },
	};
	canvas.DrawPoligon(vertices);
}
