#pragma once
#include "Cypher.h"
#include "IOutputDataStream.h"
#include <vector>

class EncodedOutputStream : public IOutputDataStream
{
public:
	EncodedOutputStream(IOutputDataStreamUniquePtr stream, const Cypher& cypher);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	const Cypher m_cypher;
	const IOutputDataStreamUniquePtr m_stream;
	std::vector<uint8_t> m_buffer;
};
