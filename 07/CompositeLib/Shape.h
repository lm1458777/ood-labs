#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(const RectD& frame, IStylePtr fillStyle, IStylePtr lineStyle);

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	IStylePtr GetLineStyle() const override;
	void SetLineStyle(const IStylePtr& style) override;

	IStylePtr GetFillStyle() const override;
	void SetFillStyle(const IStylePtr& style) override;

	IGroupPtr GetGroup() override;

	void Draw(ICanvas& canvas) const override;

private:
	virtual void DrawBehavior(ICanvas& canvas) const = 0;

private:
	RectD m_frame;
	IStylePtr m_fillStyle;
	IStylePtr m_lineStyle;
};
