#include "stdafx.h"
#include "Cypher.h"

Cypher GenerateCypher(unsigned seed)
{
	using namespace std;

	Cypher cypher;
	iota(cypher.begin(), cypher.end(), 0);

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
