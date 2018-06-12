#include "stdafx.h"
#include "../TextEditorLib/Document.h"
#include "../TextEditorLib/HtmlExporter.h"
#include "../TextEditorLib/IFileSystem.h"
#include "../TextEditorLib/IImage.h"
#include "MockFileSystem.h"

using namespace std;

TEST_SUITE("A HtmlExporter tests")
{
	SCENARIO("An Exporter exports html")
	{
		GIVEN("a document")
		{
			constexpr auto TITLE = "Document title";
			constexpr auto PARA_1 = "The first paragraph";
			constexpr auto PATH = R"(C:\temp\football\Loko_2017-10\logos\Amkar.png)";
			constexpr auto PARA_2 = "After image paragraph";
			constexpr Size imageSize{ 400, 300 };

			Document doc{ make_shared<MockFileSystem>() };
			doc.SetTitle(TITLE);
			doc.InsertParagraph(PARA_1);
			const auto image = doc.InsertImage(PATH, imageSize);
			const auto imageFilename = image->GetPath().filename();
			doc.InsertParagraph(PARA_2);

			WHEN("the document is exported")
			{
				const auto mockFS = make_shared<MockFileSystem>();
				const Path imagesDir = "imgs";
				HtmlExporter(mockFS, imagesDir).Export(doc, R"(x:\doc.html)");

				THEN("images are copied")
				{
					REQUIRE_EQ(mockFS->copiedFiles.size(), 1);
					const auto& p = mockFS->copiedFiles.front();
					CHECK_EQ(p.source, image->GetPath());
					CHECK_EQ(p.dest, Path(R"(x:\)") / imagesDir / image->GetPath().filename());
				}

				THEN("html is written to the file")
				{
					stringstream sample;
					sample << "<!DOCTYPE html>\n"
							  "<html>\n";

					sample << "<head>\n"
						   << "\t<title>" << TITLE << "</title>\n"
						   << "</head>\n"
							  "<body>\n";

					sample << "\t<p>" << PARA_1 << "</p>\n";
					sample << "\t<img src='" << (imagesDir / imageFilename).generic_string() << "'"
						   << " width=" << imageSize.width
						   << " height=" << imageSize.height
						   << ">\n";
					sample << "\t<p>" << PARA_2 << "</p>\n";

					sample << "</body>\n"
							  "</html>";

					// path
					// content
					// special symbols

					CHECK_EQ(sample.str(), mockFS->out.str());
				}
			}
		}
	}

	SCENARIO("An exporter escapes special entities")
	{
		GIVEN("a document with special entities")
		{
			Document doc{ make_shared<MockFileSystem>() };
			doc.SetTitle("a<\"&'>bc");
			doc.InsertParagraph("para 1");
			doc.InsertParagraph("1 <> 2");

			WHEN("the document is exported")
			{
				auto mockFS = make_shared<MockFileSystem>();
				HtmlExporter(mockFS, "").Export(doc, R"(x:\file)");

				THEN("the special entities are escaped")
				{
					stringstream sample;
					sample << "<!DOCTYPE html>\n"
							  "<html>\n";

					sample << "<head>\n"
						   << "\t<title>"
						   << R"(a&lt;&quot;&amp;'&gt;bc)"
						   << "</title>\n"
						   << "</head>\n"
							  "<body>\n";

					sample << "\t<p>"
						   << "para 1"
						   << "</p>\n";
					sample << "\t<p>"
						   << R"(1 &lt;&gt; 2)"
						   << "</p>\n";

					sample << "</body>\n"
							  "</html>";

					CHECK_EQ(sample.str(), mockFS->out.str());
				}
			}
		}
	}
}
