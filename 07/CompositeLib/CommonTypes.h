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
bool operator==(const Rect<T>& a, const Rect<T>& b)
{
	auto rank = [](const auto& rect) {
		return std::make_tuple(rect.left, rect.top, rect.width, rect.height);
	};

	return rank(a) == rank(b);
}

template <typename T>
bool operator!=(const Rect<T>& a, const Rect<T>& b)
{
	return !(a == b);
}

template <typename T>
Rect<T> UnionRect(const Rect<T>& a, const Rect<T>& b)
{
	auto left = std::min(a.left, b.left);
	auto top = std::min(a.top, b.top);
	auto right = std::max(a.GetRight(), b.GetRight());
	auto bottom = std::max(a.GetBottom(), b.GetBottom());
	return Rect<T>{ left, top, right - left, bottom - top };
}

template <typename T>
struct PointT
{
	T x;
	T y;
};

using PointD = PointT<double>;
using RectD = Rect<double>;
using RGBAColor = uint32_t;

constexpr RectD RectDZero{ 0, 0, 0, 0 };
