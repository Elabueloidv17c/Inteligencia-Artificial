#pragma once
#include "Headers.h"

class RenderWindow;
class GridNode;

class Grid {
	
	bool													m_isDirty;
	RectNode											m_nodeShape;

	unsigned int									m_width;
	unsigned int									m_height;
	Bounds												m_bounds;

	Vector2f											m_nodeSize;
	vector <vector <GridNode>>		m_nodes;

public:

	vector <vector <GridNode>>*		GetMap();
	GridNode*											GetNodeAt(unsigned int column, unsigned int row);
	RectNode*											GetRectNode();
	unsigned int									GetNumNodes();
	const Bounds*									GetBounds();

	void													Update(Vector2f& mousePosition, EButton& nodeType);

	void													Render(RenderWindow& window);

	void													Initialize(
																						unsigned int width, 
																						unsigned int height, 
																						Vector2f nodeSize
																					);

	Grid(
				unsigned int width,
				unsigned int height,
				Vector2f nodeSize
	);

	Grid();
	~Grid();
};

