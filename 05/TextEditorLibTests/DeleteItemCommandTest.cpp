#include "stdafx.h"
#include "../TextEditorLib/DeleteItemCommand.h"
#include "MockDocumentItem.h"

SCENARIO("A command deletes an item from an items collection")
{
	const auto item1 = CreateMockItem();
	const auto item2 = CreateMockItem();
	const auto item3 = CreateMockItem();

	DocumentItems items{
		item1,
		item2,
		item3,
	};

	GIVEN("a collection with some items and a command")
	{
		DeleteItemCommand cmd(items, 1);

		WHEN("the command is executed")
		{
			cmd.Execute();

			THEN("the item is deleted")
			{
				REQUIRE_EQ(items.size(), 2);
				CHECK(items == DocumentItems{ item1, item3 });
			}

			AND_WHEN("the command is unexecuted")
			{
				cmd.Unexecute();

				THEN("the item is restored")
				{
					REQUIRE_EQ(items.size(), 3);
					CHECK(items == DocumentItems{ item1, item2, item3 });
				}
			}
		}
	}
}
