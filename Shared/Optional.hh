#pragma once

#include <cassert>
#include <iostream>
#include <string>

namespace shared
{
	template <typename T>
	class Optional
	{
		bool isNull = true;

		union Option
		{
			T value;
			Option() {}
		} option;

	public:
		bool Null()
		{
			return isNull;
		}

		T *Get()
		{
			assert(isNull == false);
			return &option.value;
		}

		void Set(const T &value)
		{
			isNull = false;
			option.value = value;
		}

		T &Assert(const std::string &assertion)
		{
			if (isNull)
			{
				std::cerr << assertion << std::endl;
				assert(false);
			}

			return **this;
		}

		void Delete()
		{
			isNull = true;
		}

		void operator=(const T &value)
		{
			Set(value);
		}

		T &operator()(const std::string &assertion)
		{
			return Assert(assertion);
		}

		T *operator->()
		{
			return Get();
		}

		T &operator*()
		{
			return *Get();
		}
	};
}
