#pragma once
#include "CommonTypes.h"
#include "IGroup_fwd.h"
#include "IShape_fwd.h"
#include "IStyle_fwd.h"

class ICanvas;

class IShape
{
public:
	virtual ~IShape() = default;

	virtual IShapePtr Clone() const = 0;

	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual ILineStyle& GetLineStyle() = 0;
	virtual const ILineStyle& GetLineStyle() const = 0;

	virtual IFillStyle& GetFillStyle() = 0;
	virtual const IFillStyle& GetFillStyle() const = 0;

	virtual void Draw(ICanvas& canvas) const = 0;

	virtual IGroupPtr GetGroup() = 0;
};
