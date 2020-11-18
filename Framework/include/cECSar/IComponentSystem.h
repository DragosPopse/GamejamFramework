#pragma once

namespace jam::cecsar
{
	class ECSystemManager;

	class IComponentSystem
	{
		friend ECSystemManager;

	public:
		virtual ~IComponentSystem();
		virtual void Update(ECSystemManager& systemManager) = 0;

	protected:
		virtual void Initialize(ECSystemManager& manager);
	};
}
