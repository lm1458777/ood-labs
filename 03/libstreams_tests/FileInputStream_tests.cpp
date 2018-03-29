#include "stdafx.h"
#include "..\libstreams\FileInputStream.h"

using namespace std;

SCENARIO("FileInputStream tests")
{
	GIVEN("a nonexistent file")
	{
		WHEN("creating a stream")
		{
			THEN("an error occured")
			{
				CHECK_THROWS_AS(FileInputStream("nonexistent file"), ios_base::failure);
			}
		}
	}

	GIVEN("an empty file")
	{
		FileInputStream stream("test_data/empty-file");

		WHEN("testing for EOF")
		{
			THEN("returns true")
			{
				CHECK(stream.IsEOF());
			}
		}

		WHEN("reading byte")
		{
			THEN("throws an exception")
			{
				CHECK_THROWS_AS(stream.ReadByte(), ios_base::failure);
			}
		}

		WHEN("reading block")
		{
			THEN("throws an exception")
			{
				char ch = '\0';
				CHECK_THROWS_AS(stream.ReadBlock(&ch, sizeof(ch)), ios_base::failure);
			}
		}
	}

	GIVEN("a stream with 1 byte")
	{
		constexpr uint8_t DATA = 0xA5;
		FileInputStream stream("test_data/1-byte");

		WHEN("testing for EOF")
		{
			THEN("returns false")
			{
				CHECK(!stream.IsEOF());
			}
		}

		WHEN("reading byte")
		{
			auto b = stream.ReadByte();
			THEN("returns data")
			{
				CHECK_EQ(b, DATA);

				AND_WHEN("read one more byte")
				{
					THEN("throws an error")
					{
						CHECK_THROWS_AS(stream.ReadByte(), ios_base::failure);
					}
				}
			}
			THEN("at EOF")
			{
				CHECK(stream.IsEOF());
			}
		}

		WHEN("reading block")
		{
			uint8_t buf[8] = {};
			auto n = stream.ReadBlock(&buf, sizeof(buf));
			THEN("reads one byte")
			{
				CHECK_EQ(n, 1);
			}
			THEN("reads data")
			{
				CHECK_EQ(buf[0], DATA);
			}
			THEN("at EOF")
			{
				CHECK(stream.IsEOF());
			}
			AND_WHEN("read one more block")
			{
				THEN("trhows an error")
				{
					CHECK_THROWS_AS(stream.ReadBlock(&buf, sizeof(buf)), ios_base::failure);
				}
			}
		}
	}

	GIVEN("a stream with 15 byte")
	{
		const string DATA = "hello, world! \xA5";
		FileInputStream stream("test_data/15-byte");

		WHEN("reading by byte")
		{
			std::string s;
			auto n = 0;
			while (!stream.IsEOF())
			{
				s += static_cast<char>(stream.ReadByte());
				++n;
			}

			THEN("reads data")
			{
				CHECK_EQ(s, DATA);
			}

			THEN("reads 15 bytes")
			{
				CHECK_EQ(n, 15);
			}
		}

		WHEN("reading by large chunk")
		{
			char buf[32] = "";
			auto n = stream.ReadBlock(buf, sizeof(buf));
			buf[n] = '\0';

			THEN("reads data")
			{
				CHECK_EQ(buf, DATA);
			}

			THEN("reads 15 bytes")
			{
				CHECK_EQ(n, 15);
			}
		}

		WHEN("reading by small chunks")
		{
			string s;
			auto bytesRead = 0;
			char buf[7] = "";
			while (!stream.IsEOF())
			{
				auto n = stream.ReadBlock(buf, sizeof(buf));
				s.append(buf, gsl::narrow<size_t>(n));
				bytesRead += gsl::narrow<int>(n);
			}

			THEN("reads data")
			{
				CHECK_EQ(s, DATA);
			}

			THEN("reads 15 bytes")
			{
				CHECK_EQ(bytesRead, 15);
			}
		}
	}
}
