#pragma once

namespace DS
{

	template<typename T>
	class Iterator;

#pragma region Iterable
	template<typename T>
	class Iterable
	{
	public:
		virtual Iterator<T> begin() const = 0;
		virtual Iterator<T> end() const = 0;
	};
#pragma endregion Iterable

#pragma region StructureIterator
	template<typename T>
	class StructureIterator
	{
	public:
		virtual ~StructureIterator();

		virtual bool operator!=(const StructureIterator<T>& dalsi) const = 0;
		virtual const T& operator*() const = 0;
		virtual const StructureIterator<T>& operator++() = 0;

		virtual StructureIterator<T>* clone() const = 0;
	};

	template<typename T>
	StructureIterator<T>::~StructureIterator()
	{
	}
#pragma endregion StructureIterator


#pragma region Iterator
	template<typename T>
	class Iterator
	{
	public:
		Iterator(const StructureIterator<T>& iterator);
		Iterator(const Iterator<T>& dalsi);
		virtual ~Iterator();

		virtual Iterator<T>& operator=(const Iterator<T>& dalsi);

		bool operator!=(const Iterator<T>& dalsi) const;
		const T& operator*() const;
		const Iterator<T>& operator++();
	private:
		StructureIterator<T>* structureIterator_;
	};

	template<typename T>
	Iterator<T>::Iterator(const StructureIterator<T>& iterator) :
		structureIterator_(iterator.clone())
	{
	}

	template<typename T>
	Iterator<T>::Iterator(const Iterator<T>& dalsi) :
		Iterator<T>(*(dalsi.structureIterator_))
	{
	}

	template<typename T>
	Iterator<T>::~Iterator()
	{
		delete structureIterator_;
		structureIterator_ = nullptr;
	}

	template<typename T>
	Iterator<T>& Iterator<T>::operator=(const Iterator<T>& dalsi)
	{
		if (this != &dalsi)
		{
			delete structureIterator_;
			structureIterator_ = dalsi.structureIterator_->clone();
		}
		return *this;
	}

	template<typename T>
	bool Iterator<T>::operator!=(const Iterator<T>& dalsi) const
	{
		return *structureIterator_ != *(dalsi.structureIterator_);
	}

	template<typename T>
	const T& Iterator<T>::operator*() const
	{
		return *(*structureIterator_);
	}

	template<typename T>
	const Iterator<T>& Iterator<T>::operator++()
	{
		++(*structureIterator_);
		return *this;
	}
#pragma endregion Iterator
}