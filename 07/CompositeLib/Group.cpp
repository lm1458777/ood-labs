#include "stdafx.h"
#include "Group.h"

bool operator==(const IStylePtr& style1, const IStylePtr& style2)
{
	return style1 && style2
		&& style1->IsEnabled() == style2->IsEnabled()
		&& style1->GetColor() == style2->GetColor();
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

IStylePtr CGroup::GetLineStyle() const
{
	bool todo_fixme;
	IStylePtr lineStyle;
	if (!m_shapes.empty())
	{
		bool stylesEqual = std::all_of(m_shapes.cbegin(), m_shapes.cend(), [&](auto& shape) {
			return shape->GetLineStyle() == m_shapes.front()->GetLineStyle();
		});
		lineStyle = stylesEqual ? m_shapes.front()->GetLineStyle() : nullptr;
	}
	return lineStyle;
}

void CGroup::SetLineStyle(const IStylePtr& style)
{
	boost::for_each(m_shapes, [&style](const auto& shape) {
		shape->SetLineStyle(style);
	});
}

IStylePtr CGroup::GetFillStyle() const
{
	bool todo_fixme;
	IStylePtr fillStyle;
	if (!m_shapes.empty())
	{
		bool stylesEqual = std::all_of(m_shapes.cbegin(), m_shapes.cend(), [&](auto& shape) {
			return shape->GetFillStyle() == m_shapes.front()->GetFillStyle();
		});
		fillStyle = stylesEqual ? m_shapes.front()->GetFillStyle() : nullptr;
	}
	return fillStyle;
}

void CGroup::SetFillStyle(const IStylePtr& style)
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

void AddShape(IGroup& group, const IShapePtr& shape)
{
	group.InsertShape(shape, group.GetShapesCount());
}
