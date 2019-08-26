#pragma once
#define DEBUG


//External dependences
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>  
#include <chrono>
#include <stack>

//Bidimensional Vector implementation
#include "Vector2.h"

//Constants
#define	PI													3.141592f
#define HALF												0.5f
#define DOUBLE											2.0f

//Type definitions
typedef std::chrono::time_point<std::chrono::steady_clock>	TimePoint;

//This is used to short the type of some objects and functions
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::vector;
using std::string;
using std::cout;

using sf::RectangleShape;
using sf::RenderWindow;
using sf::CircleShape;
using sf::VideoMode;
using sf::FloatRect;
using sf::Vector2u;
using sf::Vector2i;
using sf::Vector2f;
using sf::Texture;
using sf::Sprite;
using sf::Vertex;
using sf::Color;
using sf::Event;
using sf::Font;
using sf::Text;
using sf::View;

//Structs
struct WindowData {
	string			
  name;

	int				
  width,
	heigh,
  style;
};

struct RectNode {
	RectangleShape	obstacle;
	RectangleShape	cost1;
	RectangleShape	cost2;
	RectangleShape	cost3;
	RectangleShape	cost4;
	RectangleShape	cost5;

	RectNode() {}

	RectNode(
						Color outlineColor, 
						float outlineThickness, 
						Vector2f size
	) {
		obstacle.setOutlineColor(outlineColor);
		obstacle.setOutlineThickness(outlineThickness);
		obstacle.setSize(size);
		obstacle.setFillColor(Color(255, 0, 0, 255));

		cost1.setOutlineColor(outlineColor);
		cost1.setOutlineThickness(outlineThickness);
		cost1.setSize(size);
		cost1.setFillColor(Color(255, 255, 255, 255));

		cost2.setOutlineColor(outlineColor);
		cost2.setOutlineThickness(outlineThickness);
		cost2.setSize(size);
		cost2.setFillColor(Color(210, 210, 210, 255));

		cost3.setOutlineColor(outlineColor);
		cost3.setOutlineThickness(outlineThickness);
		cost3.setSize(size);
		cost3.setFillColor(Color(140, 140, 140, 255));

		cost4.setOutlineColor(outlineColor);
		cost4.setOutlineThickness(outlineThickness);
		cost4.setSize(size);
		cost4.setFillColor(Color(70, 70, 70, 255));

		cost5.setOutlineColor(outlineColor);
		cost5.setOutlineThickness(outlineThickness);
		cost5.setSize(size);
		cost5.setFillColor(Color(0, 0, 0, 255));
	}
};

struct CircleNode {
	
	CircleShape											origin;
	CircleShape											destination;

	CircleShape											open;
	CircleShape											closed;
	CircleShape											path;

	CircleNode() {}

	CircleNode(Color outlineColor, float outlineThickness, Vector2f size) {
		
		closed.setOutlineColor(outlineColor);
		closed.setOutlineThickness(outlineThickness);
		closed.setRadius(size.x / 2.5f);
		closed.setFillColor(Color(64, 64, 255, 128));

		open.setOutlineColor(outlineColor);
		open.setOutlineThickness(outlineThickness);
		open.setRadius(size.x / 2.5f);
		open.setFillColor(Color(255, 255, 0, 128));

		path.setOutlineColor(outlineColor);
		path.setOutlineThickness(outlineThickness);
		path.setRadius(size.x / 2.5f);
		path.setFillColor(Color(0, 255, 0, 255));

		origin.setOutlineColor(outlineColor);
		origin.setOutlineThickness(outlineThickness);
		origin.setRadius(size.x / 2.5f);
		origin.setFillColor(Color(0, 0, 255, 255));

		destination.setOutlineColor(outlineColor);
		destination.setOutlineThickness(outlineThickness);
		destination.setRadius(size.x / 2.5f);
		destination.setFillColor(Color(0, 255, 0, 255));
	}
};

struct Bounds {
	unsigned short top;
	unsigned short bottom;
	unsigned short left;
	unsigned short right;

	Bounds() {}

	Bounds(
					Vector2f position,
					Vector2f size
	) {
		top = position.y;
		left = position.x;
		bottom = position.y + size.y;
		right = position.x + size.x;
	}

	Bounds(
					unsigned short top, 
					unsigned short bottom, 
					unsigned short left, 
					unsigned short right
	) {
		this->top = top;
		this->bottom = bottom;
		this->left = left;
		this->right = right;
	}

	bool isColliding(Vector2f& position) {
		if (position.x > left && position.x < right && position.y > top && position.y < bottom) {
			return true;
		}
		return false;
	}
};

struct AgentData {
	string			
  texturePath;
	
  Vector2			
  position, 
  direction;

	float
	acceleration,
	speed,
	mass,
	waitTime,

	seekMagnitude,
	fleeMagnitude,
	arriveMagnitude,
	pursueMagnitude,
	evadeMagnitude,
	wanderMagnitude,
	wanderTMagnitude,
	wanderRMagnitude,
	pathMagnitude,
	courseCorrection,
	neighborRadius,
	flockMagnitude,
	separationRadius,
	separationMagnitude,
	averageDirectionMagnitude,
	cohesionMagnitude,
	obstacleVision,
	obstacleDetectionRadius,
	obstacleAvoidanceMagnitude;
};

enum EHeuristic {
	SqrtDistance,
	Distance,
	Manhatan,
	Cheapest,
};

enum ESearchState {
	StillSearching,
	GoalReached,
	NoPath
};

enum EBehaviour {
	Seek = 1,
	Flee = 2,
	Arrive = 4,
	Pursue = 8,
	Evade = 16,
	Wander = 32,
	WanderR = 64,
	WanderT = 128,
	End = 256,
	Run = 512,
	Idle = 1024
};

enum EButton {
	Obstacle,
	Weight1,
	Weight2,
	Weight3,
	Weight4,
	Weight5,
	Origin,
	Objective,
	Start,
	Stop,
	Depth,
	Breadth,
	Best,
	Dijkstra,
	AStar,
	EuclidianDist,
	SqrtDist,
	CityDist,
	CheapestNode
};