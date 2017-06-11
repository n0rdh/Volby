#pragma once

#include "TableList.h"
#include "ArrayList.h"

namespace DS
{
	template <typename K, typename T>
	class TableSorted :
		public TableList<K, T>
	{
	public:
		TableSorted(const CompareFunction<K> compare);
		TableSorted(const TableSorted<K, T>& dalsi);

		Structure* clone() const override;
		virtual TableSorted<K, T>& operator=(const TableSorted<K, T>& dalsi);

	protected:
		virtual int indexOfKey(const K& key) const override;
	};


	template<typename K, typename T>
	TableSorted<K, T>::TableSorted(const CompareFunction<K> compare) :
		TableList<K, T>(new ArrayList<TableItem<K, T>*>(), compare)
	{
	}

	template<typename K, typename T>
	TableSorted<K, T>::TableSorted(const TableSorted<K, T>& dalsi) :
		TableList<K, T>(dynamic_cast<List<TableItem<K, T>*>*>(dalsi.list_->clone()), dalsi.compare_)
	{
	}

	template<typename K, typename T>
	Structure * TableSorted<K, T>::clone() const
	{
		return new TableSorted<K, T>(*this);
	}

	template<typename K, typename T>
	TableSorted<K, T>& TableSorted<K, T>::operator=(const TableSorted<K, T>& dalsi)
	{
		TableList<K, T>::operator=(dalsi);

		return *this;
	}

	template<typename K, typename T>
	int TableSorted<K, T>::indexOfKey(const K& key) const
	{
		int startIndex(0);
		int stopIndex(static_cast<int>(list_->size()));

		while (startIndex < stopIndex)
		{
			const int index(startIndex + ((stopIndex - startIndex) >> 1));

			if (compare_(key, (*list_)[index]->getKey()) < 0)
			{
				startIndex = index + 1;
			}
			else
			{
				stopIndex = index;
			}
		}

		return stopIndex;
	}
}