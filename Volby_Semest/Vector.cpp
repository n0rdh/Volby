#include <cstdlib>
#include <cstring>

#include "Vector.h"
#include "DSRoutines.h"

using namespace std;
using namespace DS;

Vector::Vector(size_t size) :
	size_(size), items_(calloc(size_, 1))
{
}

Vector::Vector(const Vector& dalsi) :
	Vector(dalsi.size_)
{
	memcpy(items_, dalsi.items_, size_);
}

Vector::~Vector()
{
	free(items_);
}

Structure* Vector::clone() const
{
	return new Vector(*this);
}

Structure & Vector::operator=(const Structure & dalsi)
{
	return (*this) = dynamic_cast<const Vector&>(dalsi);
}

Vector& Vector::operator=(const Vector& dalsi)
{
	size_ = dalsi.size_;
	items_ = realloc(items_, size_);
	memcpy(items_, dalsi.items_, size_);

	return *this;
}

bool Vector::operator==(const Vector& dalsi) const
{
	if (size_ != dalsi.size_)
	{
		return false;
	}

	return memcmp(items_, dalsi.items_, size_) == 0;
}

size_t Vector::size() const
{
	return size_;
}

byte& Vector::operator[](const int index)
{
	DSRoutines::rangeCheck(index, size_, true,
		&string("index out of range"));

	return *(reinterpret_cast<byte *>(items_) + index);
}

byte Vector::operator[](const int index) const
{
	DSRoutines::rangeCheck(index, size_, true,
		&string("index out of range"));

	return *(reinterpret_cast<byte *>(items_) + index);
}

bool Vector::byteNthBitGet(int B, int n)
{
	return ((*this)[B] >> n) & 1;
}

byte Vector::byteNthBitTo0(int B, int n)
{
	return (*this)[B] &= ~(1 << n);
}

byte Vector::byteNthBitTo1(int B, int n)
{
	return (*this)[B] |= 1 << n;
}

byte Vector::byteNthBitToggle(int B, int n)
{
	return (*this)[B] ^= 1 << n;
}

byte& Vector::readBytes(const int index, const int count, byte& dest)
{
	DSRoutines::rangeCheck(index + count, size_, true,
		&string("invalid index"));

	memcpy(&dest, getByteAddress(index), count);

	return dest;
}

void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest,
	const int destStartIndex, const int length)
{
	int maxStartIndex = srcStartIndex + length;
	int maxDestIndex = destStartIndex + length;

	DSRoutines::rangeCheck(srcStartIndex && maxStartIndex, src.size(), true,
		&string("invalid source start index"));
	DSRoutines::rangeCheck(destStartIndex && maxDestIndex, dest.size(), true,
		&string("invalid destination start index"));

	// OverlDSing data
	if ((src == dest) && ((maxStartIndex >= destStartIndex) ||
		(maxDestIndex >= srcStartIndex)))
	{
		memmove(dest.getByteAddress(destStartIndex),
			src.getByteAddress(srcStartIndex), length);
	}
	else
	{
		memcpy(dest.getByteAddress(destStartIndex),
			src.getByteAddress(srcStartIndex), length);
	}
}

byte* Vector::getByteAddress(const int index) const
{
	DSRoutines::rangeCheck(index, size_, true,
		&string("index out of range"));

	return static_cast<byte *>(items_) + index;
}
