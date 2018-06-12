#include "stdafx.h"
#include "../TextEditorLib/InsertItemCommand.h"
#include "MockDocumentItem.h"

SCENARIO("A command inserts an item to an items collection")
{
	const auto item1 = CreateMockItem();
	const auto item2 = CreateMockItem();

	DocumentItems items{
		item1,
		item2,
	};

	const auto newItem = CreateMockItem();

	GIVEN("a collection with some items and a command (insert at the end)")
	{
		InsertItemCommand cmd(items, newItem, boost::none);

		WHEN("the command is executed")
		{
			cmd.Execute();

			THEN("the item is inserted at the end")
			{
				REQUIRE_EQ(items.size(), 3);
				CHECK(items == DocumentItems{ item1, item2, newItem });
			}

			AND_WHEN("the command is unexecuted")
			{
				cmd.Unexecute();

				THEN("the item is removed")
				{
					REQUIRE_EQ(items.size(), 2);
					CHECK(items == DocumentItems{ item1, item2 });
				}
			}
		}
	}

	GIVEN("a collection with some items and a command (insert at custom position)")
	{
		InsertItemCommand cmd(items, newItem, 1);

		WHEN("the command is executed")
		{
			cmd.Execute();

			THEN("the item is inserted at custom position")
			{
				REQUIRE_EQ(items.size(), 3);
				CHECK(items == DocumentItems{ item1, newItem, item2 });
			}

			AND_WHEN("the command is unexecuted")
			{
				cmd.Unexecute();

				THEN("the item is removed")
				{
					REQUIRE_EQ(items.size(), 2);
					CHECK(items == DocumentItems{ item1, item2 });
				}
			}
		}
	}
}
