#include "Demo/ComponentSystems/TransformSystem.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include <algorithm>

jam::demo::TransformSystem::~TransformSystem()
{
	delete[] sortables;
}

void jam::demo::TransformSystem::Initialize(cecsar::ECSystemManager& manager)
{
	const int32_t capacity = manager.GetCapacity();
	sortables = new Sortable[capacity];
}

void jam::demo::TransformSystem::Update(cecsar::ECSystemManager& systemManager)
{
	auto& transforms = systemManager.GetSet<TransformComponent>();

	const int32_t count = transforms.GetCount();

	// Calculate depth.
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = transforms.dense[i];

		int32_t currentIndex = index;
		int32_t depth = 0;

		while(true)
		{
			auto& child = transforms.instances[currentIndex];
			if (child.parent == -1)
				break;

			depth++;
			currentIndex = child.parent;
		}

		Sortable& sortable = sortables[i];
		sortable.index = index;
		sortable.depth = depth;
	}

	// Sort based on depth. Parents first.
	std::sort(sortables, sortables + count);

	// Update postions based on parents.
	for (int32_t i = 0; i < count; ++i)
	{
		const auto sortable = sortables[i];
		auto& transform = transforms.instances[sortable.index];
		if (transform.parent == -1)
		{
			transform.xPosGlobal = transform.xPos;
			transform.yPosGlobal = transform.yPos;

			transform.degreesGlobal = transform.degrees;
			continue;
		}

		auto& parent = transforms.instances[transform.parent];

		transform.xPosGlobal = transform.xPos + parent.xPosGlobal;
		transform.yPosGlobal = transform.yPos + parent.yPosGlobal;

		transform.degreesGlobal = transform.degrees + parent.degreesGlobal;
	}
}

bool jam::demo::TransformSystem::Sortable::operator<(const Sortable& other) const
{
	return depth < other.depth;
}
