#pragma once
#include <cstdint>

namespace jam::cecsar
{
	class IECSubscribeable
	{
	public:
		virtual ~IECSubscribeable();

		virtual void OnAdded(int32_t index) = 0;
		virtual void OnRemoved(int32_t index) = 0;
	};
}
