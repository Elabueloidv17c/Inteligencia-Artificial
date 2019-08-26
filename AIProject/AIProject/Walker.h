#pragma once
#include"Headers.h"
#include "GridNode.h"
#include "Grid.h"

struct NodeRevision;

class Walker {

protected:

	EHeuristic											m_heuristic;
	ESearchState										m_state;
	Bounds													m_bounds;

	vector <vector <GridNode>>*			m_map;
	vector <NodeRevision>						m_open;
	vector <NodeRevision>						m_closed;
	vector <NodeRevision>						m_path;

	GridNode* m_origin;
	GridNode* m_destination;
	CircleNode											m_step;

public:

	void														Start();
	void														Stop();

	virtual ESearchState						Search();
	virtual unsigned int						EvaluateNeighbors();
	virtual void										CheckNeighbor(NodeRevision& node, short offsetY, short offsetX);

	virtual unsigned int						LightestNode();
	virtual unsigned int						ManhattanDistance();
	virtual unsigned int						EuclideanDistance();
	virtual unsigned int						QuadraticDistance();

	void														SetDestination(Vector2f& position);
	void														SetOrigin(Vector2f& position);
	void														SetHeuristic(EButton& type);

	void														Update(Vector2f& mousePosition, EButton& activeButton);
	void														Render(RenderWindow& window);
	void														Initialize(Grid* grid);
	

	CircleNode*											GetCircleNode();

	Walker() = default;
	Walker(Grid* grid);
	virtual ~Walker();
};

//Distancia euler
//Distancia cuadrada
//Distancia manhattan