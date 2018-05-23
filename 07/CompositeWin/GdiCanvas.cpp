#include "stdafx.h"
#include "GdiCanvas.h"

using namespace boost;
using std::vector;

GdiCanvas::GdiCanvas(CDCHandle dc)
	: m_dc(dc)
{
}

void GdiCanvas::DrawEllipse(double left, double top, double width, double height)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GdiCanvas::LineTo(double x, double y)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GdiCanvas::MoveTo(double x, double y)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GdiCanvas::EndFill()
{
	m_fillColor.reset();
}

void GdiCanvas::BeginFill(RGBAColor color)
{
	m_fillColor = color;
}

void GdiCanvas::SetLineColor(RGBAColor color)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void GdiCanvas::DrawPoligon(gsl::span<const PointD> points)
{
	auto toPoint = [](PointD pt) {
		return POINT{ gsl::narrow_cast<LONG>(pt.x), gsl::narrow_cast<LONG>(pt.y) };
	};

	const auto vertices = copy_range<vector<POINT>>(points | adaptors::transformed(toPoint));

	CBrush brush;
	brush.CreateSolidBrush(RGB(0x80, 0xff, 0x80));
	auto oldBrush = m_dc.SelectBrush(brush);
	m_dc.Polygon(vertices.data(), gsl::narrow<int>(vertices.size()));
	m_dc.SelectBrush(oldBrush);
}
