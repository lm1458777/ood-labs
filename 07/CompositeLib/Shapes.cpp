#include "stdafx.h"
#include "Shapes.h"
#include "IShape.h"

namespace
{

auto CloneShapes(gsl::span<const IShapePtr> shapes)
{
	using namespace boost;
	return copy_range<std::vector<IShapePtr>>(shapes | adaptors::transformed([](const IShapePtr& shape) -> IShapePtr {
		return shape->Clone();
	}));
}

} // namespace

Shapes::Shapes(const Shapes& other)
	: m_shapes{ CloneShapes(other.m_shapes) }
{
}

Shapes& Shapes::operator=(const Shapes& other)
{
	if (std::addressof(other) != this)
	{
		m_shapes = CloneShapes(other.m_shapes);
	}
	return *this;
}

size_t Shapes::GetShapesCount() const
{
	return m_shapes.size();
}

IShapePtr Shapes::GetShapeAtIndex(size_t index) const
{
	return m_shapes.at(index);
}

void Shapes::InsertShape(const IShapePtr& shape, size_t index)
{
	auto it = index < m_shapes.size()
		? m_shapes.begin() + index
		: m_shapes.end();
	m_shapes.insert(it, shape);
}

void Shapes::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

void AddShape(IShapes& shapes, const IShapePtr& shape)
{
	shapes.InsertShape(shape, shapes.GetShapesCount());
}
