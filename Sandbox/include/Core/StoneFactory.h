#pragma once
#include "Gamejam/JECS/Core/EntityFactory.h"

namespace jam
{
	class StoneFactory final : public jecs::EntityFactory
	{
	public:
		StoneFactory(jecs::SystemManager& manager);

	protected:
		void OnConstruction() override;
	};
}