#pragma once
#include "IGroup.h"

class CGroup
	: public IGroup
	, public std::enable_shared_from_this<IGroup>
{
public:
	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	IStylePtr GetLineStyle() const override;
	void SetLineStyle(const IStylePtr& style) override;

	IStylePtr GetFillStyle() const override;
	void SetFillStyle(const IStylePtr& style) override;

	void Draw(ICanvas& canvas) const override;

	IGroupPtr GetGroup() override;

	size_t GetShapesCount() const override;
	IShapePtr GetShapeAtIndex(size_t index) override;
	void InsertShape(const IShapePtr& shape, size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	std::vector<IShapePtr> m_shapes;
};
