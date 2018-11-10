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
		static std::vector<R> flatten(ForwardIter begin, ForwardIter end, std::function<std::vector<R>(T)> func)
		{
			std::vector<R> result;
			for (; begin != end; begin++)
			{
				std::vector<R> flattened = func(*begin);
				for (auto b = flattened.begin(); b != flattened.end(); b++)
				{
					result.push_back(*b);
				}
			}

			return result;
		}

		template <typename T>
		static T* toArray(std::vector<T> vector)
		{
			return &vector[0];
		}

		template <typename T>
		static std::vector<T> toVector(T * arr, int len)
		{
			return std::vector<T>(arr, len);
		}
	};
}
