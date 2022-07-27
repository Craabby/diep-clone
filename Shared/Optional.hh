#pragma once

#include <cassert>
#include <iostream>

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
			~Option() {}
		} option;

	public:
		Optional(const T &value)
		{
			Set(value);
		}

		Optional()
		{
			isNull = true;
		}

		bool Null()
		{
			return isNull;
		}

		bool Exists()
		{
			return isNull == false;
		}

		T *Get()
		{
			assert(Exists());
			return &option.value;
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
