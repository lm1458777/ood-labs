#pragma once
#include "CommonTypes.h"
#include "IShape_fwd.h"

class ICanvas;
class IShapes;

class CSlide
{
public:
	CSlide(double width, double height);
	~CSlide();

	void SetBackgroundColor(RGBAColor color);

	void AddShape(const IShapePtr& shape);
	void Draw(ICanvas& canvas) const;

private:
	IShapePtr m_background;
	std::unique_ptr<IShapes> m_shapes;
};
