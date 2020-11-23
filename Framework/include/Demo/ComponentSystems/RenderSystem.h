#pragma once
#include "cECSar/IComponentSystem.h"
#include <cstdint>

namespace jam::demo
{
	class RenderSystem final : public cecsar::IComponentSystem
	{
	public:
		~RenderSystem();

		void Initialize(cecsar::ECSystemManager& manager) override;
		void Update(cecsar::ECSystemManager& systemManager) override;

	private:
		class Sortable final
		{
		public:
			int32_t index;
			float z;

			bool operator<(const Sortable& other) const;
		};
	
		Sortable* m_sortables = nullptr;
	};
}
