#pragma once
#include "Headers.h"

class PathNode;

class Path
{
	vector <PathNode> m_path;

public:

	Path(vector <PathNode> path);
	Path();
	~Path() = default;

	void 
	AddNodeAt(int index, PathNode node),
	AddNode(PathNode node),
	EraseNodeAt(int index);

	PathNode* GetNodeAt(int index);
	vector <PathNode>* GetPath();

	void 
	SetPath(vector <PathNode> path),
	SetNodeAt(int index, PathNode node),
	SetIndexInRange(int& index),
	SetReverse();
};

