#pragma once
#include "IShape.h"
#include "Style.h"

using DrawBehavior = std::function<void(const RectD& frame, ICanvas& canvas)>;

class CSimpleShape : public IShape
{
public:
	CSimpleShape(const RectD& frame, const FillStyle& fillStyle, const LineStyle& lineStyle, DrawBehavior drawBehavior);

	IShapePtr Clone() const override;

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	ILineStyle& GetLineStyle() override;
	const ILineStyle& GetLineStyle() const override;

	IFillStyle& GetFillStyle() override;
	const IFillStyle& GetFillStyle() const override;

	IGroupPtr GetGroup() override;

	void Draw(ICanvas& canvas) const override;

private:
	RectD m_frame;
	FillStyle m_fillStyle;
	LineStyle m_lineStyle;
	DrawBehavior m_drawBehavior;
};
