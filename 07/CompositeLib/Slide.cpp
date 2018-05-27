#include "stdafx.h"
#include "Slide.h"
#include "ColorUtils.h"
#include "IGroup.h"
#include "ShapeFactory.h"
#include "StyleFactory.h"

CSlide::CSlide(double width, double height)
	: m_shapes{ CreateGroup() }
{
	auto bgRect = CreateRectangle(
		RectD{ 0, 0, width, height },
		CreateFillStyle(WHITE_COLOR),
		CreateNoLineStyle());
	AddShape(bgRect);
}

CSlide::~CSlide() = default;

RGBAColor CSlide::GetBackgroundColor() const
{
	return m_shapes->GetShapeAtIndex(0)->GetFillStyle().GetColor().value();
}

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_shapes->GetShapeAtIndex(0)->GetFillStyle().SetColor(color);
}

void CSlide::AddShape(const IShapePtr& shape)
{
	::AddShape(*m_shapes, shape);
}

void CSlide::Draw(ICanvas& canvas) const
{
	m_shapes->Draw(canvas);
}
