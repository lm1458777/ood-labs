#include "stdafx.h"
#include "FileInputStream.h"

using namespace std;

static void ThrowError(const char* msg)
{
	throw std::ios_base::failure(msg);
}

FileInputStream::FileInputStream(const std::string& fileName)
{
	m_stream.exceptions(ios_base::badbit);

	m_stream.open(fileName, ios_base::in | ios_base::binary);
	if (!m_stream.is_open())
	{
		ThrowError("Can't open file for input");
	}

	m_stream.peek();
}

bool FileInputStream::IsEOF() const
{
	return m_stream.eof();
}

uint8_t FileInputStream::ReadByte()
{
	uint8_t b = 0;
	auto bytesReaded = ReadBlock(&b, sizeof(b));
	if (bytesReaded != sizeof(b))
	{
		ThrowError("Can't read byte");
	}
	return b;
}

std::streamsize FileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (m_stream.fail() || m_stream.eof())
	{
		ThrowError("Can't read block");
	}

	m_stream.read(static_cast<char*>(dstBuffer), size);
	auto n = m_stream.gcount();
	m_stream.peek();
	return n;
}
