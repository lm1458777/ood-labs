#include "stdafx.h"
#include "ShapeFactory.h"
#include "Group.h"
#include "ICanvas.h"
#include "Shape.h"

namespace
{

void DrawRectangle(const RectD& frame, ICanvas& canvas)
{
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

void DrawTriangle(const RectD& frame, ICanvas& canvas)
{
	auto right = frame.GetRight();
	auto bottom = frame.GetBottom();
	const PointD vertices[] = {
		{ frame.left, frame.top },
		{ right, frame.top + frame.height / 2 },
		{ frame.left, bottom },
	};
	canvas.DrawPoligon(vertices);
}

void DrawEllipse(const RectD& frame, ICanvas& canvas)
{
	canvas.DrawEllipse(frame);
}

} // namespace

IShapePtr CreateRectangle(const RectD& frame, const FillStyle& fillStyle, const LineStyle& lineStyle)
{
	return std::make_shared<CSimpleShape>(frame, fillStyle, lineStyle, &DrawRectangle);
}

IShapePtr CreateTriangle(const RectD& frame, const FillStyle& fillStyle, const LineStyle& lineStyle)
{
	return std::make_shared<CSimpleShape>(frame, fillStyle, lineStyle, &DrawTriangle);
}

IShapePtr CreateEllipse(const RectD& frame, const FillStyle& fillStyle, const LineStyle& lineStyle)
{
	return std::make_shared<CSimpleShape>(frame, fillStyle, lineStyle, &DrawEllipse);
}

IGroupPtr CreateGroup()
{
	return CGroup::Create();
}
