#include "stdafx.h"
#include "Group.h"
#include "IStyle.h"
#include "ShapeRange.h"

using boost::adaptors::transformed;

CGroup::CGroup(const Shapes& shapes)
	: m_shapes(shapes)
	, m_fillStyle([this]() { return GetFillStyles(); })
	, m_lineStyle([this]() { return GetLineStyles(); })
{
}

CGroup::CGroup(const CGroup& other)
	: CGroup(other.m_shapes)
{
}

auto CGroup::GetShapeRange() const
{
	return ::GetShapeRange(m_shapes);
}

FillStyleRange CGroup::GetFillStyles() const
{
	return GetShapeRange() | transformed([](const IShapePtr& shape) -> IFillStyle& {
		return shape->GetFillStyle();
	});
}

LineStyleRange CGroup::GetLineStyles() const
{
	return GetShapeRange() | transformed([](const IShapePtr& shape) -> ILineStyle& {
		return shape->GetLineStyle();
	});
}

RectD CGroup::GetFrame() const
{
	auto shapes = GetShapeRange();
	if (shapes.begin() == shapes.end())
	{
		return RECT_ZERO;
	}

	auto getFrame = [](const IShapePtr& shape) {
		return shape->GetFrame();
	};

	auto unionRect = UnionRect<double>;

	auto headFrame = getFrame(*shapes.begin());
	auto tailFrames = boost::make_iterator_range(++shapes.begin(), shapes.end()) | transformed(getFrame);
	return boost::accumulate(tailFrames, headFrame, unionRect);
}

void CGroup::SetFrame(const RectD& rect)
{
	auto oldFrame = GetFrame();

	double ratioX = rect.width / oldFrame.width;
	double ratioY = rect.height / oldFrame.height;

	auto updateFrame = [=](const IShapePtr& shape) {
		auto shapeFrame = shape->GetFrame();
		double paddingX = shapeFrame.left - oldFrame.left;
		double paddingY = shapeFrame.top - oldFrame.top;

		shapeFrame.left = rect.left + paddingX * ratioX;
		shapeFrame.top = rect.top + paddingY * ratioY;
		shapeFrame.width *= ratioX;
		shapeFrame.height *= ratioY;

		shape->SetFrame(shapeFrame);
	};

	boost::for_each(GetShapeRange(), updateFrame);
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
	boost::for_each(GetShapeRange(), [&canvas](const auto& shape) {
		shape->Draw(canvas);
	});
}

IGroupPtr CGroup::GetGroup()
{
	return shared_from_this();
}

size_t CGroup::GetShapesCount() const
{
	return m_shapes.GetShapesCount();
}

IShapePtr CGroup::GetShapeAtIndex(size_t index) const
{
	return m_shapes.GetShapeAtIndex(index);
}

void CGroup::InsertShape(const IShapePtr& shape, size_t index)
{
	m_shapes.InsertShape(shape, index);
}

void CGroup::RemoveShapeAtIndex(size_t index)
{
	m_shapes.RemoveShapeAtIndex(index);
}

IShapePtr CGroup::Clone() const
{
	return std::shared_ptr<CGroup>(new CGroup(*this));
}
