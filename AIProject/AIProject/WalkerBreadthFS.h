#pragma once
#include "Headers.h"
#include "Walker.h"

class WalkerBreadthFS : public Walker {

public:

	void													CheckNeighbor(NodeRevision& node, short offsetY, short offsetX);
	ESearchState									Search();

	WalkerBreadthFS();
	WalkerBreadthFS(Grid* grid);
	~WalkerBreadthFS() = default;
};