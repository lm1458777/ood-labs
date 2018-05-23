#pragma once

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;

	T GetRight() const
	{
		return left + width;
	}

	T GetBottom() const
	{
		return top + height;
	}
};

template <typename T>
struct PointT
{
	T x;
	T y;
};

using PointD = PointT<double>;
using RectD = Rect<double>;
using RGBAColor = uint32_t;
