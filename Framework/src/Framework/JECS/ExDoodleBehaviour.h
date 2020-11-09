#pragma once
#include "ISystemBehaviour.h"
#include "ExDoodleBrain.h"
#include "ExTransform.h"
#include "ExRenderer.h"

namespace jam
{
	namespace jecs
	{
		namespace Examples
		{
			class ExDoodleBehaviour : public ISystemBehaviour<ExDoodleBrain>
			{
			public:
				ExDoodleBehaviour(SystemManager& manager);

				using Doodles = Utilities::SparseSet<ExDoodleBrain> &;
				using Transforms = Utilities::SparseSet<ExTransform> &;
				using Renderers = Utilities::SparseSet<ExRenderer> &;

				void Update(Doodles doodles, Transforms transforms, Renderers renderers,
					float deltaTime, float time) const;
			};
		}
	}
}
