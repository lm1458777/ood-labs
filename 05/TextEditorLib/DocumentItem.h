#pragma once
#include "IDocumentItem.h"

class EmptyDocumentItem : public IDocumentItem
{
public:
	IConstParagraphPtr GetParagraph() const final;
	IParagraphPtr GetParagraph() final;

	IConstImagePtr GetImage() const final;
	IImagePtr GetImage() final;

protected:
	EmptyDocumentItem() = default;

	virtual IParagraphPtr GetParagraphImpl() const;
	virtual IImagePtr GetImageImpl() const;
};

class ParagraphDocumentItem final : public EmptyDocumentItem
{
public:
	explicit ParagraphDocumentItem(IParagraphPtr paragraph);
	void AcceptVisitor(IDocumentItemVisitor& visitor) const override;

protected:
	IParagraphPtr GetParagraphImpl() const override;

private:
	IParagraphPtr m_paragraph;
};

class ImageDocumentItem final : public EmptyDocumentItem
{
public:
	explicit ImageDocumentItem(IImagePtr image);
	void AcceptVisitor(IDocumentItemVisitor& visitor) const override;

protected:
	virtual IImagePtr GetImageImpl() const;

private:
	IImagePtr m_image;
};
