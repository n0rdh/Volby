#pragma once

#include "TableList.h"
#include "ArrayList.h"

namespace DS
{
	template <typename K, typename T>
	class TableUnsorted :
		public TableList<K, T>
	{
	public:
		TableUnsorted(const CompareFunction<K> compare,
			bool suppressDuplicateChecks = false);
		TableUnsorted(const CompareFunction<K> compare, size_t capacity,
			bool suppressDuplicateChecks = false);
		TableUnsorted(const TableUnsorted<K, T>& other);

		Structure* clone() const override;
		virtual TableUnsorted<K, T>& operator=(const TableUnsorted<K, T>& other);

		void insert(const K& key, const T& value) override;
		T remove(const K& key) override;

		bool isSuppressDuplicateChecks() const;

	private:
		bool suppressDuplicateChecks_;
	};

	template<typename K, typename T>
	TableUnsorted<K, T>::TableUnsorted(const CompareFunction<K> compare,
		bool suppressDuplicateChecks) :
		TableList<K, T>(new ArrayList<TableItem<K, T>*>(), compare),
		suppressDuplicateChecks_(suppressDuplicateChecks)
	{
	}

	template<typename K, typename T>
	TableUnsorted<K, T>::TableUnsorted(const CompareFunction<K> compare,
		size_t capacity, bool suppressDuplicateChecks) :
		TableList<K, T>(new ArrayList<TableItem<K, T>*>(capacity), compare),
		suppressDuplicateChecks_(suppressDuplicateChecks)
	{
	}

	template<typename K, typename T>
	TableUnsorted<K, T>::TableUnsorted(const TableUnsorted<K, T>& other) :
		TableList<K, T>(dynamic_cast<List<TableItem<K, T>*>*>(other.list_->clone()),
			other.compare_),
		suppressDuplicateChecks_(other.suppressDuplicateChecks_)
	{
	}

	template<typename K, typename T>
	Structure * TableUnsorted<K, T>::clone() const
	{
		return new TableUnsorted(*this);
	}

	template<typename K, typename T>
	TableUnsorted<K, T>& TableUnsorted<K, T>::operator=(const TableUnsorted<K, T>& other)
	{
		TableList<K, T>::operator=(other);

		if (this != &other)
		{
			suppressDuplicateChecks_ = other.suppressDuplicateChecks_;
		}

		return *this;
	}

	template<typename K, typename T>
	void TableUnsorted<K, T>::insert(const K& key, const T& value)
	{
		if (suppressDuplicateChecks_)
		{
			append(key, value);
		}
		else
		{
			TableList<K, T>::insert(key, value);
		}
	}

	template<typename K, typename T>
	T TableUnsorted<K, T>::remove(const K & key)
	{
		const int index(indexOfKey(key));

		if (index == TableList<K, T>::NONEXISTENT_KEY)
		{
			throw std::invalid_argument("attempt to remove data at non-existent key");
		}

		const int lastIndex(static_cast<int>(list_->size() - 1));

		T data = (*list_)[index]->getData();

		if (lastIndex > 0)
		{
			(*list_)[index]->swap(*((*list_)[lastIndex]));
		}

		list_->removeAt(lastIndex);

		return data;
	}

	template<typename K, typename T>
	bool TableUnsorted<K, T>::isSuppressDuplicateChecks() const
	{
		return suppressDuplicateChecks_;
	}
}