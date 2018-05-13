#pragma once
#include <cstdint>
#include <intsafe.h>

constexpr BYTE GetComponentValue(uint32_t color, unsigned offset)
{
	return static_cast<BYTE>((color >> offset) & 0xff);
}

constexpr BYTE GetRedValue(uint32_t color)
{
	return GetComponentValue(color, 16);
}

constexpr BYTE GetGreenValue(uint32_t color)
{
	return GetComponentValue(color, 8);
}

constexpr BYTE GetBlueValue(uint32_t color)
{
	return GetComponentValue(color, 0);
}

constexpr auto RGB(BYTE r, BYTE g, BYTE b)
{
	return static_cast<uint32_t>(b
		| (static_cast<WORD>(g) << 8)
		| (static_cast<DWORD>(r) << 16));
}
