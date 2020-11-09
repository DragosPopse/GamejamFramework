﻿#pragma once
#include "EntityFactory.h"

namespace DJ
{
	namespace JECS
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
