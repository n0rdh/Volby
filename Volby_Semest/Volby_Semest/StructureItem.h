#pragma once

namespace DS
{
#pragma region DataItem
	template<typename T>
	class DataItem
	{
	public:
		DataItem(const T& data);
		DataItem(const DataItem<T>& dalsi);
		virtual ~DataItem();
		T& getData();
		const T& getData() const;
		void setData(const T& data);
	private:
		T data_;
	};

	template<typename T>
	DataItem<T>::DataItem(const T& data) :
		data_(data)
	{
	}

	template<typename T>
	DataItem<T>::DataItem(const DataItem<T>& dalsi) :
		DataItem(dalsi.data_)
	{
	}

	template<typename T>
	DataItem<T>::~DataItem()
	{
	}

	template<typename T>
	T& DataItem<T>::getData()
	{
		return data_;
	}

	template<typename T>
	const T & DataItem<T>::getData() const
	{
		return data_;
	}

	template<typename T>
	void DataItem<T>::setData(const T & data)
	{
		data_ = data;
	}
#pragma endregion DataItem

#pragma region TableItem
	template<typename K, typename T>
	class TableItem :
		public DataItem<T>
	{
	public:
		TableItem(const K& key, const T& data);
		TableItem(const TableItem<K, T>& dalsi);
		~TableItem() override;
		const K& getKey() const;
		void swap(TableItem<K, T>& dalsi);
	private:
		K key_;
	};

	template<typename K, typename T>
	TableItem<K, T>::TableItem(const K& key, const T& data) :
		DataItem<T>(data),
		key_(key)
	{
	}

	template<typename K, typename T>
	TableItem<K, T>::TableItem(const TableItem<K, T>& dalsi) :
		DataItem<T>(dalsi),
		key_(dalsi.key_)
	{
	}

	template<typename K, typename T>
	TableItem<K, T>::~TableItem()
	{
	}

	template<typename K, typename T>
	const K& TableItem<K, T>::getKey() const
	{
		return key_;
	}

	template<typename K, typename T>
	void TableItem<K, T>::swap(TableItem<K, T>& dalsi)
	{
		K tmpKey = key_;
		T tmpData = getData();
		
		key_ = dalsi.key_;
		setData(dalsi.getData());

		dalsi.key_ = tmpKey;
		dalsi.setData(tmpData);
	}
#pragma endregion TableItem
}