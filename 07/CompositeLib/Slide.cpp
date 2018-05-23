#include "stdafx.h"
#include "Slide.h"
#include "Group.h"
#include "Rectangle.h"
#include "Style.h"

using std::make_shared;

CSlide::CSlide()
	: m_shapes{ make_shared<CGroup>() }
	, m_backgroundFillStyle{ make_shared<CStyle>(true, 0) }
{
	auto bgRect = make_shared<CRectangle>(
		RectD{ 0, 0, 400, 300 },
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
