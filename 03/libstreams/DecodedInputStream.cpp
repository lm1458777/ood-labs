#include "stdafx.h"
#include "DecodedInputStream.h"

DecodedInputStream::DecodedInputStream(IInputDataStreamUniquePtr encodedStream, const Cypher& cypher)
	: m_encodedStream(std::move(encodedStream))
	, m_cypher(cypher)
{
	if (!m_encodedStream)
	{
		throw std::invalid_argument("The stream must not be null");
	}
}

bool DecodedInputStream::IsEOF() const
{
	return m_encodedStream->IsEOF();
}

uint8_t DecodedInputStream::ReadByte()
{
	auto encodedByte = m_encodedStream->ReadByte();
	return m_cypher[encodedByte];
}

std::streamsize DecodedInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto n = m_encodedStream->ReadBlock(dstBuffer, size);

	auto data = static_cast<uint8_t*>(dstBuffer);
	for (auto i = 0; i < n; ++i)
	{
		auto encodedByte = data[i];
		data[i] = m_cypher[encodedByte];
	}

	return n;
}
