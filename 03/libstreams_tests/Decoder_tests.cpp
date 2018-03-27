#include "stdafx.h"
#include "..\libstreams\DecodedInputStream.h"

namespace
{

struct MockInputStream : public IInputDataStream
{
	std::vector<uint8_t> data;
	size_t currentPos = 0;

	bool IsEOF() const override
	{
		return currentPos >= data.size();
	}

	uint8_t ReadByte() override
	{
		return data.at(currentPos++);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (IsEOF())
		{
			throw std::runtime_error("Buffer is empty");
		}

		auto n = std::min(gsl::narrow<size_t>(size), data.size() - currentPos);
		auto begin = data.begin() + currentPos;
		stdext::checked_array_iterator<uint8_t*> itBuffer(static_cast<uint8_t*>(dstBuffer), size);
		std::copy(begin, begin + n, itBuffer);
		currentPos += n;
		return n;
	}
};

} // namespace

SCENARIO("Decoder tests")
{
	GIVEN("an EncodedOutputStream")
	{
		Cypher cypher;
		cypher[1] = 'H';
		cypher[2] = 'e';
		cypher[3] = 'l';
		cypher[4] = 'o';

		auto mockStream = std::make_unique<MockInputStream>();
		mockStream->data.assign({ 1, 2, 3, 3, 4 });
		DecodedInputStream stream(std::move(mockStream), cypher);

		const std::vector<uint8_t> EXPECTED{ 'H', 'e', 'l', 'l', 'o' };

		WHEN("reading bytes")
		{
			std::vector<uint8_t> data;
			while (!stream.IsEOF())
			{
				data.push_back(stream.ReadByte());
			}

			THEN("a decoded stream is produced")
			{
				CHECK_EQ(EXPECTED, data);
			}
		}

		WHEN("reading blocks")
		{
			std::vector<uint8_t> data;
			uint8_t buf[3];
			while (!stream.IsEOF())
			{
				auto n = stream.ReadBlock(buf, sizeof(buf));
				if (n > 0)
				{
					data.insert(data.end(), buf, buf + n);
				}
			}

			THEN("a decoded stream is produced")
			{
				CHECK_EQ(EXPECTED, data);
			}
		}
	}
}
