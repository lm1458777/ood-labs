#pragma once
#include <iosfwd>
#include <memory>
#include <stdint.h>

class IOutputDataStream
{
public:
	virtual ~IOutputDataStream() = default;

	// ���������� � ����� ������ ����
	// ����������� ���������� std::ios_base::failure � ������ ������
	virtual void WriteByte(uint8_t data) = 0;

	// ���������� � ����� ���� ������ �������� size ����,
	// ��������������� �� ������ srcData,
	// � ������ ������ ����������� ���������� std::ios_base::failure
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;
};

using IOutputDataStreamUniquePtr = std::unique_ptr<IOutputDataStream>;
