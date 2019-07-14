#include "NodePlacer.h"

bool NodePlacer::Initialize(std::string name) {
	m_writer = std::ofstream(name);
	if (m_writer.is_open()) {
		m_isInitialized = true;
		return true;
	}
	m_isInitialized = false;
	return false;
}

void NodePlacer::AddNode(Vector2i position) {
	m_line = "";
	m_writer << position.x << ", " << position.y << "\n";
}

NodePlacer::NodePlacer() {
	m_isInitialized = false;
}

NodePlacer::~NodePlacer() {
	if(m_writer.is_open()) {
		m_writer.close();
	}
}
