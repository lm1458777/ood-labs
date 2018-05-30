#include "stdafx.h"
#include "Slide.h"
#include "ColorUtils.h"
#include "IShape.h"
#include "ShapeFactory.h"
#include "ShapeRange.h"
#include "Shapes.h"
#include "StyleFactory.h"

CSlide::CSlide(double width, double height)
	: m_background{ CreateRectangle(
		  RectD{ 0, 0, width, height },
		  CreateFillStyle(WHITE_COLOR),
		  CreateNoLineStyle()) }
	, m_shapes{ std::make_unique<Shapes>() }
{
}

CSlide::~CSlide() = default;

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_background->GetFillStyle().SetColor(color);
}

void CSlide::AddShape(const IShapePtr& shape)
{
	::AddShape(*m_shapes, shape);
}

void CSlide::Draw(ICanvas& canvas) const
{
	m_background->Draw(canvas);

	boost::for_each(GetShapeRange(*m_shapes), [&canvas](const IShapePtr& shape) {
		shape->Draw(canvas);
	});
}
