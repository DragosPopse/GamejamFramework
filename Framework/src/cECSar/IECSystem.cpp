#include "cECSar/IECSystem.h"
#include "cECSar/IECSubscribeable.h"

jam::cecsar::IECSystem::IECSystem(ECSystemManager& manager)
{
}

jam::cecsar::IECSystem::~IECSystem() = default;

void jam::cecsar::IECSystem::Add(const int32_t index)
{
	for (auto subscriber : m_subscribers)
		subscriber->OnAdded(index);
}

void jam::cecsar::IECSystem::Remove(const int32_t index)
{
	for (auto subscriber : m_subscribers)
		subscriber->OnRemoved(index);
}

void jam::cecsar::IECSystem::Subscribe(IECSubscribeable& subscribeable)
{
	m_subscribers.push_back(&subscribeable);
}

void jam::cecsar::IECSystem::Unsubscribe(IECSubscribeable& subscribeable)
{
	auto ptr = &subscribeable;

	for (auto i = m_subscribers.begin(); i != m_subscribers.end(); ++i)
		if (*i == ptr)
		{
			m_subscribers.erase(i);
			return;
		}
}