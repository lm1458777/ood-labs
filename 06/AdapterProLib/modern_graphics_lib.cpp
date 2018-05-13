#include "stdafx.h"
#include "modern_graphics_lib.h"
#include <boost/format.hpp>
#include <iostream>

using namespace std;

namespace modern_graphics_lib
{

CModernGraphicsRenderer::CModernGraphicsRenderer(ostream& strm)
	: m_out(strm)
{
}

CModernGraphicsRenderer::~CModernGraphicsRenderer()
{
	if (m_drawing) // ��������� ���������, ���� ��� ���� ������
	{
		EndDraw();
	}
}

void CModernGraphicsRenderer::BeginDraw()
{
	if (m_drawing)
	{
		throw logic_error("Drawing has already begun");
	}
	m_out << "<draw>" << endl;
	m_drawing = true;
}

void CModernGraphicsRenderer::DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
{
	if (!m_drawing)
	{
		throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}

	m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)") % start.x % start.y % end.x % end.y << endl;
	m_out << boost::format(R"(    <color r="%1$.2f" g="%2$.2f" b="%3$.2f" a="%4$.2f" />)") % color.r % color.g % color.b % color.a << endl;
	m_out << R"(  </line>)" << endl;
}

void CModernGraphicsRenderer::EndDraw()
{
	if (!m_drawing)
	{
		throw logic_error("Drawing has not been started");
	}
	m_out << "</draw>" << endl;
	m_drawing = false;
}

} // namespace modern_graphics_lib
