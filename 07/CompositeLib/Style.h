#pragma once
#include "IStyle.h"

class CStyle : public IStyle
{
public:
	CStyle(bool enable, RGBAColor color);

	bool IsEnabled() const override;
	void Enable(bool enable) override;

	RGBAColor GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	bool m_isEnabled = false;
	RGBAColor m_color = 0;
};
