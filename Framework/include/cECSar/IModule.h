#pragma once

namespace jam::cecsar
{
	class ECSystemManager;

	/*
	You can inherit this interface to make it automatically generated
	and accessable for everything within the ECSystemManager.

	Modules can be, for instance: TextureLibraryModule, RenderModule, SceneManagementModule, TimeModule.
	*/
	class IModule
	{
		friend ECSystemManager;

	public:
		virtual ~IModule();

	protected:
		virtual void Initialize(ECSystemManager& manager);
	};
}