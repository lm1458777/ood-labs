#pragma once
#include "CommonTypes.h"
#include "IStyle_fwd.h"

class IBaseStyle
{
public:
	virtual ~IBaseStyle() = default;

	virtual boost::optional<bool> IsEnabled() const = 0;
	virtual void Enable(bool enable) = 0;

	virtual boost::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(RGBAColor color) = 0;
};

class IFillStyle : public IBaseStyle
{
};

void CopyValues(IFillStyle& dest, const IFillStyle& src);

class ILineStyle : public IBaseStyle
{
public:
	virtual boost::optional<float> GetWidth() const = 0;
	virtual void SetWidth(float width) = 0;
};

void CopyValues(ILineStyle& dest, const ILineStyle& src);
