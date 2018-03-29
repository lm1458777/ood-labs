#include "stdafx.h"
#include "Cypher.h"

Cypher GenerateCypher(unsigned seed)
{
	using namespace std;

	Cypher cypher;
	uint8_t i = 0;
	generate(cypher.begin(), cypher.end(), [&i]() {
		return i++;
	});

	shuffle(cypher.begin(), cypher.end(), std::mt19937(seed));

	return cypher;
}

Cypher CreateCypherForDecoding(const Cypher& cypher)
{
	Cypher newCypher{};
	for (auto i = 0u; i < cypher.size(); ++i)
	{
		auto encodedValue = cypher[i];
		newCypher[encodedValue] = gsl::narrow_cast<uint8_t>(i);
	}

	return newCypher;
}
