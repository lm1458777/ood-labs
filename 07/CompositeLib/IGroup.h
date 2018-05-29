#pragma once
#include "IGroup_fwd.h"
#include "IShape.h"
#include "IShapes.h"

class IGroup
	: public IShape
	, public IShapes
{
};
