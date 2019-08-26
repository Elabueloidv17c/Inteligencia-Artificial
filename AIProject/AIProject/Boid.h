#pragma once
#include "Headers.h"
#include "CircleObstacle.h"
#include "Vector2.h"
#include "Math.h"

class PathNode;
class AgentManager;

class Boid
{
	EBehaviour 
	m_currentState;

	Vector2u			
  m_textureCenter;

	Texture				
  m_texture;

	Sprite				
  m_sprite;

	Vector2
	m_position,
  m_direction,
	m_vision,
	m_steeringForce,
	m_steeringDirection;

	float				
  m_acceleration,
	m_currentSpeed,
	m_waitTime,
	m_timer,
	m_speed,
	m_mass,

	m_seekMagnitude,
	m_fleeMagnitude,
	m_evadeMagnitude,
	m_arriveMagnitude,
	m_pursueMagnitude,
	m_wanderMagnitude,
	m_wanderTMagnitude,
	m_wanderRMagnitude,

	m_neighborRadius,
	m_visionRange,
	m_pathMagnitude,
	m_courseCorrection,
	m_flockMagnitude,
	m_separationRadius,
	m_separationMagnitude,
	m_averageDirectionMagnitude,
	m_cohesionMagnitude,
	m_obstacleVision,
	m_obstacleDetectionRadius,
	m_obstacleAvoidanceMagnitude;

	Vector2*
  m_seekObjective;
	Vector2*
  m_fleeObjective;
	Vector2*
  m_arriveObjective;

	Boid*	
  m_evadeObjective;
	Boid*	
  m_pursueObjective;

	vector <PathNode>*
  m_path;

	vector <CircleObstacle>* 
	m_obstacles;

	vector <CircleObstacle>*
	m_closeObstacles;

	AgentManager* 
	m_parent;

	vector <Boid*>
	m_neighbors;

	int					
  m_currentPathNode;

	bool
	m_isPathReverse;

public:

	Vector2*
	GetPosition();

	Vector2*
	GetDirection();

	Vector2*
	GetVision();

	Vector2*
	GetSteeringForce();

	Vector2*
	GetSteeringDirection();

	EBehaviour*
	GetCurrentState();

	Vector2*
	GetSeekObjective();
	Vector2*
	GetFleeObjective();
	Vector2*
	GetArriveObjective();

	Boid*
	GetEvadeObjective();

	Boid*
	GetPursueObjective();

	vector <PathNode>*
	GetPath();

	vector <CircleObstacle>*
	GetObstacles();

	AgentManager*
	GetParent();

	int*
	GetCurrentPathNode();

	bool*
	GetIsPathReverse();

	Boid();
	~Boid();

	bool 
  Initialize(
							AgentData& agent
	);
	
	void
	Render(
			RenderWindow& window
	);

	void
	Update(
			float deltaTime
	);

#ifdef DEBUG
	void
  DrawLine(
						Vector2 position, 
						Vector2 direction, 
						RenderWindow& window, 
						float magnitude
	);
#endif 

	void
	SetPosition(int x, int y),

	SetSeekObjective(Vector2* objective),
	SetFleeObjective(Vector2* objective),
	SetArriveObjective(Vector2* objective),
	SetPursueObjective(Boid* objective),
	SetEvadeObjective(Boid* objective),

	SetObstacles(vector<CircleObstacle>* obstacle),
	SetFlock(AgentManager* parent),

	SetPath(vector<PathNode>* path),
	SetPathOrientation(bool isReverse),
	SetCurrentPathNode(int node);

	Boid* 
  Get();
	
	void
	SetCurrentState(EBehaviour state);

	static Vector2 
  Seek(
		const Vector2& position, 
		const Vector2& objective, 
		float magnitude
	);

	static Vector2
	Flee(
		const Vector2& position, 
		const Vector2& danger, 
		const float& magnitude, 
		const float& radius
	);

	static Vector2
	Arrive(
		const Vector2& position, 
		const Vector2& objective, 
		float radius, 
		float magnitude
	);
	
	static Vector2
	Pursue(
		const Vector2& position, 
		const Boid* objective, 
		float magnitude, 
		float projectedTime, 
		float deltaTime
	);

	static Vector2
	Evade(
		const Vector2& position, 
		const Boid* danger, 
		float magnitude, 
		float radius, 
		float projectedTime, 
		float deltaTime
	);
	
	static Vector2
	Wander(
		const Vector2& position, 
		int min, 
		int max, 
		float magnitude
	);

	static Vector2
	Wander(
		const Vector2& position,
		const Vector2& direction, 
		int min, 
		int max, 
		float magnitude, 
		float deltaTime, 
		float& currentTime,
		float timeLimit
	);

	static Vector2
	Wander(
		const Vector2& position, 
		const Vector2& direction, 
		float magnitude, 
		float distProj, 
		float radius, 
		int angle,
		float deltaTime, 
		float& currentTime, 
		float timeLimit
	);
  
	static Vector2
	ObstacleAvoidance(
		const Vector2& position, 
		const Vector2& direction, 
		const float visionRange, 
		CircleObstacle* obstacle, 
		const float& magnitude
	);

	static Vector2
	FollowPathC(
		const Vector2& position,
		vector <PathNode>& path,
		int& currentNode,
		float magnitude
	);

	static Vector2
	FollowPath(
		const Vector2& position,
		vector <PathNode>& path,
		int& currentNode,
		float magnitude
	);

	CircleObstacle* 
	GetClosestObstacle(
		const Vector2& position, 
		const float& detectionRadius, 
		vector <CircleObstacle>* obstacles
	);

	//FollowTheLeader();
	
	static Vector2
		Separation(const Vector2& position, vector <Boid*>& neighbors, float radius, float magnitude);

	static Vector2
	Cohesion(
		const Vector2& position, 
		vector <Boid*>& neighbors, 
		float magnitude
	);

	static Vector2
	AvergeDirection(
		vector <Boid*>& neighbors, 
		float magnitude
	);

	static Vector2
	Flock(
		const Vector2& position, 
		vector <Boid*>& neighbors, 
		float separationRadius, 
		float separationMagnitude,
		float cohesionMagnitude, 
		float averageDirectionMagnitude
	);

	static void
	GetNeighbors(
		const Vector2& position,
		const float& radius,
		AgentManager& agents,
		vector <Boid*>& neighbors
	);

	//--------------------------------------------------------------------------------------------------------------------------------
	//Car Functions
	//--------------------------------------------------------------------------------------------------------------------------------
	
	static Vector2
	FollowCircuit(
		const Vector2& position, 
		vector <PathNode>& path, 
		int& currentNode, 
		float& currentSpeed, 
		float correctionMag, 
		float magnitude,
		float deltaTime
	);
};

