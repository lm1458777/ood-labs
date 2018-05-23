#pragma once
#include "CommonTypes.h"
#include "IStyle_fwd.h"

class IBaseStyle
{
public:
	virtual ~IBaseStyle() = default;

	virtual bool IsEnabled() const = 0;
	virtual void Enable(bool enable) = 0;

	virtual RGBAColor GetColor() const = 0;
	virtual void SetColor(RGBAColor color) = 0;
};

class IFillStyle : public IBaseStyle
{
};

class ILineStyle : public IBaseStyle
{
public:
	virtual float GetWidth() const = 0;
	virtual void SetWidth(float width) = 0;
};
