#pragma once

#include "Table.h"
#include "List.h"

#include <stdexcept>

namespace DS
{
	template <typename K, typename T>
	class TableList :
		public Table<K, T>
	{
	public:
		~TableList() override;

		virtual Structure* clone() const = 0;
		Structure& operator=(const Structure& dalsi) override;
		Table<K, T>& operator=(const Table<K, T>& dalsi) override;
		virtual TableList<K, T>& operator=(const TableList<K, T>& dalsi);

		size_t size() const override;
		T& operator[](const K& key) override;
		const T& operator[](const K& key) const override;

		void insert(const K& key, const T& value) override;
		T remove(const K& key) override;
		bool tryFind(const K& key, T& value) const override;
		void clear() override;

		Iterator<TableItem<K, T>*> begin() const override;
		Iterator<TableItem<K, T>*> end() const override;

	protected:
		static const int NONEXISTENT_KEY = -1;

		TableList(List<TableItem<K, T>*>* list, const CompareFunction<K> compare);

		void append(const K& key, const T& value);

		virtual int indexOfKey(const K& key) const;

		List<TableItem<K, T>*>* list_;

	private:
		T& getDataAt(const K& key) const;
	};

	template<typename K, typename T>
	TableList<K, T>::~TableList()
	{
		clear();
		compare_ = nullptr;

		delete list_;
	}

	template<typename K, typename T>
	Structure & TableList<K, T>::operator=(const Structure & dalsi)
	{
		return (*this) = dynamic_cast<const TableList&>(dalsi);
	}

	template<typename K, typename T>
	Table<K, T>& TableList<K, T>::operator=(const Table<K, T>& dalsi)
	{
		return (*this) = dynamic_cast<const TableList&>(dalsi);
	}

	template<typename K, typename T>
	TableList<K, T>& TableList<K, T>::operator=(const TableList<K, T>& dalsi)
	{
		if (this != &dalsi)
		{
			clear();

			for (auto item : *dalsi.list_)
			{
				list_->add(new TableItem<K, T>(*item));
			}
		}

		return *this;
	}

	template<typename K, typename T>
	size_t TableList<K, T>::size() const
	{
		return list_->size();
	}

	template<typename K, typename T>
	T & TableList<K, T>::operator[](const K & key)
	{
		return getDataAt(key);
	}

	template<typename K, typename T>
	const T & TableList<K, T>::operator[](const K & key) const
	{
		return getDataAt(key);
	}

	template<typename K, typename T>
	void TableList<K, T>::insert(const K & key, const T & value)
	{
		const int index(indexOfKey(key));
		TableItem<K, T>* newItem(new TableItem<K, T>(key, value));

		if ((index == NONEXISTENT_KEY) || (index == list_->size()))
		{
			list_->add(newItem);
		}
		else
		{
			list_->insert(newItem, index);
		}
	}

	template<typename K, typename T>
	T TableList<K, T>::remove(const K & key)
	{
		const int index(indexOfKey(key));

		if (index == NONEXISTENT_KEY)
		{
			throw invalid_argument("attempt to remove data at non-existent key");
		}

		T data = (*list_)[index]->getData();
		delete (*list_)[index];
		list_->removeAt(index);

		return data;
	}

	template<typename K, typename T>
	bool TableList<K, T>::tryFind(const K & key, T & value) const
	{
		const int index(indexOfKey(key));

		if ((index != NONEXISTENT_KEY) &&
			(index < static_cast<int>(list_->size())))
		{
			if (compare_(key, (*list_)[index]->getKey()) == 0)
			{
				value = (*list_)[index]->getData();
				return true;
			}
		}

		return false;
	}

	template<typename K, typename T>
	void TableList<K, T>::clear()
	{
		for (auto item : *list_)
		{
			delete item;
		}

		list_->clear();
	}

	template<typename K, typename T>
	Iterator<TableItem<K, T>*> TableList<K, T>::begin() const
	{
		return list_->begin();
	}

	template<typename K, typename T>
	Iterator<TableItem<K, T>*> TableList<K, T>::end() const
	{
		return list_->end();
	}

	template<typename K, typename T>
	TableList<K, T>::TableList(List<TableItem<K, T>*>* list, const CompareFunction<K> compare) :
		Table<K, T>(compare), list_(list)
	{
	}

	template<typename K, typename T>
	void TableList<K, T>::append(const K& key, const T& value)
	{
		// WARNING! No checking for duplicates. Implemented for optimizational purposes.
		list_->add(new TableItem<K, T>(key, value));
	}

	template<typename K, typename T>
	int TableList<K, T>::indexOfKey(const K & key) const
	{
		auto index(0);

		for (auto item : *list_)
		{
			if (compare_(item->getKey(), key) == 0)
			{
				return index;
			}

			index++;
		}

		return NONEXISTENT_KEY;
	}

	template<typename K, typename T>
	T & TableList<K, T>::getDataAt(const K& key) const
	{
		const int index(indexOfKey(key));

		if (index == NONEXISTENT_KEY)
		{
			throw invalid_argument("attempt to access a non-existent key");
		}

		return (*list_)[index]->getData();
	}
}