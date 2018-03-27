#pragma once
#include "Cypher.h"
#include "IInputDataStream.h"

class DecodedInputStream : public IInputDataStream
{
public:
	DecodedInputStream(IInputDataStreamUniquePtr encodedStream, const Cypher& cypher);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	const IInputDataStreamUniquePtr m_encodedStream;
	const Cypher m_cypher;
};
