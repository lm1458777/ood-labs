#pragma once
#include "IStyle.h"

template <class T>
class IBaseStyleImpl : public T
{
public:
	bool IsEnabled() const override
	{
		return m_isEnabled;
	}

	void Enable(bool enable) override
	{
		m_isEnabled = enable;
	}

	RGBAColor GetColor() const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

protected:
	IBaseStyleImpl(RGBAColor color, bool enable)
		: m_isEnabled(enable)
		, m_color(color)
	{
	}

private:
	bool m_isEnabled = false;
	RGBAColor m_color = 0;
};

class FillStyle final : public IBaseStyleImpl<IFillStyle>
{
public:
	FillStyle(RGBAColor color, bool enable = true);
	IFillStylePtr Clone() const override;
};

class LineStyle final : public IBaseStyleImpl<ILineStyle>
{
public:
	LineStyle(RGBAColor color, float width, bool enable = true);

	float GetWidth() const override;
	void SetWidth(float width) override;

	virtual ILineStyleUniquePtr Clone() const override;

private:
	float m_width = 1.f;
};
