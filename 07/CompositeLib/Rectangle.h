#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const RectD& frame, const IFillStylePtr& fillStyle, const ILineStylePtr& lineStyle);

	IShapeUniquePtr Clone() const override;

private:
	void DrawBehavior(ICanvas& canvas) const override;
};
