#pragma once
#include "../Core/ISystemBehaviour.h"
#include "ExRenderer.h"
#include "ExTransform.h"

namespace jam
{
	namespace jecs
	{
		namespace Examples
		{
			class ExRendererModule;

			class ExRendererBehaviour final : public ISystemBehaviour<ExRenderer>
			{
			public:
				using Renderers = Utilities::SparseSet<ExRenderer> &;
				using Transforms = Utilities::SparseSet<ExTransform> &;

				ExRendererBehaviour(SystemManager& manager, ExRendererModule& module);
				void Update(Renderers renderers, Transforms transforms) const;

			private:
				ExRendererModule& _renderModule;
			};
		}
	}
}
