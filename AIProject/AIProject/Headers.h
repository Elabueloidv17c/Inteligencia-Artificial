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

//This is used in structs
#include "Vector2.h"

//This is used to short the type of some objects and functions
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::vector;
using std::string;
using std::cout;

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
struct WindowData
{
	string			
  name;

	int				
  width,
  heigh,
  style;
};

struct AgentData
{
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
	flockMagnitude,
	separationRadius,
	separationMagnitude,
	averageDirectionMagnitude,
	cohesionMagnitude,
	obstacleVision,
	obstacleDetectionRadius,
	obstacleAvoidanceMagnitude;
};

enum EBehaviour
{
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

//Constants
#define	PI													3.141592f
#define HALF												0.5f

//Type definitions
typedef std::chrono::time_point<std::chrono::steady_clock>	TimePoint;