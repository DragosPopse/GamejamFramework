#pragma once

#include <Gamejam/Core/Core.hpp>


/*
	Utility class that converts a container into a reverse container to be used in a range-based for loop
	Basically, it swaps begin/end with rbegin/rend
*/

namespace jam
{
	namespace adapt
	{
		template <class Iterable>
		class Reverse
		{
		public:
			explicit Reverse(Iterable& iterable) :
				m_iterable(iterable)
			{
			}

			auto begin() { return m_iterable.rbegin(); }
			auto end() { return m_iterable.rend(); }

		private:
			Iterable& m_iterable;
		};
	}
}