#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include <boost/optional.hpp>
#include <iosfwd>

class CanvasClassAdapter
	: public graphics_lib::ICanvas
	, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	explicit CanvasClassAdapter(std::ostream& strm);

	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;

private:
	boost::optional<modern_graphics_lib::CPoint> m_currentPos;
};
