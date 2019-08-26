#pragma once
#include "Headers.h"
#include "Walker.h"

class WalkerDepthFS : public Walker {

public:

	void													CheckNeighbor(NodeRevision& node, short offsetY, short offsetX);
	ESearchState									Search();

	WalkerDepthFS();
	WalkerDepthFS(Grid* grid);
	~WalkerDepthFS() = default;
};