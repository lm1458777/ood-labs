#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const RectD& frame, const IFillStylePtr& fillStyle, const ILineStylePtr& lineStyle);

private:
	void DrawBehavior(ICanvas& canvas) const override;
};
