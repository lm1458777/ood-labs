#include "stdafx.h"
#include "Group.h"
#include "IStyle.h"

namespace
{

bool operator==(const IFillStylePtr& style1, const IFillStylePtr& style2)
{
	bool use_shared_ptr_eq;

	return style1 && style2
		&& style1->IsEnabled() == style2->IsEnabled()
		&& style1->GetColor() == style2->GetColor();
}

bool operator==(const ILineStylePtr& style1, const ILineStylePtr& style2)
{
	return style1 && style2
		&& style1->IsEnabled() == style2->IsEnabled()
		&& style1->GetColor() == style2->GetColor()
		&& style1->GetWidth() == style2->GetWidth();
}

auto CloneShapes(gsl::span<const IShapePtr> shapes)
{
	using namespace boost;
	return copy_range<std::vector<IShapePtr>>(shapes | adaptors::transformed([](const IShapePtr& shape) -> IShapePtr {
		return shape->Clone();
	}));
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
	bool todo_fixme;
	ILineStylePtr lineStyle;
	if (!m_shapes.empty())
	{
		bool stylesEqual = std::all_of(m_shapes.cbegin(), m_shapes.cend(), [&](auto& shape) {
			return shape->GetLineStyle() == m_shapes.front()->GetLineStyle();
		});
		lineStyle = stylesEqual ? m_shapes.front()->GetLineStyle() : nullptr;
	}
	return lineStyle;
}

void CGroup::SetLineStyle(const ILineStylePtr& style)
{
	boost::for_each(m_shapes, [&style](const auto& shape) {
		shape->SetLineStyle(style);
	});
}

IFillStylePtr CGroup::GetFillStyle() const
{
	bool todo_fixme;
	IFillStylePtr fillStyle;
	if (!m_shapes.empty())
	{
		bool stylesEqual = std::all_of(m_shapes.cbegin(), m_shapes.cend(), [&](auto& shape) {
			return shape->GetFillStyle() == m_shapes.front()->GetFillStyle();
		});
		fillStyle = stylesEqual ? m_shapes.front()->GetFillStyle() : nullptr;
	}
	return fillStyle;
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
	bool TODO_CHECK_GT_GE;

	if (index > m_shapes.size())
	{
		throw std::out_of_range("out of range");
	}

	m_shapes.insert(m_shapes.begin() + index, shape);
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
	return std::make_shared<CGroup>(*this);
}

void AddShape(IGroup& group, const IShapePtr& shape)
{
	group.InsertShape(shape, group.GetShapesCount());
}
