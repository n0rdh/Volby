#pragma once

#include "Structure.h"

namespace DS
{
	template<typename T> class Array;

	class Vector : public Structure
	{
		template<typename T> friend class DS::Array;
	public:
		Vector(size_t size);
		Vector(const Vector& dalsi);
		~Vector();

		Structure* clone() const override;

		Structure& operator=(const Structure& dalsi) override;
		Vector& operator=(const Vector& dalsi);
		bool operator==(const Vector& dalsi) const;

		size_t size() const;

		byte& operator[](const int index);
		byte  operator[](const int index) const;

		bool byteNthBitGet(int B, int n);
		byte byteNthBitTo0(int B, int n);
		byte byteNthBitTo1(int B, int n);
		byte byteNthBitToggle(int B, int n);
		
		byte& readBytes(const int index, const int count, byte& dest);

		static void copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length);
	protected:
		byte* getByteAddress(const int index) const;

	private:
		size_t size_;
		void* items_;
	};

}