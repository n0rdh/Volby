#pragma once

namespace DS
{
	template<typename T>
	using EqualityFunction = bool(*)(const T& a, const T& b);

	template<typename T>
	bool functionEqual(const T& a, const T& b)
	{
		return a == b;
	}

	template<typename T>
	using CompareFunction = int(*)(const T& a, const T& b);
	
	template<typename T>
	int functionCompare(const T& a, const T& b)
	{
		return a > b ? -1 : b > a ? 1 : 0;
	}

	template<typename T>
	using HashFunction = int(*)(const T& data);


	typedef unsigned char byte;

	class Structure
	{
	public:
		Structure();
		virtual ~Structure();

		virtual Structure& operator=(const Structure& dalsi) = 0;

		virtual Structure* clone() const = 0;
	};

}

