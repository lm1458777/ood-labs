#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const RectD& frame, const IStylePtr& fillStyle, const IStylePtr& lineStyle);

private:
	void DrawBehavior(ICanvas& canvas) const override;
};
