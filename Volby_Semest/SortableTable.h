#pragma once

#include "Comparator.h"
#include "TableUnsorted.h"
#include "DSRoutines.h"

namespace DS
{
	template <typename K, typename T>
	class SortableTable :
		public TableUnsorted<K, T>
	{
	public:
		SortableTable(bool suppressDuplicateChecks = false);
		SortableTable(size_t capacity, bool suppressDuplicateChecks = false);
		SortableTable(const SortableTable& dalsi);

		void sort(const Comparator<K, T>& comparator);

	private:
		void buildHeap(const Comparator<K, T>& comparator);
		void popFromHeap(const Comparator<K, T>& comparator);
	};

	template<typename K, typename T>
	SortableTable<K, T>::SortableTable(bool suppressDuplicateChecks) :
		TableUnsorted<K, T>(functionCompare, suppressDuplicateChecks)
	{
	}

	template<typename K, typename T>
	SortableTable<K, T>::SortableTable(size_t capacity, bool suppressDuplicateChecks) :
		TableUnsorted<K, T>(functionCompare, capacity, suppressDuplicateChecks)
	{
	}

	template<typename K, typename T>
	SortableTable<K, T>::SortableTable(const SortableTable& dalsi) :
		TableUnsorted<K, T>(dalsi)
	{
	}

	template<typename K, typename T>
	void SortableTable<K, T>::sort(const Comparator<K, T>& comparator)
	{
		buildHeap(comparator);
		popFromHeap(comparator);
	}

	template<typename K, typename T>
	void SortableTable<K, T>::buildHeap(const Comparator<K, T>& comparator)
	{
		bool swapped;

		for (auto i(1); i < static_cast<int>(list_->size()); i++)
		{
			int currIndex(i);

			do {
				const int parent((currIndex - 1) >> 1);
				swapped = false;

				if ((currIndex > 0) &&															
					((comparator.compare(*(*list_)[currIndex], *(*list_)[parent])) > 0))
				{
					DSRoutines::swap<TableItem<K, T>*>((*list_)[currIndex], (*list_)[parent]);
					currIndex = parent;
					swapped = true;
				}
			} while (swapped);
		}
	}

	template<typename K, typename T>
	void SortableTable<K, T>::popFromHeap(const Comparator<K, T>& comparator)
	{
		bool swapped;

		for (auto i(static_cast<int>(list_->size() - 1)); i > 0; i--)
		{
			DSRoutines::swap<TableItem<K, T>*>((*list_)[0], (*list_)[i]);

			int currIndex(0);

			do
			{
				swapped = false;
				
				const int left((currIndex << 1) + 1);
				const int right((currIndex << 1) + 2);
				int max;

				if ((left < i) && (right < i))
				{
					max = (comparator.compare(*(*list_)[left], *(*list_)[right]) > 0) ? left : right;
				}
				else
				{
					max = (left < i) ? left : right;
				}

				if ((max < i) &&
					(comparator.compare(*(*list_)[max], *(*list_)[currIndex]) > 0))
				{
					DSRoutines::swap<TableItem<K, T>*>((*list_)[max], (*list_)[currIndex]);
					currIndex = max;
					swapped = true;
				}
			} while (swapped);
		}
	}
}