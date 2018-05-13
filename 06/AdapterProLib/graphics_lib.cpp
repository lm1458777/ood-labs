#include "stdafx.h"
#include "graphics_lib.h"
#include "ColorUtils.h"

using namespace std;

namespace graphics_lib
{

void CCanvas::SetColor(uint32_t rgbColor)
{
	boost::io::ios_flags_saver ifs(cout);
	cout << "SetColor (#" << hex << setw(6) << setfill('0') << rgbColor << ")" << endl;
}

void CCanvas::MoveTo(int x, int y)
{
	cout << "MoveTo (" << x << ", " << y << ")" << endl;
}

void CCanvas::LineTo(int x, int y)
{
	cout << "LineTo (" << x << ", " << y << ")" << endl;
}

} // namespace graphics_lib
