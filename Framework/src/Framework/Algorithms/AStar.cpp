#include "Gamejam/Algorithms/AStar.h"
#include <unordered_set>

jam::algorithms::ITraversable::~ITraversable() = default;

jam::algorithms::AStar::Node::Node() = default;

jam::algorithms::AStar::Node::Node(const int32_t x, const int32_t y)
{
	this->x = x;
	this->y = y;
}

bool jam::algorithms::AStar::Node::operator==(const Node& other) const
{
	return x == other.x && y == other.y;
}

bool jam::algorithms::AStar::Comparer::operator()(const Node a, const Node b) const
{
	return a.cost - b.cost > 0;
}

size_t jam::algorithms::AStar::Comparer::operator()(const Node& other) const
{
	const size_t xHash = std::hash<int>()(other.x);
	const size_t yHash = std::hash<int>()(other.y) << 1;
	return xHash ^ yHash;
}

jam::algorithms::AStar::Node jam::algorithms::AStar::GetNext(
	ITraversable& grid, const Node from, const Node to)
{
	m_grid = &grid;
	m_from = from;
	m_to = to;

	m_heap.push(to);
	m_closed.insert(to);

	while(!m_heap.empty())
	{
		const Node node = m_heap.top();
		m_heap.pop();

		const int32_t x = node.x;
		const int32_t y = node.y;

		CheckNeighbour(x, y + 1);
		CheckNeighbour(x + 1, y);
		CheckNeighbour(x, y - 1);
		CheckNeighbour(x - 1, y);

		if(m_checkVertical)
		{
			CheckNeighbour(x + 1, y + 1);
			CheckNeighbour(x + 1, y - 1);
			CheckNeighbour(x - 1, y - 1);
			CheckNeighbour(x - 1, y + 1);
		}

		if (!m_found)
			continue;

		Clear();
		return m_foundNode;
	}

	Clear();
	return from;
}

void jam::algorithms::AStar::CheckNeighbour(const int32_t x, const int32_t y)
{
	Node node(x, y);

	if (m_closed.find(node) != m_closed.end())
		return;

	const int32_t id = m_grid->GetTileID(x, y);
	for (auto walkable : m_walkable)
		if(id == walkable)
		{
			const float distanceFrom = GetDistance(node, m_from);
			const float distanceTo = GetDistance(node, m_to);
			if (distanceFrom <= m_stoppingDistance + FLT_EPSILON)
			{
				m_foundNode = node;
				m_found = true;
			}

			node.cost = -(distanceFrom + distanceTo);
			m_heap.push(node);
			m_closed.insert(node);
			return;
		}
}

float jam::algorithms::AStar::GetDistance(const Node a, const Node b) const
{
	const float xPow = pow(abs(a.x - b.x), 2);
	const float yPow = pow(abs(a.y - b.y), 2);
	return sqrtf(xPow + yPow);
}

void jam::algorithms::AStar::Clear()
{
	m_heap = std::priority_queue<Node, std::vector<Node>, Comparer>();
	m_closed.clear();
	m_found = false;
}
