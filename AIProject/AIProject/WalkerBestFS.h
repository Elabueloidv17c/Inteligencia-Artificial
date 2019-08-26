#pragma once
#include "Walker.h"
class WalkerBestFS : public Walker {

public:


	void													CheckNeighbor(NodeRevision& node, short offsetY, short offsetX);
	unsigned int									GetBestStep();
	unsigned int  								EvaluateNode(unsigned short Y, unsigned short X);
	ESearchState									Search();

	unsigned int									Weight(unsigned short Y, unsigned short X);
	unsigned int									ManhattanDistance(unsigned short Y, unsigned short X);
	unsigned int									EuclideanDistance(unsigned short Y, unsigned short X);
	unsigned int									QuadraticDistance(unsigned short Y, unsigned short X);

	/*void													CheckNeighbor(NodeRevision& node, short offsetY, short offsetX);
	unsigned int									EvaluateNeighbors();
	ESearchState									Search();

	unsigned int									LightestNode();
	unsigned int									ManhattanDistance();
	unsigned int									EuclideanDistance();
	unsigned int									QuadraticDistance();*/

	WalkerBestFS();
	WalkerBestFS(Grid* grid);
	~WalkerBestFS() = default;
};

