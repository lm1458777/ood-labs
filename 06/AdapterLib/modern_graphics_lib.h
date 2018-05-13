#pragma once
#include <iosfwd>

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

// ����� ��� ������������ ��������� �������
class CModernGraphicsRenderer
{
public:
	explicit CModernGraphicsRenderer(std::ostream& strm);

	~CModernGraphicsRenderer();

	// ���� ����� ������ ���� ������ � ������ ���������
	void BeginDraw();

	// ��������� ��������� �����
	void DrawLine(const CPoint& start, const CPoint& end);

	// ���� ����� ������ ���� ������ � ����� ���������
	void EndDraw();

private:
	std::ostream& m_out;
	bool m_drawing = false;
};

} // namespace modern_graphics_lib
