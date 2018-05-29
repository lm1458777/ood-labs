#pragma once
#include "GroupStyle.h"
#include "IGroup.h"
#include "Shapes.h"

class CGroup
	: public IGroup
	, public std::enable_shared_from_this<IGroup>
{
public:
	static auto Create()
	{
		return std::shared_ptr<CGroup>(new CGroup());
	}

	IShapePtr Clone() const override;

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	ILineStyle& GetLineStyle() override;
	const ILineStyle& GetLineStyle() const override;

	IFillStyle& GetFillStyle() override;
	const IFillStyle& GetFillStyle() const override;

	void Draw(ICanvas& canvas) const override;

	IGroupPtr GetGroup() override;

	size_t GetShapesCount() const override;
	IShapePtr GetShapeAtIndex(size_t index) const override;
	void InsertShape(const IShapePtr& shape, size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	explicit CGroup(const Shapes& shapes = {});
	CGroup(const CGroup& other);

	FillStyleRange GetFillStyles() const;
	LineStyleRange GetLineStyles() const;

	auto GetShapeRange() const;

private:
	Shapes m_shapes;
	GroupFillStyle m_fillStyle;
	GroupLineStyle m_lineStyle;
};
