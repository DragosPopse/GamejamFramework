#pragma once

namespace jam::cecsar
{
	class ECSystemManager;

	class IModule
	{
		friend ECSystemManager;

	public:
		virtual ~IModule();

	protected:
		virtual void Initialize(ECSystemManager& manager);
	};
}