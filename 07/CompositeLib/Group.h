#pragma once
#include "IGroup.h"

class CGroup
	: public IGroup
	, public std::enable_shared_from_this<IGroup>
{
public:
	CGroup() = default;
	CGroup(const CGroup& other);
	CGroup& operator=(const CGroup& other) = delete;

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	ILineStylePtr GetLineStyle() const override;
	void SetLineStyle(const ILineStylePtr& style) override;

	IFillStylePtr GetFillStyle() const override;
	void SetFillStyle(const IFillStylePtr& style) override;

	void Draw(ICanvas& canvas) const override;

	IGroupPtr GetGroup() override;

	size_t GetShapesCount() const override;
	IShapePtr GetShapeAtIndex(size_t index) override;
	void InsertShape(const IShapePtr& shape, size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	IShapeUniquePtr Clone() const override;

private:
	std::vector<IShapePtr> m_shapes;
};
