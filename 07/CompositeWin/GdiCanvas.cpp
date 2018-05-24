#include "stdafx.h"
#include "GdiCanvas.h"
#include "../CompositeLib/ColorUtils.h"

using namespace Gdiplus;
using namespace boost;
using std::vector;

namespace
{

auto ToGdiplusColor(RGBAColor rgba)
{
	return Gdiplus::Color::MakeARGB(
		GetAlphaValue(rgba),
		GetRedValue(rgba),
		GetGreenValue(rgba),
		GetBlueValue(rgba));
}

auto CastToPointF(gsl::span<const PointD> points)
{
	auto toPoint = [](PointD pt) {
		return PointF{ gsl::narrow_cast<REAL>(pt.x), gsl::narrow_cast<REAL>(pt.y) };
	};

	return copy_range<vector<PointF>>(points | adaptors::transformed(toPoint));
}

auto CastToRectF(const RectD& r)
{
	return Gdiplus::RectF{
		gsl::narrow_cast<REAL>(r.left),
		gsl::narrow_cast<REAL>(r.top),
		gsl::narrow_cast<REAL>(r.width),
		gsl::narrow_cast<REAL>(r.height)
	};
}

void VerifyStatus(Status st)
{
	ATLVERIFY(Status::Ok == st);
}

} // namespace

GdiCanvas::GdiCanvas(CDCHandle dc)
	: m_graphics(dc)
	, m_pen(static_cast<ARGB>(Color::Black))
{
	VerifyStatus(m_pen.SetAlignment(PenAlignmentInset));
	VerifyStatus(m_graphics.SetInterpolationMode(InterpolationModeHighQuality));
}

void GdiCanvas::DrawEllipse(const RectD& bounds)
{
	const auto frame = CastToRectF(bounds);

	if (m_brush)
	{
		VerifyStatus(m_graphics.FillEllipse(m_brush.get_ptr(), frame));
	}

	VerifyStatus(m_graphics.DrawEllipse(&m_pen, frame));
}

void GdiCanvas::EndFill()
{
	m_brush.reset();
}

void GdiCanvas::BeginFill(RGBAColor color)
{
	m_brush.emplace(ToGdiplusColor(color));
}

void GdiCanvas::SetLineColor(RGBAColor color)
{
	VerifyStatus(m_pen.SetColor(ToGdiplusColor(color)));
}

void GdiCanvas::DrawPoligon(gsl::span<const PointD> points)
{
	const auto vertices = CastToPointF(points);
	const auto verticesCount = gsl::narrow<int>(vertices.size());

	if (m_brush)
	{
		VerifyStatus(m_graphics.FillPolygon(m_brush.get_ptr(), vertices.data(), verticesCount));
	}

	VerifyStatus(m_graphics.DrawPolygon(&m_pen, vertices.data(), verticesCount));
}

void GdiCanvas::SetLineWidth(float width)
{
	m_pen.SetWidth(width);
}
