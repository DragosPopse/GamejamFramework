#pragma once
#include <Gamejam/Core/Config.hpp>
#include "AStar.h"

namespace jam::algorithms::examples
{
	class AStarExample final : public ITraversable
	{
	public:
		int32_t GetTileID(int32_t x, int32_t y) override;
		void Run();

	private:
		// Edit to test.
		AStar::Node from = AStar::Node(1, 4);
		AStar::Node to = AStar::Node(4, 1);

		const int32_t m_grid[5][5] =
		{
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		};
	};
}
