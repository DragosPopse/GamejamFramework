#pragma once
#include <vector>

namespace jam::cecsar
{
	class ECSystemManager;
	class IECSubscribeable;

	class IECSystem
	{
	public:
		IECSystem(ECSystemManager& manager);
		virtual ~IECSystem();

		virtual void Add(int32_t index);
		virtual void Remove(int32_t index);

		void Subscribe(IECSubscribeable& subscribeable);
		void Unsubscribe(IECSubscribeable& subscribeable);

	private:
		std::vector<IECSubscribeable*> m_subscribers;
	};
}
