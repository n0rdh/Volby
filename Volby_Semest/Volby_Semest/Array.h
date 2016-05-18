#pragma once

#include "DSRoutines.h"

#include "Vector.h"
#include "Structure.h"

namespace DS 
{
	template<typename T> 
	class Array	: 
		public Structure
	{
	public:
		static void copy(const Array<T>& src, const int srcStartIndex,
			Array<T>& dest, const int destStartIndex, const int length);

		Array(const size_t size);
		Array(const Array<T>& dalsi);
		~Array() override;
		
		Structure* clone() const override;
		Structure& operator=(const Structure& dalsi) override;
		Array<T>& operator=(const Array<T>& dalsi);
		bool Array<T>::operator==(const Array<T>& dalsi);

		size_t size() const;
		T& operator[](const int index);
		const T operator[](const int index) const;

	private:
		Vector* vector_;
		size_t size_;

	private:
		int mapArrayIndexToVectorIndex(const int index) const;
	};

	template<typename T>
	Array<T>::Array(const size_t size)
		: vector_(new Vector(size * sizeof(T))), size_(size)
	{
	}

	template<typename T>
	Array<T>::Array(const Array<T>& dalsi)
		: vector_(new Vector(*dalsi.vector_)), size_(dalsi.size_)
	{
	}

	template<typename T>
	Array<T>::~Array()
	{
		delete vector_;
	}

	template<typename T>
	Structure* Array<T>::clone() const
	{
		return new Array<T>(*this);
	}

	template<typename T>
	bool Array<T>::operator==(const Array<T>& dalsi)
	{
		return *vector_ == *dalsi.vector_;
	}

	template<typename T>
	Structure& Array<T>::operator=(const Structure& dalsi)
	{
		return (*this) = dynamic_cast<const Array&>(dalsi);
	}

	template<typename T>
	Array<T>& Array<T>::operator=(const Array<T>& dalsi)
	{
		if (this != &dalsi)
		{
			if (size_ != dalsi.size_)
			{
				throw invalid_argument("array sizes do not match");
			}

			*vector_ = *dalsi.vector_;
		}

		return *this;
	}
	
	template<typename T>
	size_t Array<T>::size() const
	{
		return size_;
	}

	template<typename T>
	T& Array<T>::operator[](const int index)
	{
		DSRoutines::rangeCheck(index, size_, true,
			&string("index out of range"));

		int vectorIndex = mapArrayIndexToVectorIndex(index);
		byte *itemPointer = vector_->getByteAddress(vectorIndex);
		return *(reinterpret_cast<T *>(itemPointer));
	}

	template<typename T>
	const T Array<T>::operator[](const int index) const
	{
		DSRoutines::rangeCheck(index, size_, true,
			&string("index out of range"));

		int vectorIndex = mapArrayIndexToVectorIndex(index);
		byte *itemPointer = vector_->getByteAddress(vectorIndex);
		return *(reinterpret_cast<T *>(itemPointer));
	}

	template<typename T>
	void Array<T>::copy(const Array<T>& src, const int srcStartIndex,
		Array<T>& dest, const int destStartIndex, const int length)
	{
		Vector::copy(*src.vector_,
			src.mapArrayIndexToVectorIndex(srcStartIndex),
			*dest.vector_,
			dest.mapArrayIndexToVectorIndex(destStartIndex),
			length * sizeof(T));
	}

	template<typename T>
	inline int Array<T>::mapArrayIndexToVectorIndex(const int index) const
	{
		DSRoutines::rangeCheck(index, size_, true,
			&string("index out of range"));

		return index * sizeof(T);
	}
}

