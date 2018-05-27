#include "stdafx.h"
#include "../CompositeLib/ColorUtils.h"
#include "../CompositeLib/IGroup.h"
#include "../CompositeLib/ShapeFactory.h"
#include "../CompositeLib/StyleFactory.h"

using namespace std;

namespace
{

auto CreateShape(const LineStyle& lineStyle)
{
	return CreateRectangle(RECT_ZERO, CreateFillStyle(0, false), lineStyle);
}

} // namespace

SCENARIO("A Group line style tests")
{
	GIVEN("a Group containing 2 shapes with different line styles")
	{
		auto group = CreateGroup();
		auto shape1 = CreateShape(CreateLineStyle(RED_COLOR, 0.5f));
		auto shape2 = CreateShape(CreateLineStyle(GREEN_COLOR, 1.5f));
		AddShape(*group, shape1);
		AddShape(*group, shape2);

		const auto& groupStyle = group->GetLineStyle();
		CHECK(groupStyle.GetColor() == boost::none);
		CHECK(groupStyle.GetWidth() == boost::none);
		CHECK(groupStyle.IsEnabled() == true);

		WHEN("a new line width is set")
		{
			constexpr auto NEW_LINE_WIDTH = 3.f;

			group->GetLineStyle().SetWidth(NEW_LINE_WIDTH);

			THEN("the shape 1 line width changes but not the color")
			{
				const auto& style = shape1->GetLineStyle();
				CHECK_EQ(style.GetWidth(), NEW_LINE_WIDTH);
				CHECK_EQ(style.GetColor(), RED_COLOR);
			}

			THEN("the shape 2 line width changes but not the color")
			{
				const auto& style = shape2->GetLineStyle();
				CHECK_EQ(style.GetWidth(), NEW_LINE_WIDTH);
				CHECK_EQ(style.GetColor(), GREEN_COLOR);
			}

			THEN("the group line width changes but not the color")
			{
				CHECK_EQ(groupStyle.GetWidth(), NEW_LINE_WIDTH);
				CHECK(groupStyle.GetColor() == boost::none);
			}
		}
	}
}

SCENARIO("A Group styles tests")
{
	GIVEN("a Group containing an empty subgroup")
	{
		auto group = CreateGroup();
		AddShape(*group, CreateGroup());

		WHEN("get fill style")
		{
			const auto& fillStyle = group->GetFillStyle();

			THEN("Enabled is empty")
			{
				CHECK(!fillStyle.IsEnabled().is_initialized());
			}

			THEN("Color is empty")
			{
				CHECK(!fillStyle.GetColor().is_initialized());
			}
		}

		WHEN("get line style")
		{
			const auto& lineStyle = group->GetLineStyle();

			THEN("Enabled is empty")
			{
				CHECK(!lineStyle.IsEnabled().is_initialized());
			}

			THEN("Color is empty")
			{
				CHECK(!lineStyle.GetColor().is_initialized());
			}

			THEN("Width is empty")
			{
				CHECK(!lineStyle.GetWidth().is_initialized());
			}
		}
	}

	GIVEN("a Group containing a subgroup with 1 shape")
	{
		const auto shape = CreateRectangle(RECT_ZERO, CreateNoFillStyle(), CreateNoLineStyle());
		const auto subgroup = CreateGroup();
		const auto group = CreateGroup();
		AddShape(*group, subgroup);
		AddShape(*subgroup, shape);

		WHEN("get the group fill style")
		{
			const auto& groupStyle = group->GetFillStyle();
			const auto& shapeStyle = shape->GetFillStyle();

			THEN("Enabled is equal to the shape value")
			{
				CHECK_EQ(groupStyle.IsEnabled(), shapeStyle.IsEnabled());
			}

			THEN("Color is equal to the shape value")
			{
				CHECK_EQ(groupStyle.GetColor(), shapeStyle.GetColor());
			}
		}

		WHEN("get the group line style")
		{
			const auto& groupStyle = group->GetLineStyle();
			const auto& shapeStyle = shape->GetLineStyle();

			THEN("Enabled is equal to the shape value")
			{
				CHECK_EQ(groupStyle.IsEnabled(), shapeStyle.IsEnabled());
			}

			THEN("Color is equal to the shape value")
			{
				CHECK_EQ(groupStyle.GetColor(), shapeStyle.GetColor());
			}

			THEN("Width is equal to the shape value")
			{
				CHECK_EQ(groupStyle.GetWidth(), shapeStyle.GetWidth());
			}
		}
	}
}
