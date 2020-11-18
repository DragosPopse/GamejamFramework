#pragma once
#include <cstdint>

namespace jam::cecsar
{
	class ECSystemManager;

	class IEntityFactory
	{
		friend ECSystemManager;

	public:
		virtual ~IEntityFactory();
		virtual void OnConstruction(ECSystemManager& manager, int32_t index) = 0;

	protected:
		virtual void Initialize(ECSystemManager& manager);
	};
}