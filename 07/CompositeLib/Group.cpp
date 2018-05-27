#include "stdafx.h"
#include "Group.h"
#include "IStyle.h"

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

CGroup::CGroup(std::vector<IShapePtr>&& shapes)
	: m_shapes(std::move(shapes))
	, m_fillStyle([this]() { return GetFillStyles(); })
	, m_lineStyle([this]() { return GetLineStyles(); })
{
}

CGroup::CGroup(const CGroup& other)
	: CGroup(CloneShapes(other.m_shapes))
{
}

FillStyleRange CGroup::GetFillStyles() const
{
	return m_shapes | boost::adaptors::transformed([](const IShapePtr& shape) -> IFillStyle& {
		return shape->GetFillStyle();
	});
}

LineStyleRange CGroup::GetLineStyles() const
{
	return m_shapes | boost::adaptors::transformed([](const IShapePtr& shape) -> ILineStyle& {
		return shape->GetLineStyle();
	});
}

RectD CGroup::GetFrame() const
{
	if (m_shapes.empty())
	{
		return RECT_ZERO;
	}

	auto getFrame = [](const IShapePtr& shape) {
		return shape->GetFrame();
	};

	auto unionRect = UnionRect<double>;

	auto tailShapes = boost::make_iterator_range(m_shapes.begin() + 1, m_shapes.end());
	return boost::accumulate(tailShapes | boost::adaptors::transformed(getFrame), getFrame(m_shapes.front()), unionRect);
}

void CGroup::SetFrame(const RectD& rect)
{
	auto oldFrame = GetFrame();

	double ratioX = rect.width / oldFrame.width;
	double ratioY = rect.height / oldFrame.height;

	for (auto& shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		double paddingX = shapeFrame.left - oldFrame.left;
		double paddingY = shapeFrame.top - oldFrame.top;

		shapeFrame.left = rect.left + paddingX * ratioX;
		shapeFrame.top = rect.top + paddingY * ratioY;
		shapeFrame.width *= ratioX;
		shapeFrame.height *= ratioY;

		shape->SetFrame(shapeFrame);
	}
}

ILineStyle& CGroup::GetLineStyle()
{
	return m_lineStyle;
}

const ILineStyle& CGroup::GetLineStyle() const
{
	return m_lineStyle;
}

IFillStyle& CGroup::GetFillStyle()
{
	return m_fillStyle;
}

const IFillStyle& CGroup::GetFillStyle() const
{
	return m_fillStyle;
}

void CGroup::Draw(ICanvas& canvas) const
{
	boost::for_each(m_shapes, [&canvas](const auto& shape) {
		shape->Draw(canvas);
	});
}

IGroupPtr CGroup::GetGroup()
{
	return shared_from_this();
}

size_t CGroup::GetShapesCount() const
{
	return m_shapes.size();
}

IShapePtr CGroup::GetShapeAtIndex(size_t index)
{
	return m_shapes.at(index);
}

void CGroup::InsertShape(const IShapePtr& shape, size_t index)
{
	auto it = index < m_shapes.size()
		? m_shapes.begin() + index
		: m_shapes.end();
	m_shapes.insert(it, shape);
}

void CGroup::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

IShapePtr CGroup::Clone() const
{
	return std::shared_ptr<CGroup>(new CGroup(*this));
}

void AddShape(IGroup& group, const IShapePtr& shape)
{
	group.InsertShape(shape, group.GetShapesCount());
}
