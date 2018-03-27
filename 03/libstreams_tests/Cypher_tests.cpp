#include "stdafx.h"
#include "..\libstreams\Cypher.h"

using namespace std;

namespace
{

bool ContainsUniqueValues(const Cypher& cypher)
{
	std::bitset<CYPHER_SIZE> values;

	for (auto i = 0; i < CYPHER_SIZE; ++i)
	{
		auto value = cypher[i];

		if (values.test(value))
		{
			return false;
		}

		values.set(value);
	}

	return true;
}

bool IsValidEncDecCyphers(const Cypher& enc, const Cypher& dec)
{
	for (auto i = 0; i < enc.size(); ++i)
	{
		if (dec.at(enc[i]) != i)
		{
			return false;
		}
	}

	return true;
}

} // namespace

SCENARIO("Cypher generation tests")
{
	GIVEN("a cypher generator")
	{
		WHEN("generates a cypher")
		{
			auto cypher = GenerateCypher(0x123);

			THEN("cypher contains 256 values")
			{
				CHECK_EQ(cypher.size(), 256);
			}

			THEN("cypher contains unique values [0..255]")
			{
				CHECK(ContainsUniqueValues(cypher));
			}

			THEN("values are not sorted")
			{
				CHECK(!is_sorted(cypher.begin(), cypher.end()));
			}
		}

		WHEN("generates a cyphers for the same key")
		{
			auto cypher1 = GenerateCypher(100500);
			auto cypher2 = GenerateCypher(100500);

			THEN("cyphers are equal")
			{
				CHECK(cypher1 == cypher2);
			}
		}

		WHEN("generates a cyphers for different keys")
		{
			auto cypher1 = GenerateCypher(3);
			auto cypher2 = GenerateCypher(100500);

			THEN("cyphers are different")
			{
				CHECK(cypher1 != cypher2);
			}
		}

		WHEN("generates a cyphers for encoding and decoding")
		{
			auto encoding = GenerateCypher(17);
			auto decoding = CreateCypherForDecoding(encoding);

			THEN("cyphers are valid")
			{
				CHECK(IsValidEncDecCyphers(encoding, decoding));

				CHECK(!IsValidEncDecCyphers(encoding, encoding));
				CHECK(!IsValidEncDecCyphers(Cypher(), decoding));
			}
		}
	}
}
