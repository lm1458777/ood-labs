#pragma once
#include <iosfwd>

// ѕространство имен современной графической библиотеки (недоступно дл€ изменени€)
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

//  ласс дл€ современного рисовани€ графики
class CModernGraphicsRenderer
{
public:
	explicit CModernGraphicsRenderer(std::ostream& strm);

	~CModernGraphicsRenderer();

	// Ётот метод должен быть вызван в начале рисовани€
	void BeginDraw();

	// ¬ыполн€ет рисование линии
	void DrawLine(const CPoint& start, const CPoint& end);

	// Ётот метод должен быть вызван в конце рисовани€
	void EndDraw();

private:
	std::ostream& m_out;
	bool m_drawing = false;
};

} // namespace modern_graphics_lib
