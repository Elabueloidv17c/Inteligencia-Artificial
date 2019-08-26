#include "WalkerAStar.h"

void 
WalkerAStar::CheckNeighbor(NodeRevision& node, short offsetY, short offsetX) {
	//If the indices are inside the range of the grid
	if ((node.column + offsetY) < m_map[0].size() && (node.row + offsetX) < m_map[0][0].size()) {
		//If the node isn't closed and it's not an obstacle
		if (!m_map[0][node.column + offsetY][node.row + offsetX].IsIn(m_closed) &&
			!*m_map[0][node.column + offsetY][node.row + offsetX].GetIsObstacle()) {
			//Get the cost for the new step
			int index,
			costW = Weight(node.column + offsetY, node.row + offsetX),
			costD = EvaluateNode(node.column + offsetY, node.row + offsetX);
			//Add a new node with the calculated cost and current node as parent
			m_open.push_back(NodeRevision(m_map[0][node.column + offsetY][node.row + offsetX].GetPosition(),
			&m_map[0][node.column + offsetY][node.row + offsetX], new NodeRevision(node), &m_step.open, costD, costW));
		}
	}
}

unsigned int 
WalkerAStar::GetBestStep() {
	//Start with the fist score
	unsigned int best = 0, bestScore = m_open[0].costD;
	//Check all open nodes and compare their scores
	for (size_t i = 1; i < m_open.size(); i++) {
		//If a better score is found
		if (bestScore > m_open[i].costD) {
			//Update the best score and the index where that was found
			bestScore = m_open[i].costD;
			best = i;
		}
	}
	return best;
}

unsigned int  
WalkerAStar::EvaluateNode(unsigned short Y, unsigned short X) {
	//Check the current heuristic to apply and calculate the score of the node
	if (m_heuristic == EHeuristic::Distance || m_heuristic == EHeuristic::Cheapest) {
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
WalkerAStar::Search() {
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
				//Check if the old cost is bigger 
				if (m_closed[best].cost > current.cost) {
					//Replace the cost and parent of the found node
					m_closed[best].parent = current.parent;
					m_closed[best].cost = current.cost;
					m_closed[best].costD = current.costD;
					m_closed[best].costW = current.costW;
				}
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
WalkerAStar::Weight(unsigned short Y, unsigned short X) {
	return *m_map[0][Y][X].GetWeight();
}

unsigned int 
WalkerAStar::ManhattanDistance(unsigned short Y, unsigned short X) {
	return abs(m_destination->GetColumn() - m_map[0][Y][X].GetColumn()) + abs(m_destination->GetRow() - m_map[0][Y][X].GetRow()) + Weight(Y, X);
}

unsigned int 
WalkerAStar::EuclideanDistance(unsigned short Y, unsigned short X) {
	return Weight(Y, X) + Vector2(*m_map[0][Y][X].GetPosition() - *m_destination->GetPosition()).Magnitude();
}

unsigned int
WalkerAStar::QuadraticDistance(unsigned short Y, unsigned short X) {
	return Weight(Y, X) + Vector2(*m_map[0][Y][X].GetPosition() - *m_destination->GetPosition()).SqrtMagnitude();
}

WalkerAStar::WalkerAStar() : Walker() {}

WalkerAStar::WalkerAStar(Grid* grid) : Walker(grid) {}