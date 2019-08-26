#include "WalkerDijkstra.h"

void
WalkerDijkstra::CheckNeighbor(NodeRevision& node, short offsetY, short offsetX) {
	//If the indices are inside the range of the grid
	if ((node.column + offsetY) < m_map[0].size() && (node.row + offsetX) < m_map[0][0].size()) {
		//If the node isn't closed and it's not an obstacle
		if (!m_map[0][node.column + offsetY][node.row + offsetX].IsIn(m_closed) &&
			!*m_map[0][node.column + offsetY][node.row + offsetX].GetIsObstacle()) {
			//Get the cost for the new step
			int index, cost = node.cost + EvaluateNode(node.column + offsetY, node.row + offsetX);
			//Add a new node with the calculated cost and current node as parent
			m_open.push_back(NodeRevision(m_map[0][node.column + offsetY][node.row + offsetX].GetPosition(),
			&m_map[0][node.column + offsetY][node.row + offsetX], new NodeRevision(node), &m_step.open, cost));
		}
	}
}

unsigned int
WalkerDijkstra::GetBestStep() {
	//Start with the fist score
	unsigned int best = 0, bestScore = m_open[0].cost;
	return best;
	//Check all open nodes and compare their scores
	for (size_t i = 1; i < m_open.size(); i++) {
		//If a better score is found
		if (bestScore > m_open[i].cost) {
			//Update the best score and the index where that was found
			bestScore = m_open[i].cost;
			best = i;
		}
	}
	return best;
}

unsigned int
WalkerDijkstra::EvaluateNode(unsigned short Y, unsigned short X) {
	//Check the current heuristic to apply and calculate the score of the node
	if (m_heuristic == EHeuristic::Cheapest) {
		return Weight(Y, X);
	}
	if (m_heuristic == EHeuristic::Distance) {
		return EuclideanDistance(Y, X);
	}
	if (m_heuristic == EHeuristic::Manhatan) {
		return ManhattanDistance(Y, X);
	}
	if (m_heuristic == EHeuristic::SqrtDistance) {
		return QuadraticDistance(Y, X);
	}

}

ESearchState
WalkerDijkstra::Search() {
	if (m_destination && m_origin && m_map) {
		if (m_open.size()) {
			//----------------------------------------------------------------------------------------
			//Get best open node
			//----------------------------------------------------------------------------------------
			int best = GetBestStep();
			NodeRevision current = m_open[best];
			m_open.erase(m_open.begin() + best);

			//----------------------------------------------------------------------------------------
			//Set current node as closed
			//----------------------------------------------------------------------------------------
			if (current.reference->IsIn(m_closed, best)) {
				if (m_closed[best].cost > current.cost) {
					m_closed[best].parent = current.parent;
					m_closed[best].cost = current.cost;
				}
				return StillSearching;
			}
			current.visualState = &m_step.closed;
			m_closed.push_back(current);

			//----------------------------------------------------------------------------------------
			//Check if we reached the goal
			//----------------------------------------------------------------------------------------
			if (current.column == m_destination->GetColumn() && current.row == m_destination->GetRow()) {
				if (m_path.size() == 0) {
					m_path.push_back(NodeRevision(current));
				}
				else if (current.cost < m_path[0].cost) {
					m_path[0].cost = current.cost;
					m_path[0].parent = current.parent;
				}
			}

			//----------------------------------------------------------------------------------------
			//Get all connections
			//----------------------------------------------------------------------------------------
			CheckNeighbor(current, 0, 1);
			CheckNeighbor(current, -1, 1);
			CheckNeighbor(current, -1, 0);
			CheckNeighbor(current, -1, -1);
			CheckNeighbor(current, 0, -1);
			CheckNeighbor(current, 1, -1);
			CheckNeighbor(current, 1, 0);
			CheckNeighbor(current, 1, 1);
			return StillSearching;
		}
		if (m_path.size()) {
			//-------------------------------------------------------------------------------
			//Build current path
			//-------------------------------------------------------------------------------
			int index;
			if (m_destination->IsIn(m_closed, index)) {
				NodeRevision current = m_closed[index];
				m_path.clear();
				while (current.parent != nullptr) {
					current.visualState = &m_step.path;
					m_path.push_back(current);
					current = *current.parent;
				}
			}
			return ESearchState::StillSearching;
		}
		return NoPath;
	}
	return NoPath;
}

unsigned int
WalkerDijkstra::Weight(unsigned short Y, unsigned short X) {
	return *m_map[0][Y][X].GetWeight();
}

unsigned int
WalkerDijkstra::ManhattanDistance(unsigned short Y, unsigned short X) {
	return abs(m_destination->GetColumn() - m_map[0][Y][X].GetColumn()) + abs(m_destination->GetRow() - m_map[0][Y][X].GetRow()) + Weight(Y, X);
}

unsigned int
WalkerDijkstra::EuclideanDistance(unsigned short Y, unsigned short X) {
	return Weight(Y, X) + Vector2(*m_map[0][Y][X].GetPosition() - *m_destination->GetPosition()).Magnitude();
}

unsigned int
WalkerDijkstra::QuadraticDistance(unsigned short Y, unsigned short X) {
	return Weight(Y, X) + Vector2(*m_map[0][Y][X].GetPosition() - *m_destination->GetPosition()).SqrtMagnitude();
}

WalkerDijkstra::WalkerDijkstra() : Walker() {}

WalkerDijkstra::WalkerDijkstra(Grid* grid) : Walker(grid) {}

/*ESearchState 
WalkerDijkstra::Search() {
	if (m_destination && m_origin && m_map) {
		if (m_open.size()) {
			
			//----------------------------------------------------------------------------------------
			//Evaluate all neighbors
			//----------------------------------------------------------------------------------------
			int index = EvaluateNeighbors();

			//----------------------------------------------------------------------------------------
			//Get open node
			//----------------------------------------------------------------------------------------
			NodeRevision current = m_open[index];
			m_open.erase(m_open.begin());

			//----------------------------------------------------------------------------------------
			//Set current node as closed
			//----------------------------------------------------------------------------------------
			if (current.reference->IsIn(m_closed, index)) {
				if (m_closed[index].cost > current.cost) {
					m_closed[index].parent = current.parent;
					m_closed[index].cost = current.cost;
				}
				return StillSearching;
			}
			current.visualState = &m_step.closed;
			m_closed.push_back(current);

			//----------------------------------------------------------------------------------------
			//Check if we reached the goal and if that's the best path
			//----------------------------------------------------------------------------------------
			if (current.column == m_destination->GetColumn() && current.row == m_destination->GetRow()) {
				if (m_path.size() == 0) {
					m_path.push_back(NodeRevision(current));
				}
				else if (current.cost < m_path[0].cost) {
					m_path[0].cost = current.cost;
					m_path[0].parent = current.parent;
				}
			}

			//----------------------------------------------------------------------------------------
			//Get all connections
			//----------------------------------------------------------------------------------------

			//Right Down
			CheckNeighbor(current, 0, 1);
			CheckNeighbor(current, -1, 1);
			CheckNeighbor(current, -1, 0);
			CheckNeighbor(current, -1, -1);
			CheckNeighbor(current, 0, -1);
			CheckNeighbor(current, 1, -1);
			CheckNeighbor(current, 1, 0);
			CheckNeighbor(current, 1, 1);

			return StillSearching;
		}
		if (m_path.size()) {
			//-------------------------------------------------------------------------------
			//Build current path
			//-------------------------------------------------------------------------------
			int index;
			if (m_destination->IsIn(m_closed, index)) {
				NodeRevision current = m_closed[index];
				m_path.clear();
				while (current.parent != nullptr) {
					current.visualState = &m_step.path;
					m_path.push_back(current);
					current = *current.parent;
				}
			}
			return ESearchState::StillSearching;
		}
		return NoPath;
	}
	return NoPath;
}

unsigned int
WalkerDijkstra::EvaluateNeighbors() {
	if (m_heuristic == EHeuristic::Cheapest) {
		return LightestNode();
	}
	if (m_heuristic == EHeuristic::Manhatan) {
		return ManhattanDistance();
	}
	if (m_heuristic == EHeuristic::Distance) {
		return EuclideanDistance();
	}
	if (m_heuristic == EHeuristic::SqrtDistance) {
		return QuadraticDistance();
	}
}

void 
WalkerDijkstra::CheckNeighbor(NodeRevision& node, short offsetY, short offsetX) {
	int index;
	if ((node.column + offsetY) < m_map[0].size() && (node.row + offsetX) < m_map[0][0].size()
		&& !*m_map[0][node.column + offsetY][node.row + offsetX].GetIsObstacle()) {
		if (m_map[0][node.column + offsetY][node.row + offsetX].IsIn(m_closed, index)) {
			if (m_closed[index].cost > node.cost) {
				m_closed[index].parent = node.parent;
				m_closed[index].cost = node.cost;
			}
		}
		else {
			m_open.push_back(NodeRevision(m_map[0][node.column + offsetY][node.row + offsetX].GetPosition(),
			&m_map[0][node.column + offsetY][node.row + offsetX], new NodeRevision(node), &m_step.open, node.cost));
		}
	}
}

unsigned int 
WalkerDijkstra::LightestNode() {
	m_open[0].cost += *m_open[0].reference->GetWeight();
	return 0;
}

unsigned int 
WalkerDijkstra::ManhattanDistance() {
	m_open[0].cost += abs(m_destination->GetColumn() - m_open[0].reference->GetColumn()) +
	abs(m_destination->GetRow() - m_open[0].reference->GetRow());
	return 0;
}

unsigned int 
WalkerDijkstra::EuclideanDistance() {
	Vector2 BestNode = *m_open[0].reference->GetPosition() - *m_destination->GetPosition();
	m_open[0].cost += BestNode.Magnitude();
	return 0;
}

unsigned int 
WalkerDijkstra::QuadraticDistance() {
	Vector2 BestNode = *m_open[0].reference->GetPosition() - *m_destination->GetPosition();
	m_open[0].cost += BestNode.SqrtMagnitude();
	return 0;
}

WalkerDijkstra::WalkerDijkstra() : Walker() {}

WalkerDijkstra::WalkerDijkstra(Grid* grid) : Walker(grid) {}*/