#include "stdafx.h"
#include "EncodedOutputStream.h"

EncodedOutputStream::EncodedOutputStream(IOutputDataStreamUniquePtr stream, const Cypher& cypher)
	: m_cypher(cypher)
	, m_stream(std::move(stream))
{
	if (!m_stream)
	{
		throw std::invalid_argument("The stream must not be null");
	}
}

void EncodedOutputStream::WriteByte(uint8_t data)
{
	auto encoded = m_cypher[data];
	m_stream->WriteByte(encoded);
}

void EncodedOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	auto src = gsl::make_span(static_cast<const uint8_t*>(srcData), size);

	m_buffer.clear();
	m_buffer.reserve(size);
	std::transform(src.begin(), src.end(), std::back_inserter(m_buffer), [this](uint8_t srcByte) {
		return m_cypher[srcByte];
	});

	m_stream->WriteBlock(m_buffer.data(), size);
}
