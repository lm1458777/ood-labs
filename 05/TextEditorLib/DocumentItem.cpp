#include "stdafx.h"
#include "DocumentItem.h"
#include "IDocumentItemVisitor.h"

#pragma region EmptyDocumentItem
IConstParagraphPtr EmptyDocumentItem::GetParagraph() const
{
	return GetParagraphImpl();
}

IParagraphPtr EmptyDocumentItem::GetParagraph()
{
	return GetParagraphImpl();
}

IConstImagePtr EmptyDocumentItem::GetImage() const
{
	return GetImageImpl();
}

IImagePtr EmptyDocumentItem::GetImage()
{
	return GetImageImpl();
}

IParagraphPtr EmptyDocumentItem::GetParagraphImpl() const
{
	return nullptr;
}

IImagePtr EmptyDocumentItem::GetImageImpl() const
{
	return nullptr;
}

#pragma endregion

#pragma region ParagraphDocumentItem
ParagraphDocumentItem::ParagraphDocumentItem(IParagraphPtr paragraph)
	: m_paragraph(std::move(paragraph))
{
	if (!m_paragraph)
	{
		throw std::invalid_argument("Paragraph must not be null");
	}
}

void ParagraphDocumentItem::AcceptVisitor(IDocumentItemVisitor& visitor) const
{
	visitor.VisitParagraph(*m_paragraph);
}

IParagraphPtr ParagraphDocumentItem::GetParagraphImpl() const
{
	return m_paragraph;
}

#pragma endregion

#pragma region ImageDocumentItem
ImageDocumentItem::ImageDocumentItem(IImagePtr image)
	: m_image(std::move(image))
{
	if (!m_image)
	{
		throw std::invalid_argument("Image must not be null");
	}
}

void ImageDocumentItem::AcceptVisitor(IDocumentItemVisitor& visitor) const
{
	visitor.VisitImage(*m_image);
}

IImagePtr ImageDocumentItem::GetImageImpl() const
{
	return m_image;
}

#pragma endregion
