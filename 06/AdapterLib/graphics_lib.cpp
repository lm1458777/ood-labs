#include "stdafx.h"
#include "graphics_lib.h"
#include <iostream>

using std::cout;
using std::endl;

namespace graphics_lib
{

void CCanvas::MoveTo(int x, int y)
{
	cout << "MoveTo (" << x << ", " << y << ")" << endl;
}

void CCanvas::LineTo(int x, int y)
{
	cout << "LineTo (" << x << ", " << y << ")" << endl;
}

} // namespace graphics_lib
