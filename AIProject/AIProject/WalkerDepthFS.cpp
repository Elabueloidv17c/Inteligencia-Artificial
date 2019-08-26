#include "WalkerDepthFS.h"

void 
WalkerDepthFS::CheckNeighbor(NodeRevision& node, short offsetY, short offsetX) {
	auto& mapRef = (*m_map);

	if ((node.column + offsetY) < mapRef.size() && (node.row + offsetX) < mapRef[0].size()) {
		if (!mapRef[node.column + offsetY][node.row + offsetX].IsIn(m_closed) && !mapRef[node.column + offsetY][node.row + offsetX].GetIsObstacle()) {
			m_open.emplace_back(mapRef[node.column + offsetY][node.row + offsetX].GetPosition(),
				&mapRef[node.column + offsetY][node.row + offsetX], new NodeRevision(node), &m_step.open);
		}
	}
}

ESearchState
WalkerDepthFS::Search() {
	if (m_destination && m_origin && m_map) {
		if (m_open.size()) {
			//----------------------------------------------------------------------------------------
			//Get last inserted open node
			//----------------------------------------------------------------------------------------
			NodeRevision current = m_open[m_open.size() - 1];
			m_open.pop_back();

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

WalkerDepthFS::WalkerDepthFS() : Walker() {}

WalkerDepthFS::WalkerDepthFS(Grid* grid) : Walker(grid) {}

