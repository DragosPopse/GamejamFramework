#pragma once
#include <Gamejam/Core/Config.hpp>
#include <vector>
#include <queue>
#include <unordered_set>

namespace jam::algorithms
{
	// Inherit this interface to be able to use AStar.
	class ITraversable
	{
	public:
		virtual ~ITraversable();
		virtual int32_t GetTileID(int32_t x, int32_t y) = 0;
	};

	// Create an instance of AStar and tweak it's variables to your liking.
	class AStar final
	{
	public:
		class Node final
		{
		public:
			int32_t x = 0, y = 0;
			float cost = 0;

			Node();
			Node(int32_t x, int32_t y);

			bool operator==(const Node& other) const;
		};

		std::vector<int32_t> m_walkable;
		bool m_checkVertical = false;
		float m_stoppingDistance = 1;

		Node GetNext(ITraversable& grid, Node from, Node to);

	private:
		class Comparer final
		{
		public:
			bool operator()(Node a, Node b) const;
			size_t operator()(const Node& other) const;
		};

		std::priority_queue<Node, std::vector<Node>, Comparer> m_heap;
		std::unordered_set<Node, Comparer> m_closed;
		ITraversable* m_grid = nullptr;
		Node m_from{}, m_to{};

		bool m_found = false;
		Node m_foundNode{};

		void CheckNeighbour(int32_t x, int32_t y);
		float GetDistance(Node a, Node b) const;
		void Clear();
	};
}
