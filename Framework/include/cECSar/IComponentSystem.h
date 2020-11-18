#pragma once

namespace jam::cecsar
{
	class ECSystemManager;

	/*
	You can inherit this interface to make it automatically generated
	and accessable for everything within the ECSystemManager.

	A componentsystem is used to give behaviour to components, 
	like moving a transformComponent or rendering the renderComponent.
	*/
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
