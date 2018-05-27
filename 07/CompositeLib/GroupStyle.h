#pragma once
#include "IStyle.h"

using FillStyleRange = boost::any_range<
	IFillStyle,
	boost::forward_traversal_tag>;

class GroupFillStyle : public IFillStyle
{
public:
	using StyleEnumerator = std::function<FillStyleRange()>;

	explicit GroupFillStyle(StyleEnumerator styleEnumerator);

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	StyleEnumerator m_styleEnumerator;
};

using LineStyleRange = boost::any_range<
	ILineStyle,
	boost::forward_traversal_tag>;

class GroupLineStyle : public ILineStyle
{
public:
	using StyleEnumerator = std::function<LineStyleRange()>;

	explicit GroupLineStyle(StyleEnumerator styleEnumerator);

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	boost::optional<float> GetWidth() const override;
	void SetWidth(float width) override;

private:
	StyleEnumerator m_styleEnumerator;
};
