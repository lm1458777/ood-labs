#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(const RectD& frame, IFillStylePtr fillStyle, ILineStylePtr lineStyle);
	CShape(const CShape& other);

	CShape& operator=(const CShape&) = delete;

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	ILineStylePtr GetLineStyle() const override;
	void SetLineStyle(const ILineStylePtr& style) override;

	IFillStylePtr GetFillStyle() const override;
	void SetFillStyle(const IFillStylePtr& style) override;

	IGroupPtr GetGroup() override;

	void Draw(ICanvas& canvas) const override;

private:
	virtual void DrawBehavior(ICanvas& canvas) const = 0;

private:
	RectD m_frame;
	IFillStylePtr m_fillStyle;
	ILineStylePtr m_lineStyle;
};
