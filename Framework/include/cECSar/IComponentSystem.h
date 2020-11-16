#pragma once

namespace jam::cecsar
{
	class ECSystemManager;

	class IComponentSystem
	{
	public:
		IComponentSystem(ECSystemManager& manager);

		virtual ~IComponentSystem();
		virtual void Update(ECSystemManager& systemManager) = 0;
	};
}
