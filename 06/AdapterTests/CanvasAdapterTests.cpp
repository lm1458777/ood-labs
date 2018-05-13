#include "stdafx.h"
#include "../AdapterLib/CanvasAdapter.h"
#include <vector>

SCENARIO("A CanvasAdapter test")
{
	GIVEN("a CanvasAdapter")
	{
		using modern_graphics_lib::CPoint;
		using std::make_pair;
		using Line = std::pair<CPoint, CPoint>;
		using Lines = std::vector<Line>;

		Lines lines;
		auto linePainter = [&lines](const CPoint& start, const CPoint& end) {
			lines.emplace_back(start, end);
		};
		CanvasAdapter canvasAdapter{ linePainter };

		WHEN("we draw a line")
		{
			constexpr CPoint start(1, 2);
			constexpr CPoint end(3, 4);

			canvasAdapter.MoveTo(start.x, start.y);
			canvasAdapter.LineTo(end.x, end.y);

			THEN("the line is drawn")
			{
				CHECK(lines == Lines({ make_pair(start, end) }));
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
				CHECK(lines == Lines({
								   make_pair(pt1, pt2),
								   make_pair(pt2, pt3),
								   make_pair(pt3, pt1),
							   }));
			}
		}
	}
}
