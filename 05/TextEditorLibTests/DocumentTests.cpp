#include "stdafx.h"
#include "../TextEditorLib/Document.h"
#include "../TextEditorLib/IDocumentItem.h"
#include "../TextEditorLib/IImage.h"
#include "MockFileSystem.h"

using namespace std;

TEST_SUITE("Document tests")
{
	TEST_CASE("A new document")
	{
		Document doc{ make_shared<MockFileSystem>() };

		SUBCASE("has no title")
		{
			CHECK(doc.GetTitle().empty());
		}

		SUBCASE("has no items")
		{
			CHECK_EQ(doc.GetItemsCount(), 0u);
		}

		SUBCASE("has no history")
		{
			SUBCASE("can't undo")
			{
				CHECK_FALSE(doc.CanUndo());
			}

			SUBCASE("can't redo")
			{
				CHECK_FALSE(doc.CanRedo());
			}
		}
	}

	TEST_CASE("set title")
	{
		GIVEN("a document with empty title")
		{
			Document doc{ make_shared<MockFileSystem>() };

			REQUIRE(doc.GetTitle().empty());

			WHEN("set the document title")
			{
				const std::string NEW_TITLE = "new document title";

				doc.SetTitle(NEW_TITLE);

				THEN("the document has the new title")
				{
					CHECK_EQ(doc.GetTitle(), NEW_TITLE);
				}

				THEN("can't redo")
				{
					CHECK(!doc.CanRedo());
				}

				THEN("can undo")
				{
					CHECK(doc.CanUndo());
				}

				AND_WHEN("undo")
				{
					doc.Undo();

					THEN("the document title is empty")
					{
						CHECK(doc.GetTitle().empty());
					}

					THEN("can't undo")
					{
						CHECK(!doc.CanUndo());
					}

					THEN("can redo")
					{
						CHECK(doc.CanRedo());
					}

					AND_WHEN("redo")
					{
						doc.Redo();

						THEN("the document has the new title")
						{
							CHECK_EQ(doc.GetTitle(), NEW_TITLE);
						}

						THEN("can't redo")
						{
							CHECK(!doc.CanRedo());
						}

						THEN("can undo")
						{
							CHECK(doc.CanUndo());
						}
					}
				}
			}
		}
	}

	SCENARIO("Insert an image")
	{
		GIVEN("a document")
		{
			auto mockFS = make_shared<MockFileSystem>();
			Document doc{ mockFS };

			WHEN("an image is inserted")
			{
				const Path imagePath = R"(x:\image.png)";
				constexpr Size imageSize{ 400, 300 };
				const auto image = doc.InsertImage(imagePath, imageSize);

				THEN("the image is copied")
				{
					REQUIRE_EQ(mockFS->copiedFiles.size(), 1);
					CHECK_EQ(mockFS->copiedFiles.front().source, imagePath);
				}

				THEN("the document contains an image item")
				{
					REQUIRE_EQ(doc.GetItemsCount(), 1);
					CHECK_EQ(doc.GetItem(0)->GetImage(), image);
				}
			}
		}
	}

	TEST_CASE("ListDocument test")
	{
		constexpr auto TITLE = "Document title";
		constexpr auto PARA_1 = "The first paragraph";
		constexpr auto PARA_2 = "After image paragraph";
		constexpr Size imageSize{ 400, 300 };

		Document doc{ make_shared<MockFileSystem>() };
		doc.InsertParagraph(PARA_1);
		doc.InsertParagraph(PARA_2, 1);
		const auto image = doc.InsertImage(R"(x:\image.png)", imageSize, 1);
		doc.SetTitle(TITLE);

		stringstream out;
		ListDocument(doc, out);

		stringstream sample;
		sample
			<< "Title: '" << TITLE << "'" << endl
			<< "0. Paragraph: '" << PARA_1 << "'" << endl
			<< "1. Image: " << imageSize.width << "x" << imageSize.height << ", '" << image->GetPath().generic_string() << "'" << endl
			<< "2. Paragraph: '" << PARA_2 << "'" << endl;
		CHECK_EQ(out.str(), sample.str());
	}
}
