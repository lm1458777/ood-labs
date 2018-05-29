#pragma once
#include "IShapes.h"

class Shapes final : public IShapes
{
public:
	Shapes() = default;

	Shapes(const Shapes& other);
	Shapes& operator=(const Shapes& other);

	Shapes(Shapes&&) = default;
	Shapes& operator=(Shapes&&) = default;

	size_t GetShapesCount() const override;
	IShapePtr GetShapeAtIndex(size_t index) const override;
	void InsertShape(const IShapePtr& shape, size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	std::vector<IShapePtr> m_shapes;
};
