#include "WalkerBreadthFS.h"

void 
WalkerBreadthFS::CheckNeighbor(NodeRevision& node, short offsetY, short offsetX) {
	if ((node.column + offsetY) < m_map[0].size() && (node.row + offsetX) < m_map[0][0].size()) {
		if (!m_map[0][node.column + offsetY][node.row + offsetX].IsIn(m_closed) && !*m_map[0][node.column + offsetY][node.row + offsetX].GetIsObstacle()) {
			m_open.push_back(NodeRevision(m_map[0][node.column + offsetY][node.row + offsetX].GetPosition(),
				&m_map[0][node.column + offsetY][node.row + offsetX], new NodeRevision(node), &m_step.open));
		}
	}
}

ESearchState
WalkerBreadthFS::Search() {
	if (m_destination && m_origin && m_map) {
		if (m_open.size()) {
			//----------------------------------------------------------------------------------------
			//Get last inserted open node
			//----------------------------------------------------------------------------------------
			NodeRevision current = m_open[0];
			m_open.erase(m_open.begin());

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

WalkerBreadthFS::WalkerBreadthFS() : Walker() {}

WalkerBreadthFS::WalkerBreadthFS(Grid* grid) : Walker(grid) {}

