#pragma once
#include <array>

constexpr auto CYPHER_SIZE = 256;
using Cypher = std::array<uint8_t, CYPHER_SIZE>;

Cypher GenerateCypher(unsigned seed);
Cypher CreateCypherForDecoding(const Cypher& cypher);
