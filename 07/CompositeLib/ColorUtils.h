#pragma once
#include "CommonTypes.h"
#include <cstdint>
#include <intsafe.h>

enum
{
	RedShift = 24,
	GreenShift = 16,
	BlueShift = 8,
	AlphaShift = 0,
};

constexpr BYTE GetComponentValue(uint32_t color, unsigned offset)
{
	return static_cast<BYTE>((color >> offset) & 0xff);
}

constexpr BYTE GetRedValue(uint32_t color)
{
	return GetComponentValue(color, RedShift);
}

constexpr BYTE GetGreenValue(uint32_t color)
{
	return GetComponentValue(color, GreenShift);
}

constexpr BYTE GetBlueValue(uint32_t color)
{
	return GetComponentValue(color, BlueShift);
}

constexpr BYTE GetAlphaValue(uint32_t color)
{
	return GetComponentValue(color, AlphaShift);
}

constexpr auto MakeColorRGBA(BYTE r, BYTE g, BYTE b, BYTE a)
{
	return (static_cast<uint32_t>(a) << AlphaShift)
		| (static_cast<uint32_t>(b) << BlueShift)
		| (static_cast<uint32_t>(g) << GreenShift)
		| (static_cast<uint32_t>(r) << RedShift);
}

constexpr auto MakeColorRGB(BYTE r, BYTE g, BYTE b)
{
	return MakeColorRGBA(r, g, b, 0xff);
}

constexpr RGBAColor MakeColorWithAlpha(RGBAColor color, BYTE alpha)
{
	return MakeColorRGBA(
		GetRedValue(color),
		GetGreenValue(color),
		GetBlueValue(color),
		alpha);
}

constexpr RGBAColor BLACK_COLOR = MakeColorRGB(0, 0, 0);
constexpr RGBAColor WHITE_COLOR = MakeColorRGB(0xff, 0xff, 0xff);

constexpr RGBAColor RED_COLOR = MakeColorRGB(0xff, 0, 0);
constexpr RGBAColor GREEN_COLOR = MakeColorRGB(0, 0xff, 0);
constexpr RGBAColor BLUE_COLOR = MakeColorRGB(0, 0, 0xff);
