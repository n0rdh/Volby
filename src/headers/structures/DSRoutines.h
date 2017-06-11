#pragma once

#include <string>

using namespace std;

namespace DS
{
	class DSRoutines
	{
	public:
		static bool rangeCheck(const int index, const size_t size, const bool throwException = false, const string* message = nullptr);
		
		template<typename T>
		static void swap(T& a, T& b);
	private:
		DSRoutines();

	};

	template<typename T>
	void DSRoutines::swap(T& a, T& b)
	{
		T pom = a;
		a = b;
		b = pom;
	}
}
