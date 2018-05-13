#pragma once

namespace graphics_lib
{
class ICanvas;
}

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{

struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;
	virtual ~ICanvasDrawable() = default;
};

using Color = uint32_t;

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point& p1, const Point& p2, const Point& p3, Color color = 0);

	void Draw(graphics_lib::ICanvas& canvas) const override;

private:
	Point m_points[3];
	Color m_color = 0;
};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point& leftTop, int width, int height, Color color = 0);

	void Draw(graphics_lib::ICanvas& canvas) const override;

private:
	Point m_leftTop;
	Point m_rightBottom;
	Color m_color = 0;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas& canvas);
	void Draw(const ICanvasDrawable& drawable);

private:
	graphics_lib::ICanvas& m_canvas;
};

} // namespace shape_drawing_lib
