#pragma once
#include "IImage_fwd.h"
#include "Path.h"
#include "Size.h"

class IImage
{
public:
	virtual ~IImage() = default;

	virtual Path GetPath() const = 0;

	virtual unsigned GetWidth() const = 0;
	virtual unsigned GetHeight() const = 0;

	virtual void Resize(Size newSize) = 0;
};
