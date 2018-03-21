#include "stdafx.h"
#include "..\libstreams\FileOutputStream.h"
#include <vector>

using namespace std;

static bool FileContainsData(const string& fileName, gsl::span<const uint8_t> data)
{
	std::vector<uint8_t> fileData(data.size());
	ifstream in(fileName, ios_base::binary | ios_base::in);
	in.exceptions(ios_base::badbit);
	in.read(reinterpret_cast<char*>(fileData.data()), data.size());
	const auto n = in.gcount();

	if (in.fail())
	{
		return false;
	}

	if (n != data.size())
	{
		return false;
	}

	in.peek();
	if (!in.eof())
	{
		return false;
	}

	return std::equal(fileData.begin(), fileData.end(), data.begin(), data.end());
}

SCENARIO("FileOutputStream tests")
{
	const uint8_t DATA1[] = { 0x7f, 0x00, 0xff, 0x01, 0xA5 };
	const uint8_t DATA2[] = { 0x00, 0x01, 0x7f, 0xff };

	GIVEN("a file output stream")
	{
		WHEN("writing DATA1 to a new file")
		{
			const string fileName = R"(test_data/temp-file)";

			{
				FileOutputStream out(fileName);
				for (auto b : DATA1)
				{
					out.WriteByte(b);
				}
			}

			THEN("file contains DATA1")
			{
				CHECK(FileContainsData(fileName, DATA1));
			}

			AND_WHEN("writing DATA2 to an existing file")
			{
				{
					FileOutputStream out(fileName);
					out.WriteBlock(DATA2, sizeof(DATA2));
				}

				THEN("file contains DATA2")
				{
					CHECK(FileContainsData(fileName, DATA2));
				}
			}

			std::remove(fileName.c_str());
		}
	}
}
