#include "Path.h"
#include "PathNode.h"

Path::Path() {
}

Path::Path(vector<PathNode> path) {
	m_path = path;
}

void Path::AddNodeAt(int index, PathNode node) {
	SetIndexInRange(index);

	vector <PathNode>* copy = new vector<PathNode>(m_path);

	m_path.erase(m_path.begin() + index, m_path.end());
	m_path.push_back(node);

	while (index < copy->size()) {
		m_path.push_back(copy[0][index++]);
	}

	delete copy;
}

void Path::AddNode(PathNode node) {
	m_path.push_back(node);
}

void Path::EraseNodeAt(int index) {
	SetIndexInRange(index);

	m_path.erase(m_path.begin() + index);
}

PathNode* Path::GetNodeAt(int index) {
	SetIndexInRange(index);
	return &m_path[index];
}

vector<PathNode>* Path::GetPath() {
	return &m_path;
}

void Path::SetReverse() {

	vector <PathNode>* copy = new vector<PathNode>(m_path);

	for (size_t i = 0; i < m_path.size(); i++) {
		m_path[i] = copy[0][m_path.size() - i - 1];
	}

	delete copy;
}

void Path::SetIndexInRange(int& index) {
	if (index < 0) {
		index = 0;
	}
	if (index >= m_path.size()) {
		index = m_path.size() - 1;
	}
}

void Path::SetPath(vector<PathNode> path) {
	m_path = path;
}

void Path::SetNodeAt(int index, PathNode node) {
	SetIndexInRange(index);
	m_path[index] = node;
}
