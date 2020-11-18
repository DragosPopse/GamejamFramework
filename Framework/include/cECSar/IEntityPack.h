#pragma once
#include <cstdint>

namespace jam::cecsar
{
	class ECSystemManager;

	/*
	You can inherit this interface to make it automatically generated
	and accessable for everything within the ECSystemManager.

	You can add and remove a pack from an entity.
	The standard usercase would be to add/remove a couple of components, but you're free
	to do whatever else you want with it, like call events or even modify other entities.
	*/
	class IEntityPack
	{
		friend ECSystemManager;

	public:
		virtual ~IEntityPack();

		virtual void AddToEntity(ECSystemManager& manager, int32_t index) = 0;
		virtual void RemoveFromEntity(ECSystemManager& manager, int32_t index) = 0;

	protected:
		virtual void Initialize(ECSystemManager& manager);
	};
}
