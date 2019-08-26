#pragma once
#include "Walker.h"
class WalkerAStar : public Walker {
public:

	void													CheckNeighbor(NodeRevision& node, short offsetY, short offsetX);
	unsigned int  								EvaluateNode(unsigned short Y, unsigned short X);
	unsigned int									GetBestStep();
	ESearchState									Search();

	unsigned int									Weight(unsigned short Y, unsigned short X);
	unsigned int									ManhattanDistance(unsigned short Y, unsigned short X);
	unsigned int									EuclideanDistance(unsigned short Y, unsigned short X);
	unsigned int									QuadraticDistance(unsigned short Y, unsigned short X);

	WalkerAStar();
	WalkerAStar(Grid* grid);
	~WalkerAStar() = default;
};