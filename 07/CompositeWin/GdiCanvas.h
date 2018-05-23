#pragma once

#include "../CompositeLib/ICanvas.h"

class GdiCanvas final : public ICanvas
{
public:
	explicit GdiCanvas(CDCHandle dc);

	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void DrawEllipse(const RectD& bounds) override;
	void DrawPoligon(gsl::span<const PointD> points) override;

private:
	Gdiplus::Graphics m_graphics;
	boost::optional<Gdiplus::SolidBrush> m_brush;
	Gdiplus::Pen m_pen;
};
