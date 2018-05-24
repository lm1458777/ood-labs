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

template <class T, class StyleGetter>
T GetStyle(gsl::span<const IShapePtr> shapes, StyleGetter styleGetter)
{
	if (shapes.empty())
	{
		return T{};
	}

	auto getStyle = [styleGetter](const IShapePtr& shape) {
		return std::invoke(styleGetter, *shape);
	};

	T style = getStyle(shapes.at(0));
	if (shapes.size() == 1)
	{
		return style;
	}

	bool allShapesHasSameStyle = all_of(shapes.begin() + 1, shapes.end(), [&style, getStyle](const IShapePtr& shape) {
		return getStyle(shape) == style;
	});

	return allShapesHasSameStyle ? style : T{};
}

} // namespace

CGroup::CGroup(const CGroup& other)
	: m_shapes(CloneShapes(other.m_shapes))
{
}

RectD CGroup::GetFrame() const
{
	RectD frame = {
		std::numeric_limits<double>::infinity(),
		std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity()
	};
	double maxRight = 0;
	double maxBottom = 0;
	for (const auto& shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		frame.left = std::min(shapeFrame.left, frame.left);
		frame.top = std::min(shapeFrame.top, frame.top);
		maxRight = std::max(shapeFrame.width + shapeFrame.left, maxRight);
		maxBottom = std::max(shapeFrame.height + shapeFrame.top, maxBottom);
	}
	frame.width = maxRight - frame.left;
	frame.height = maxBottom - frame.top;

	return frame;
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

ILineStylePtr CGroup::GetLineStyle() const
{
	return GetStyle<ILineStylePtr>(m_shapes, &IShape::GetLineStyle);
}

void CGroup::SetLineStyle(const ILineStylePtr& style)
{
	boost::for_each(m_shapes, [&style](const auto& shape) {
		shape->SetLineStyle(style);
	});
}

IFillStylePtr CGroup::GetFillStyle() const
{
	return GetStyle<IFillStylePtr>(m_shapes, &IShape::GetFillStyle);
}

void CGroup::SetFillStyle(const IFillStylePtr& style)
{
	boost::for_each(m_shapes, [&style](const auto& shape) {
		shape->SetFillStyle(style);
	});
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
