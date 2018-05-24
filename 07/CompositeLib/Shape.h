#pragma once
#include "IShape.h"

using DrawBehavior = std::function<void(const RectD& frame, ICanvas& canvas)>;

class CSimpleShape : public IShape
{
public:
	CSimpleShape(const RectD& frame, IFillStylePtr fillStyle, ILineStylePtr lineStyle, DrawBehavior drawBehavior);
	CSimpleShape(const CSimpleShape& other);
	CSimpleShape(CSimpleShape&&) = default;

	CSimpleShape& operator=(const CSimpleShape&) = delete;
	CSimpleShape& operator=(CSimpleShape&&) = default;

	IShapePtr Clone() const override;

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	ILineStylePtr GetLineStyle() const override;
	void SetLineStyle(const ILineStylePtr& style) override;

	IFillStylePtr GetFillStyle() const override;
	void SetFillStyle(const IFillStylePtr& style) override;

	IGroupPtr GetGroup() override;

	void Draw(ICanvas& canvas) const override;

private:
	RectD m_frame;
	IFillStylePtr m_fillStyle;
	ILineStylePtr m_lineStyle;
	DrawBehavior m_drawBehavior;
};
