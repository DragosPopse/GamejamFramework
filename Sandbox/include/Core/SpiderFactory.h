#pragma once
#include "Gamejam/JECS/Core/EntityFactory.h"

namespace jam
{
	class SpiderFactory final : public jecs::EntityFactory
	{
	public:
		SpiderFactory(jecs::SystemManager& manager);

	protected:
		void OnConstruction() override;
	};
}
