#pragma once

namespace jam::cecsar
{
	class ECSystemManager;

	class ComponentSystem
	{
	public:
		virtual ~ComponentSystem();
		virtual void Update(ECSystemManager& systemManager) = 0;
	};
}
