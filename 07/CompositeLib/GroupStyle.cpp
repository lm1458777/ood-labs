#include "stdafx.h"
#include "GroupStyle.h"

namespace
{

template <class T, class R, class ValueGetter>
boost::optional<T> GetValue(R&& styleRange, ValueGetter valueGetter)
{
	auto it = styleRange.begin();

	if (it == styleRange.end()) // empty range
	{
		return boost::none;
	}

	auto getValue = [valueGetter](const auto& style) {
		return std::invoke(valueGetter, style);
	};

	auto firstValue = getValue(*it);
	if (!firstValue.is_initialized())
	{
		return boost::none;
	}

	++it;
	if (it == styleRange.end()) // range contains only one item
	{
		return firstValue;
	}

	bool allStylesHaveSameValue = std::all_of(it, styleRange.end(), [&firstValue, getValue](const auto& style) {
		auto value = getValue(style);
		return value.is_initialized() && *value == firstValue;
	});

	return allStylesHaveSameValue ? firstValue : boost::none;
}

template <class R, class ValueSetter, class T>
void SetValue(R&& styleRange, ValueSetter valueSetter, T value)
{
	boost::for_each(styleRange, [value, valueSetter](auto& style) {
		std::invoke(valueSetter, style, value);
	});
}

} // namespace

GroupFillStyle::GroupFillStyle(StyleEnumerator styleEnumerator)
	: m_styleEnumerator{ std::move(styleEnumerator) }
{
}

boost::optional<bool> GroupFillStyle::IsEnabled() const
{
	return GetValue<bool>(m_styleEnumerator(), &IFillStyle::IsEnabled);
}

void GroupFillStyle::Enable(bool enable)
{
	SetValue(m_styleEnumerator(), &IFillStyle::Enable, enable);
}

boost::optional<RGBAColor> GroupFillStyle::GetColor() const
{
	return GetValue<RGBAColor>(m_styleEnumerator(), &IFillStyle::GetColor);
}

void GroupFillStyle::SetColor(RGBAColor color)
{
	SetValue(m_styleEnumerator(), &IFillStyle::SetColor, color);
}

GroupLineStyle::GroupLineStyle(StyleEnumerator styleEnumerator)
	: m_styleEnumerator{ std::move(styleEnumerator) }
{
}

boost::optional<bool> GroupLineStyle::IsEnabled() const
{
	return GetValue<bool>(m_styleEnumerator(), &ILineStyle::IsEnabled);
}

void GroupLineStyle::Enable(bool enable)
{
	SetValue(m_styleEnumerator(), &ILineStyle::Enable, enable);
}

boost::optional<RGBAColor> GroupLineStyle::GetColor() const
{
	return GetValue<RGBAColor>(m_styleEnumerator(), &ILineStyle::GetColor);
}

void GroupLineStyle::SetColor(RGBAColor color)
{
	SetValue(m_styleEnumerator(), &ILineStyle::SetColor, color);
}

boost::optional<float> GroupLineStyle::GetWidth() const
{
	return GetValue<float>(m_styleEnumerator(), &ILineStyle::GetWidth);
}

void GroupLineStyle::SetWidth(float width)
{
	SetValue(m_styleEnumerator(), &ILineStyle::SetWidth, width);
}
