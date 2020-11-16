#pragma once
#include <cstdint>

namespace cescar
{
	class ECSystemManager final
	{
	public:
		ECSystemManager(int32_t capacity = 1000);

	private:
		const int32_t capacity;
	};
}
