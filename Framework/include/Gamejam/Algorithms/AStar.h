#pragma once
#include <Gamejam/Core/Config.hpp>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>

namespace jam::algorithms
{
	// Inherit this interface to be able to use AStar.
	class ITraversable
	{
	public:
		const int32_t TYPETYPE_NONE = -1;
		virtual int32_t GetTileID(float x, float y) = 0;
	};

	// Create an instance of AStar and tweak it's variables to your liking.
	class AStar final
	{
		class Node final
		{
		public:
			int32_t x, y;
			float cost;

			bool operator==(const Node& other) const;
		};

		class Comparer final
		{
		public:
			bool operator()(Node a, Node b);
			size_t operator()(const Node& other) const;
		};

	public:
		std::vector<int32_t> m_walkable;
		bool m_checkVertical = false;
		float m_stoppingDistance = 1;

		Node GetNext(ITraversable& grid, Node from, Node to);

	private:
		std::priority_queue<Node, std::vector<Node>, Comparer> m_heap;
		std::unordered_set<Node, Comparer> m_closed;
		ITraversable* m_grid = nullptr;
		Node m_from{}, m_to{};
		bool found = false;

		void CheckNeighbour(int32_t x, int32_t y);
		float GetDistance(Node a, Node b) const;
		void Clear();
	};
}
