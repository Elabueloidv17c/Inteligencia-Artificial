#include "GridNode.h"
#include "Grid.h"


Grid::Grid() {

}

Grid::~Grid() {

}

void
Grid::Initialize(
									unsigned int width,
									unsigned int height,
									Vector2f nodeSize
								) {
	m_isDirty = false;
	m_bounds = Bounds(0, height * nodeSize.y, 0, width * nodeSize.x);
	m_nodeSize = nodeSize;
	m_height = height;
	m_width = width;

	m_nodeShape = RectNode(Color(0, 0, 127, 255), 1, Vector2f(10, 10));

	m_nodes.resize(height);

	for (int i = 0; i < m_nodes.size(); i++) {
		m_nodes[i].resize(width);
	}

	for (int i = 0; i < m_nodes.size(); i++) {
		for (int j = 0; j < m_nodes[i].size(); j++) {
			m_nodes[i][j].Initialize(&m_isDirty, &m_nodeShape, Vector2f(j * m_nodeSize.x, i * m_nodeSize.y), false, 1, i, j);
		}
	}
}

Grid::Grid(
						unsigned int width,
						unsigned int height,
						Vector2f nodeSize
					) {
	m_isDirty = false;
	m_bounds = Bounds(0, height * nodeSize.y, 0, width * nodeSize.x);
	m_nodeSize = nodeSize;
	m_height = height;
	m_width = width;

	m_nodeShape = RectNode(Color(0, 0, 127, 255), 1, Vector2f(10, 10));

	m_nodes.resize(height);

	for (int i = 0; i < m_nodes.size(); i++) {
		m_nodes[i].resize(width);
	}

	for (int i = 0; i < m_nodes.size(); i++) {
		for (int j = 0; j < m_nodes[i].size(); j++) {
			m_nodes[i][j].Initialize(&m_isDirty, &m_nodeShape, Vector2f(j * m_nodeSize.x, i * m_nodeSize.y), false, 1, i, j);
		}
	}
}

vector<vector<GridNode>>* 
Grid::GetMap() {
	return &m_nodes;
}

GridNode*
Grid::GetNodeAt(unsigned int column, unsigned int row) {
	if (column < 0 || column >= m_nodes.size() || row < 0 || row >= m_nodes[0].size()) {
			return nullptr;
	}
	return &m_nodes[column][row];
}

RectNode* 
Grid::GetRectNode() {
	return &m_nodeShape;
}

unsigned int 
Grid::GetNumNodes() {
	return m_nodes.size();
}

const Bounds* 
Grid::GetBounds() {
	return &m_bounds;
}

void 
Grid::Update(Vector2f& mousePosition, EButton& nodeType) {
	if (m_bounds.isColliding(mousePosition)) {
		for (int i = 0; i < m_nodes.size(); i++) {
			for (int j = 0; j < m_nodes[i].size(); j++) {
				m_nodes[i][j].Update(mousePosition, nodeType);
			}
		}
	}
}

void 
Grid::Render(RenderWindow& window) {
	for (int i = 0; i < m_nodes.size(); i++) {
		for (int j = 0; j < m_nodes[i].size(); j++) {
			m_nodes[i][j].Render(window);
		}
	}
}
