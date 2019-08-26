#include "WalkerBestFS.h"

void
WalkerBestFS::CheckNeighbor(NodeRevision& node, short offsetY, short offsetX) {
	//If the indices are inside the range of the grid
	if ((node.column + offsetY) < m_map[0].size() && (node.row + offsetX) < m_map[0][0].size()) {
		//If the node isn't closed and it's not an obstacle
		if (!m_map[0][node.column + offsetY][node.row + offsetX].IsIn(m_closed) &&
			!*m_map[0][node.column + offsetY][node.row + offsetX].GetIsObstacle()) {
				//Add a new node with the calculated cost and current node as parent
				m_open.push_back(NodeRevision(m_map[0][node.column + offsetY][node.row + offsetX].GetPosition(),
				&m_map[0][node.column + offsetY][node.row + offsetX], new NodeRevision(node), &m_step.open, 
				EvaluateNode(node.column + offsetY, node.row + offsetX)));
		}
	}
}

unsigned int
WalkerBestFS::GetBestStep() {
	//Start with the fist score
	unsigned int best = 0, bestScore = m_open[0].cost;
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
WalkerBestFS::EvaluateNode(unsigned short Y, unsigned short X) {
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
WalkerBestFS::Search() {
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
				return StillSearching;
			}
			current.visualState = &m_step.closed;
			m_closed.push_back(current);

			//----------------------------------------------------------------------------------------
			//Check if we reached the goal
			//----------------------------------------------------------------------------------------
			if (current.column == m_destination->GetColumn() && current.row == m_destination->GetRow()) {
				//Build path by backtrack
				while (current.parent != nullptr) {
					current.visualState = &m_step.path;
					m_path.push_back(current);
					current = *current.parent;
				}
				return ESearchState::GoalReached;
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
		return NoPath;
	}
	return NoPath;
}

unsigned int
WalkerBestFS::Weight(unsigned short Y, unsigned short X) {
	return *m_map[0][Y][X].GetWeight();
}

unsigned int
WalkerBestFS::ManhattanDistance(unsigned short Y, unsigned short X) {
	return abs(m_destination->GetColumn() - m_map[0][Y][X].GetColumn()) + abs(m_destination->GetRow() - m_map[0][Y][X].GetRow());
}

unsigned int
WalkerBestFS::EuclideanDistance(unsigned short Y, unsigned short X) {
	return Vector2(*m_map[0][Y][X].GetPosition() - *m_destination->GetPosition()).Magnitude();
}

unsigned int
WalkerBestFS::QuadraticDistance(unsigned short Y, unsigned short X) {
	return Weight(Y, X) + Vector2(*m_map[0][Y][X].GetPosition() - *m_destination->GetPosition()).SqrtMagnitude();
}

WalkerBestFS::WalkerBestFS() : Walker() {}

WalkerBestFS::WalkerBestFS(Grid* grid) : Walker(grid) {}

/*void 
WalkerBestFS::CheckNeighbor(NodeRevision& node, short offsetY, short offsetX) {
	if ((node.column + offsetY) < m_map[0].size() && (node.row + offsetX) < m_map[0][0].size()) {
		if (!m_map[0][node.column + offsetY][node.row + offsetX].IsIn(m_closed) && !*m_map[0][node.column + offsetY][node.row + offsetX].GetIsObstacle()) {
			m_open.push_back(NodeRevision(m_map[0][node.column + offsetY][node.row + offsetX].GetPosition(),
			&m_map[0][node.column + offsetY][node.row + offsetX], new NodeRevision(node), &m_step.open));
		}
	}
}

unsigned int
WalkerBestFS::EvaluateNeighbors() {
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

ESearchState WalkerBestFS::Search() {
	if (m_destination && m_origin && m_map) {
		if (m_open.size()) {
			//----------------------------------------------------------------------------------------
			//Get best open node
			//----------------------------------------------------------------------------------------
			int best = EvaluateNeighbors();
			NodeRevision current = m_open[best];
			m_open.erase(m_open.begin() + best);

			//if it's already in closed nodes, return
			if (current.reference->IsIn(m_closed)) {
				return StillSearching;
			}
			//----------------------------------------------------------------------------------------
			//Set current node as closed
			//----------------------------------------------------------------------------------------
			current.visualState = &m_step.closed;
			m_closed.push_back(current);

			//----------------------------------------------------------------------------------------
			//Check if we reached the goal
			//----------------------------------------------------------------------------------------
			if (current.column == m_destination->GetColumn() && current.row == m_destination->GetRow()) {

				//Build path by backtrack
				while (current.parent != nullptr) {
					current.visualState = &m_step.path;
					m_path.push_back(current);
					current = *current.parent;
				}
				return ESearchState::GoalReached;
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
		return NoPath;
	}
	return NoPath;
}

unsigned int 
WalkerBestFS::LightestNode() {
	unsigned int best = 0;
	for (size_t i = 1; i < m_open.size(); i++) {
		if (*m_open[best].reference->GetWeight() > * m_open[i].reference->GetWeight()) {
			best = i;
		}
	}
	return best;
}

unsigned int
WalkerBestFS::ManhattanDistance() {
	unsigned int best = 0;
	int bestDistance = abs(m_destination->GetColumn() - m_open[best].reference->GetColumn()) +
	abs(m_destination->GetRow() - m_open[best].reference->GetRow());
	unsigned int currentCost;
	int currentDistance;
	for (size_t i = 1; i < m_open.size(); i++) {
		currentDistance = abs(m_destination->GetColumn() - m_open[i].reference->GetColumn()) +
			abs(m_destination->GetRow() - m_open[i].reference->GetRow());
		if (bestDistance > currentDistance) {
			bestDistance = currentDistance;
			best = i;
		}
	}
	return best;
}

unsigned int
WalkerBestFS::EuclideanDistance() {
	unsigned int best = 0;
	Vector2 BestNode = *m_open[best].reference->GetPosition() - *m_destination->GetPosition();
	Vector2 CurrentNode;
	for (size_t i = 1; i < m_open.size(); i++) {
		CurrentNode = *m_open[i].reference->GetPosition() - *m_destination->GetPosition();
		if (BestNode.Magnitude() > CurrentNode.Magnitude()) {
			BestNode = CurrentNode;
			best = i;
		}
	}
	return best;
}

unsigned int
WalkerBestFS::QuadraticDistance() {
	unsigned int best = 0;
	Vector2 BestNode = *m_open[best].reference->GetPosition() - *m_destination->GetPosition();
	Vector2 CurrentNode;
	for (size_t i = 1; i < m_open.size(); i++) {
		CurrentNode = *m_open[i].reference->GetPosition() - *m_destination->GetPosition();
		if (BestNode.SqrtMagnitude() > CurrentNode.SqrtMagnitude()) {
			BestNode = CurrentNode;
			best = i;
		}
	}
	return best;
}

WalkerBestFS::WalkerBestFS() : Walker() {}

WalkerBestFS::WalkerBestFS(Grid* grid) : Walker(grid) {}*/