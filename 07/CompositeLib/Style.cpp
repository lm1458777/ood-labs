#include "stdafx.h"
#include "Style.h"

CStyle::CStyle(bool enable, RGBAColor color)
	: m_isEnabled(enable)
	, m_color(color)
{
}

bool CStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

RGBAColor CStyle::GetColor() const
{
	return m_color;
}

void CStyle::SetColor(RGBAColor color)
{
	m_color = color;
}
