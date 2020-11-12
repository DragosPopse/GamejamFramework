#include "Gamejam/Algorithms/AStarExample.h"
#include <iostream>

int32_t jam::algorithms::examples::AStarExample::GetTileID(const int32_t x, const int32_t y)
{
	if (x < 0 || y < 0)
		return -1;
	if (x > 5 || y > 5)
		return -1;

	return m_grid[x][y];
}

void jam::algorithms::examples::AStarExample::Run()
{
	AStar aStar;
	aStar.m_walkable.push_back(0);
	const auto res = aStar.GetNext(*this, from, to);
	std::cout << res.x << " " << res.y << std::endl;
}
