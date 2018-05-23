#pragma once
#include "CommonTypes.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void BeginFill(RGBAColor color) = 0;
	virtual void EndFill() = 0;
	virtual void DrawEllipse(const RectD& bounds) = 0;
	virtual void DrawPoligon(gsl::span<const PointD> points) = 0;
};
