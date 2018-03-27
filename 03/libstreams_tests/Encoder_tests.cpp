#include "stdafx.h"
#include "..\libstreams\EncodedOutputStream.h"

namespace
{

struct MockOutputStream : public IOutputDataStream
{
	std::vector<uint8_t> data;

	void WriteByte(uint8_t b) override
	{
		data.push_back(b);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto begin = static_cast<const uint8_t*>(srcData);
		data.insert(data.end(), begin, begin + size);
	}
};

} // namespace

SCENARIO("EncodedOutputStream tests")
{
	GIVEN("an EncodedOutputStream")
	{
		Cypher cypher;
		cypher['H'] = 1;
		cypher['e'] = 2;
		cypher['l'] = 3;
		cypher['o'] = 4;

		auto mockStream = std::make_unique<MockOutputStream>();
		auto& mockStreamRef = *mockStream;
		EncodedOutputStream encodedStream(std::move(mockStream), cypher);

		const std::vector<uint8_t> DATA{ 'H', 'e', 'l', 'l', 'o' };

		WHEN("writing bytes")
		{
			for (auto d : DATA)
			{
				encodedStream.WriteByte(d);
			}

			THEN("an encoded stream is produced")
			{
				CHECK_EQ(std::vector<uint8_t>({ 1, 2, 3, 3, 4 }), mockStreamRef.data);
			}
		}

		WHEN("writing blocks")
		{
			encodedStream.WriteBlock(DATA.data(), DATA.size());
			encodedStream.WriteBlock(DATA.data(), DATA.size() - 1);

			THEN("an encoded stream is produced")
			{
				CHECK_EQ(std::vector<uint8_t>({ 1, 2, 3, 3, 4, 1, 2, 3, 3 }), mockStreamRef.data);
			}
		}
	}
}
