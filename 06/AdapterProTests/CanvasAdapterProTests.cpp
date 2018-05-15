#include "stdafx.h"
#include "../AdapterProLib/CanvasAdapter.h"
#include "../AdapterProLib/ColorUtils.h"
#include <vector>

SCENARIO("A CanvasAdapterPro test")
{
	GIVEN("a CanvasAdapterPro")
	{
		using modern_graphics_lib::CPoint;
		using modern_graphics_lib::CRGBAColor;
		using std::make_tuple;
		using Line = std::tuple<CPoint, CPoint, CRGBAColor>;
		using Lines = std::vector<Line>;

		Lines lines;
		auto linePainter = [&lines](const CPoint& start, const CPoint& end, const CRGBAColor& color) {
			lines.emplace_back(start, end, color);
		};
		CanvasAdapter canvasAdapter{ linePainter };

		const auto _05f = 0x7f / 255.f;

		WHEN("we draw a line")
		{
			constexpr CPoint start(1, 2);
			constexpr CPoint end(3, 4);

			canvasAdapter.SetColor(RGB(0, 0x7f, 0xff));
			canvasAdapter.MoveTo(start.x, start.y);
			canvasAdapter.LineTo(end.x, end.y);

			THEN("the line is drawn")
			{
				CHECK(lines == Lines({ make_tuple(start, end, CRGBAColor(0.f, _05f, 1.0f, 1.0f)) }));
			}
		}

		WHEN("we draw a path")
		{
			constexpr CPoint pt1(1, 2);
			constexpr CPoint pt2(3, 4);
			constexpr CPoint pt3(5, 6);

			canvasAdapter.MoveTo(pt1.x, pt1.y);

			canvasAdapter.SetColor(RGB(0, 0xff, 0x7f));
			canvasAdapter.LineTo(pt2.x, pt2.y);

			canvasAdapter.SetColor(RGB(0xff, 0, 0x7f));
			canvasAdapter.LineTo(pt3.x, pt3.y);

			canvasAdapter.SetColor(RGB(0x7f, 0xff, 0));
			canvasAdapter.LineTo(pt1.x, pt1.y);

			THEN("the path is drawn")
			{
				CHECK(lines == Lines({
								   make_tuple(pt1, pt2, CRGBAColor(0.f, 1.0f, _05f, 1.0f)),
								   make_tuple(pt2, pt3, CRGBAColor(1.0f, 0.f, _05f, 1.0f)),
								   make_tuple(pt3, pt1, CRGBAColor(_05f, 1.0f, 0.f, 1.0f)),
							   }));
			}
		}
	}
}
