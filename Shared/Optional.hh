#pragma once

#include <cassert>

namespace shared
{
	template <typename T>
	class Optional
	{
		union Option
		{
			T value;
			Option() {}
		} option;

	public:
		bool isNull = true;

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

		void Delete()
		{
			isNull = true;
		}

		void operator=(const T &value)
		{
			Set(value);
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