#pragma once
#include "cECSar/IComponentSystem.h"
#include <cstdint>

namespace jam::demo
{
	class TransformSystem final : public cecsar::IComponentSystem
	{
	public:
		~TransformSystem();

		void Initialize(cecsar::ECSystemManager& manager) override;
		void Update(cecsar::ECSystemManager& systemManager) override;

	private:
		class Sortable final
		{
		public:
			int32_t index;
			int32_t depth;

			bool operator<(const Sortable& other) const;
		};

		Sortable* m_sortables = nullptr;
	};
}
