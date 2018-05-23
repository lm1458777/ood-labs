#include "stdafx.h"
#include "Slide.h"
#include "ColorUtils.h"
#include "IGroup.h"
#include "IStyle.h"
#include "ShapeFactory.h"
#include "StyleFactory.h"

CSlide::CSlide(double width, double height)
	: m_shapes{ CreateGroup() }
	, m_backgroundFillStyle{ CreateFillStyle(MakeColorRGB(0xff, 0xff, 0xff)) }
{
	auto bgRect = CreateRectangle(
		RectD{ 0, 0, width, height },
		m_backgroundFillStyle,
		nullptr);
	AddShape(bgRect);
}

CSlide::~CSlide() = default;

RGBAColor CSlide::GetBackgroundColor() const
{
	return m_backgroundFillStyle->GetColor();
}

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_backgroundFillStyle->SetColor(color);
}

void CSlide::AddShape(const IShapePtr& shape)
{
	::AddShape(*m_shapes, shape);
}

void CSlide::Draw(ICanvas& canvas) const
{
	m_shapes->Draw(canvas);
}
