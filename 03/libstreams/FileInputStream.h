#pragma once
#include "IInputDataStream.h"
#include <fstream>

class FileInputStream final : public IInputDataStream
{
public:
	explicit FileInputStream(const std::string& fileName);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::ifstream m_stream;
};
