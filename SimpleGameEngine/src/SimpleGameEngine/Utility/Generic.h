#pragma once
#include <functional>
#include <iterator>
#include <vector>

namespace SimpleGameEngine::Utility
{
	class Generic
	{
	public:
		template <typename ForwardIter, typename T, typename R>
		static std::vector<R> flatten(ForwardIter begin, ForwardIter end, std::function<void(const T &, std::vector<R> &)> func)
		{
			std::vector<R> result;
			for (; begin != end; begin++)
			{
				func(*begin, result);
			}

			return result;
		}

		template <typename T>
		static T* copyToArray(const std::vector<T> & vector)
		{
			T * arr = new T[vector.size()];
			std::copy(vector.begin(), vector.end(), arr);
			
			return arr;
		}

		template <typename T>
		static std::vector<T> wrapInVector(T * arr, int len)
		{
			std::vector<T> vec;
			vec.assign(arr, arr + len);

			return vec;
		}
	};
}
