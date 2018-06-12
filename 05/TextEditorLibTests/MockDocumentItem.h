#pragma once
#include "../TextEditorLib/IDocumentItem.h"

struct MockDocumentItem : IDocumentItem
{
	IParagraphPtr GetParagraph() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	IConstParagraphPtr GetParagraph() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	IImagePtr GetImage() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	IConstImagePtr GetImage() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void AcceptVisitor(IDocumentItemVisitor& /*visitor*/) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
};

inline auto CreateMockItem()
{
	return std::make_shared<MockDocumentItem>();
}
