#pragma once

#include "../CompositeLib/ICanvas.h"

class GdiCanvas final : public ICanvas
{
public:
	explicit GdiCanvas(CDCHandle dc);

	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double left, double top, double width, double height) override;
	void DrawPoligon(gsl::span<const PointD> points) override;

private:
	CDCHandle m_dc;
	boost::optional<RGBAColor> m_fillColor;
};
