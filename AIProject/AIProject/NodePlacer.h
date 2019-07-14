#pragma once
#include "Headers.h"

class NodePlacer
{
	Vector2i			m_position;
	std::string		m_line;

	std::ofstream m_writer;

	bool					m_isInitialized;

public:

	bool
	Initialize(std::string name);
	
	void
	AddNode(Vector2i position);

	NodePlacer();
	~NodePlacer();
};

