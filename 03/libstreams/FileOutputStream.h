#pragma once
#include "IOutputDataStream.h"
#include <fstream>

class FileOutputStream : public IOutputDataStream
{
public:
	explicit FileOutputStream(const std::string& fileName);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ofstream m_stream;
};
