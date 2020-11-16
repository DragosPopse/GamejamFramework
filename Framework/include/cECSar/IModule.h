#pragma once

namespace jam::cecsar
{
	class ECSystemManager;

	class IModule
	{
	public:
		IModule(ECSystemManager& manager);
		virtual ~IModule();
	};
}