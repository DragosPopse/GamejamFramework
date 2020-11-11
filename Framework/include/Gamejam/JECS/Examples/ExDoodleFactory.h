#pragma once
#include <Gamejam/Core/Config.hpp>
#include <Gamejam/JECS/Core/EntityFactory.h>

namespace jam
{
	namespace jecs
	{
		namespace Examples
		{
			class ExRendererModule;

			class ExDoodleFactory final : public EntityFactory
			{
			public:
				ExDoodleFactory(SystemManager& manager, ExRendererModule& module);

			private:
				ExRendererModule* _renderModule = nullptr;
				const std::string texturePath = "Art/Doodle.png";

				void OnConstruction() override;
			};
		}
	}
}
