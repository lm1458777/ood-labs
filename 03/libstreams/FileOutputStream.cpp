#include "stdafx.h"
#include "FileOutputStream.h"

using namespace std;

FileOutputStream::FileOutputStream(const string& fileName)
{
	m_stream.exceptions(ios_base::failbit | ios_base::badbit);
	m_stream.open(fileName, ios_base::out | ios_base::binary | ios_base::trunc);
}

void FileOutputStream::WriteByte(uint8_t data)
{
	WriteBlock(&data, sizeof(data));
}

void FileOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	m_stream.write(static_cast<const char*>(srcData), size);
}
