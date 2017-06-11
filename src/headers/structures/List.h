#pragma once

#include "Structure.h"
#include "Iterator.h"

namespace DS
{
	template<typename T>
	class List :
		public Structure,
		public Iterable<T>
	{
	public:
		virtual ~List();

		virtual Structure* clone() const = 0;
		virtual Structure& operator=(const Structure& dalsi);
		virtual List<T>& operator=(const List<T>& dalsi);

		virtual size_t size() const = 0;
		virtual T& operator[](const int index) = 0;
		virtual const T& operator[](const int index) const = 0;

		virtual void add(const T& data) = 0;
		virtual void insert(const T& data, const int index) = 0;
		virtual bool tryRemove(const T& data) = 0;
		virtual T& removeAt(const int index) = 0;
		virtual int getIndexOf(const T& data) = 0;
		virtual void clear() = 0;

		virtual Iterator<T> begin() const = 0;
		virtual Iterator<T> end() const = 0;
	protected:
		EqualityFunction<T> equalityFunction_;

		List(const EqualityFunction<T>& equalityFunction);
		List(const List<T>& dalsi);
	};

	template<typename T>
	List<T>::List(const EqualityFunction<T>& equalityFunction) :
		Structure(),
		equalityFunction_(equalityFunction)
	{
	}

	template<typename T>
	List<T>::List(const List<T>& dalsi) :
		Structure(),
		equalityFunction_(dalsi.equalityFunction_)
	{
	}

	template<typename T>
	List<T>::~List()
	{
		equalityFunction_ = nullptr;
	}

	template<typename T>
	Structure & List<T>::operator=(const Structure& dalsi)
	{
		return (*this) = dynamic_cast<const List<T>&>(dalsi);
	}

	template<typename T>
	List<T>& List<T>::operator=(const List<T>& dalsi)
	{
		equalityFunction_ = dalsi.equalityFunction_;
		return *this;
	}

}