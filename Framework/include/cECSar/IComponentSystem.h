#pragma once

namespace jam::cecsar
{
	class ECSystemManager;

	class IComponentSystem
	{
	public:
		virtual ~IComponentSystem();
		virtual void Update(ECSystemManager& systemManager) = 0;
	};
}
