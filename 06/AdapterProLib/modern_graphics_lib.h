#pragma once
#include <iosfwd>
#include <tuple>

// ������������ ���� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib
{

class CPoint
{
public:
	constexpr CPoint(int x, int y)
		: x(x)
		, y(y)
	{
	}

	int x;
	int y;
};

inline bool operator==(CPoint pt1, CPoint pt2)
{
	return pt1.x == pt2.x
		&& pt1.y == pt2.y;
}

inline bool operator!=(CPoint pt1, CPoint pt2)
{
	return !(pt1 == pt2);
}

// ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
	}
	float r, g, b, a;
};

inline bool operator==(const CRGBAColor& left, const CRGBAColor& right)
{
	auto rank = [](const CRGBAColor& color) {
		return std::make_tuple(color.r, color.b, color.g, color.a);
	};

	return rank(left) == rank(right);
}

inline bool operator!=(const CRGBAColor& left, const CRGBAColor& right)
{
	return !(left == right);
}

// ����� ��� ������������ ��������� �������
class CModernGraphicsRenderer
{
public:
	explicit CModernGraphicsRenderer(std::ostream& strm);

	~CModernGraphicsRenderer();

	// ���� ����� ������ ���� ������ � ������ ���������
	void BeginDraw();

	// ��������� ��������� �����
	void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color);

	// ���� ����� ������ ���� ������ � ����� ���������
	void EndDraw();

private:
	std::ostream& m_out;
	bool m_drawing = false;
};

} // namespace modern_graphics_lib
