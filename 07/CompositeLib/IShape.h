#pragma once
#include "CommonTypes.h"
#include "IGroup_fwd.h"
#include "IShape_fwd.h"
#include "IStyle.h"

class ICanvas;

class IShape
{
public:
	virtual ~IShape() = default;

	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual IStylePtr GetLineStyle() const = 0;
	virtual void SetLineStyle(const IStylePtr& style) = 0;

	virtual IStylePtr GetFillStyle() const = 0;
	virtual void SetFillStyle(const IStylePtr& style) = 0;

	virtual void Draw(ICanvas& canvas) const = 0;

	virtual IGroupPtr GetGroup() = 0;
};
