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

bool operator==(const ILineStyle& style1, const ILineStyle& style2);

inline bool operator==(const ILineStylePtr& style1, const ILineStylePtr& style2)
{
	return style1 && style2 && *style1 == *style2;
}

class IFillStyle : public IBaseStyle
{
public:
	virtual IFillStylePtr Clone() const = 0;
};

class ILineStyle : public IBaseStyle
{
public:
	virtual ILineStyleUniquePtr Clone() const = 0;

	virtual float GetWidth() const = 0;
	virtual void SetWidth(float width) = 0;
};

bool operator==(const IFillStyle& style1, const IFillStyle& style2);

inline bool operator==(const IFillStylePtr& style1, const IFillStylePtr& style2)
{
	return style1 && style2 && *style1 == *style2;
}

