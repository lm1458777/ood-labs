#pragma once
#include "CommonTypes.h"
#include "IGroup_fwd.h"
#include "IShape_fwd.h"
#include "IStyle_fwd.h"

class ICanvas;

class CSlide
{
public:
	CSlide(double width, double height);
	~CSlide();

	RGBAColor GetBackgroundColor() const;
	void SetBackgroundColor(RGBAColor color);

	void AddShape(const IShapePtr& shape);
	void Draw(ICanvas& canvas) const;

private:
	IGroupPtr m_shapes;
	IFillStylePtr m_backgroundFillStyle;
};
