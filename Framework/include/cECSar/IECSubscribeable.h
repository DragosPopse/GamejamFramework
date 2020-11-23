#pragma once
#include <cstdint>

namespace jam::cecsar
{
	/*
	You can inherit from this interface to get notified on certain component related events.
	*/
	class IECSubscribeable
	{
	public:
		virtual ~IECSubscribeable();

		virtual void OnAdded(int32_t index) = 0;
		virtual void OnRemoved(int32_t index) = 0;
	};
}
