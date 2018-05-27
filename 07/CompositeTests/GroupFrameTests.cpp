#include "stdafx.h"
#include "../CompositeLib/IGroup.h"
#include "../CompositeLib/ShapeFactory.h"
#include "../CompositeLib/StyleFactory.h"

using namespace std;

namespace
{

auto CreateShape(const RectD& frame)
{
	return CreateRectangle(frame, CreateNoFillStyle(), CreateNoLineStyle());
}

} // namespace

ostream& operator<<(ostream& out, const RectD& rect)
{
	out << "Rect(L: " << rect.left
		<< ", T: " << rect.top
		<< ", W: " << rect.width
		<< ", H: " << rect.height
		<< ")";

	return out;
}

SCENARIO("A Group frame tests")
{
	GIVEN("a Group")
	{
		auto group = CreateGroup();

		WHEN("the group is empty")
		{
			REQUIRE_EQ(group->GetShapesCount(), 0u);

			THEN("the group frame is zero")
			{
				CHECK_EQ(group->GetFrame(), RECT_ZERO);
			}
		}

		WHEN("the group contains 1 shape")
		{
			constexpr RectD FRAME{ -100, -50, 20, 10 };
			AddShape(*group, CreateShape(FRAME));

			THEN("the group frame equals to the shape frame")
			{
				CHECK_EQ(group->GetFrame(), FRAME);
			}
		}

		WHEN("the group contains 2 shapes")
		{
			AddShape(*group, CreateShape({ -100, -50, 20, 10 }));
			AddShape(*group, CreateShape({ 100, 50, 30, 40 }));

			THEN("the group frame equals to the shapes frames union")
			{
				CHECK_EQ(group->GetFrame(), RectD{ -100, -50, 230, 140 });
			}
		}
	}

	GIVEN("a Group containing 2 shapes")
	{
		auto group = CreateGroup();
		auto shape1 = CreateShape({ -100, -50, 20, 10 });
		auto shape2 = CreateShape({ 100, 50, 30, 40 });
		AddShape(*group, shape1);
		AddShape(*group, shape2);

		WHEN("a new frame is set")
		{
			group->SetFrame({ 10, 5, 115, 210 });
			THEN("the shape 1 preserves relative frame")
			{
				CHECK_EQ(shape1->GetFrame(), RectD{ 10, 5, 10, 15 });
			}

			THEN("the shape 2 preserves relative frame")
			{
				CHECK_EQ(shape2->GetFrame(), RectD{ 110, 155, 15, 60 });
			}
		}
	}
}
