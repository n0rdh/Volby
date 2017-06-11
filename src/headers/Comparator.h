#pragma once

#include "StructureItem.h"

namespace DS
{
	template <typename K, typename T>
	class Comparator
	{
	public:
		Comparator() { }
		virtual ~Comparator() { }

		virtual int compare(const TableItem<K, T>& first,
			const TableItem<K, T>& second) const = 0;
	};
}