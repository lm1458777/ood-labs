#pragma once
#include "CommonTypes.h"
#include "IStyle_fwd.h"

class IStyle
{
public:
	virtual ~IStyle() = default;

	virtual bool IsEnabled() const = 0;
	virtual void Enable(bool enable) = 0;

	virtual RGBAColor GetColor() const = 0;
	virtual void SetColor(RGBAColor color) = 0;
};
