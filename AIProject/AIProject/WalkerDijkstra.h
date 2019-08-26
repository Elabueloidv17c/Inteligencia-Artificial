#pragma once
#include "Walker.h"
class WalkerDijkstra : public Walker {

public:

	void													CheckNeighbor(NodeRevision& node, short offsetY, short offsetX);
	unsigned int  								EvaluateNode(unsigned short Y, unsigned short X);
	unsigned int									GetBestStep();
	ESearchState									Search();

	unsigned int									Weight(unsigned short Y, unsigned short X);
	unsigned int									ManhattanDistance(unsigned short Y, unsigned short X);
	unsigned int									EuclideanDistance(unsigned short Y, unsigned short X);
	unsigned int									QuadraticDistance(unsigned short Y, unsigned short X);

	/*void													CheckNeighbor(NodeRevision& node, short offsetX, short offSetY);
	unsigned int									EvaluateNeighbors();
	ESearchState									Search();

	unsigned int									LightestNode();
	unsigned int									ManhattanDistance();
	unsigned int									EuclideanDistance();
	unsigned int									QuadraticDistance();*/

	WalkerDijkstra();
	WalkerDijkstra(Grid* grid);
	~WalkerDijkstra() = default;
};

