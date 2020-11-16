#pragma once
#include "IECSubscribeable.h"
#include <vector>

namespace jam::cecsar
{
	class IECSystem
	{
	public:
		virtual ~IECSystem();

		virtual void Add(int32_t index);
		virtual void Remove(int32_t index);

		void Subscribe(IECSubscribeable* subscribeable);
		void Unsubscribe(IECSubscribeable* subscribeable);

	private:
		std::vector<IECSubscribeable*> m_subscribers;
	};
}
