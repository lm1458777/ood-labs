#pragma once
#include "IDocument.h"
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/irange.hpp>

inline auto GetItemRange(const IDocument& doc)
{
	return boost::irange(static_cast<size_t>(0), doc.GetItemsCount())
		| boost::adaptors::transformed([&doc](size_t i) { return doc.GetItem(i); });
}

template <class Visitor>
void VisitItems(const IDocument& doc, Visitor&& v)
{
	for (const auto& item : GetItemRange(doc))
	{
		item->AcceptVisitor(v);
	}
}
