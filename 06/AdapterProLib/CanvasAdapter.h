#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include <boost/optional.hpp>

class CanvasAdapter : public graphics_lib::ICanvas
{
public:
	using LinePainter = std::function<void(
		const modern_graphics_lib::CPoint&,
		const modern_graphics_lib::CPoint&,
		const modern_graphics_lib::CRGBAColor& color)>;
	explicit CanvasAdapter(LinePainter linePainter);

	explicit CanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer);

	void SetColor(uint32_t rgbColor) override;
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;

private:
	LinePainter m_linePainter;
	boost::optional<modern_graphics_lib::CPoint> m_currentPos;
	boost::optional<modern_graphics_lib::CRGBAColor> m_color;
};
