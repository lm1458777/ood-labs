#include "stdafx.h"
#include "../AdapterLib/CanvasClassAdapter.h"
#include <sstream>

SCENARIO("A CanvasAdapter test")
{
	GIVEN("a CanvasAdapter")
	{
		using modern_graphics_lib::CPoint;

		std::ostringstream ss;
		CanvasClassAdapter canvasAdapter{ ss };
		ss.str({});

		WHEN("we draw a line")
		{
			constexpr CPoint start(1, 2);
			constexpr CPoint end(3, 4);

			canvasAdapter.MoveTo(start.x, start.y);
			canvasAdapter.LineTo(end.x, end.y);

			THEN("the line is drawn")
			{
				const std::string ExpectedOut = R"(  <line fromX="1" fromY="2" toX="3" toY="4"/>
)";
				CHECK_EQ(ss.str(), ExpectedOut);
			}
		}

		WHEN("we draw a path")
		{
			constexpr CPoint pt1(1, 2);
			constexpr CPoint pt2(3, 4);
			constexpr CPoint pt3(5, 6);

			canvasAdapter.MoveTo(pt1.x, pt1.y);
			canvasAdapter.LineTo(pt2.x, pt2.y);
			canvasAdapter.LineTo(pt3.x, pt3.y);
			canvasAdapter.LineTo(pt1.x, pt1.y);

			THEN("the path is drawn")
			{
				const std::string ExpectedOut = R"(  <line fromX="1" fromY="2" toX="3" toY="4"/>
  <line fromX="3" fromY="4" toX="5" toY="6"/>
  <line fromX="5" fromY="6" toX="1" toY="2"/>
)";
				CHECK_EQ(ss.str(), ExpectedOut);
			}
		}
	}
}
