#include "Boid.h"
#include "Timer.h"
#include "PathNode.h"
#include "AgentManager.h"

Boid* Boid::GetEvadeObjective()
{
	return m_evadeObjective;
}

Boid* Boid::GetPursueObjective()
{
	return m_pursueObjective;
}

vector<PathNode>* Boid::GetPath()
{
	return m_path;
}

vector<CircleObstacle>* Boid::GetObstacles()
{
	return m_obstacles;
}

AgentManager * Boid::GetParent()
{
	return m_parent;
}

int * Boid::GetCurrentPathNode()
{
	return &m_currentPathNode;
}

bool * Boid::GetIsPathReverse()
{
	return &m_isPathReverse;
}

Boid::Boid() {
	m_currentState = EBehaviour::Run;
	m_currentLap = 1;
	m_timer = 0.0f;
	m_currentPathNode = 0;
	m_seekObjective = nullptr;
	m_fleeObjective = nullptr;
	m_evadeObjective = nullptr;
	m_pursueObjective = nullptr;
	m_arriveObjective = nullptr;
	m_obstacles = nullptr;
	m_parent = nullptr;
	m_path = nullptr;
}

Boid::~Boid() {

}

#ifdef DEBUG
void 
Boid::DrawLine(Vector2 position, Vector2 direction, RenderWindow& window, float magnitude){
	direction *= magnitude;

	Vertex line[2] = { Vertex(Vector2f(position.x , position.y)), 
	Vertex(Vector2f(position.x + direction.x, position.y + direction.y)) };

	window.draw(line, 2, sf::Lines);
}
#endif // DEBUG

bool 
Boid::Initialize(AgentData& agent) {
	m_position = agent.position;
	m_direction = agent.direction;

	m_acceleration = agent.acceleration;
	m_waitTime = agent.waitTime;
	m_currentSpeed = 0.0f;
	m_speed = agent.speed;
	m_mass = 1/agent.mass;

	m_seekMagnitude = agent.seekMagnitude;
	m_fleeMagnitude = agent.fleeMagnitude;
	m_arriveMagnitude = agent.arriveMagnitude;
	m_pursueMagnitude = agent.pursueMagnitude;
	m_evadeMagnitude = agent.evadeMagnitude;
	m_wanderMagnitude = agent.wanderMagnitude;
	m_wanderTMagnitude = agent.wanderTMagnitude;
	m_wanderRMagnitude = agent.wanderRMagnitude;
	m_pathMagnitude = agent.pathMagnitude;
	m_courseCorrection = agent.courseCorrection;
	m_pathMagnitude = agent.pathMagnitude;
	m_courseCorrection = agent.courseCorrection;
	m_flockMagnitude = agent.flockMagnitude;

	m_separationRadius = agent.separationRadius;
	m_separationMagnitude = agent.separationMagnitude;
	m_averageDirectionMagnitude = agent.averageDirectionMagnitude;
	m_cohesionMagnitude = agent.cohesionMagnitude;

	m_vision = m_direction * m_visionRange;

	m_obstacleAvoidanceMagnitude = agent.obstacleAvoidanceMagnitude;
	m_obstacleDetectionRadius = agent.obstacleDetectionRadius;
	m_obstacleVision = agent.obstacleVision;

	if (!m_texture.loadFromFile(agent.texturePath)){
		return false;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position.x, m_position.y);

	return true;
}

void 
Boid::Update(float deltaTime) {
	
	//Set steering force to 0 at the beginning of each frame
	m_steeringForce = Vector2();

	//Setting up the current speed
	m_currentSpeed += m_acceleration * deltaTime;

	//If current speed is bigger than max speed
	if (m_currentSpeed > m_speed){
		//truncate current speed to max speed
		m_currentSpeed = m_speed;
	}

	//------------------------------------------------------------------------------------------------------------------
	//ADDING FORCES
	//------------------------------------------------------------------------------------------------------------------
	if (m_seekObjective != nullptr){
		m_steeringForce += Seek(m_position, *m_seekObjective, m_seekMagnitude);
	}
	if (m_fleeObjective != nullptr){
		m_steeringForce += Flee(m_position, *m_fleeObjective, m_fleeMagnitude, 200);
	}
	if (m_arriveObjective != nullptr){
		m_steeringForce += Arrive(m_position, *m_arriveObjective, 100, m_arriveMagnitude);
	}
	if (m_pursueObjective != nullptr){
		m_steeringForce += Pursue(m_position, m_pursueObjective, m_pursueMagnitude, 4.0f, deltaTime);
	}
	if (m_evadeObjective != nullptr){
		m_steeringForce += Evade(m_position, m_evadeObjective, m_evadeMagnitude, 100, 3.0f, deltaTime);
	}
	if (m_path != nullptr) {
		m_steeringForce += FollowCircuit(m_position, *m_path, m_currentPathNode, m_currentSpeed, m_courseCorrection, m_pathMagnitude, deltaTime);
	}
	if (m_parent != nullptr) {
		m_steeringForce += Separation(m_position, *m_parent, m_separationRadius, m_separationMagnitude) * (m_currentSpeed / m_speed);
	}
	if (m_obstacles != nullptr) {
		m_steeringForce += ObstacleAvoidance(m_position, m_direction, m_obstacleVision, GetClosestObstacle(m_position, 
		m_obstacleDetectionRadius, m_obstacles), m_obstacleAvoidanceMagnitude);
	}

	m_steeringForce += Wander(m_position, m_direction, m_wanderMagnitude, 300, 150, 120, deltaTime, m_timer, m_waitTime);
	m_steeringForce += Wander(m_position, m_direction, -200, 200, m_wanderTMagnitude, deltaTime, m_timer, m_waitTime);
	m_steeringForce += Wander(m_position, -200, 200, m_wanderRMagnitude);

	//------------------------------------------------------------------------------------------------------------------
	//CALCULATING NEW DIRECTION
	//------------------------------------------------------------------------------------------------------------------
	if (m_steeringForce.Magnitude() > 0) {
		m_steeringDirection = (m_steeringForce - m_direction) * m_mass;
		m_direction += m_steeringDirection * deltaTime;
		m_direction.Normalize();

		m_steeringForce.Truncated(m_currentSpeed);
		m_position += m_direction * m_steeringForce.Magnitude() * deltaTime;
	}
}

void 
Boid::SetSeekObjective(Vector2* objective) {
	m_seekObjective = objective;
}

void Boid::SetFlock(AgentManager* parent) {
	m_parent = parent;
}

void 
Boid::SetPath(vector<PathNode>* path) {
  m_path = path;
}

void
Boid::SetObstacles(vector<CircleObstacle>* obstacle) {
	m_obstacles = obstacle;
}

void 
Boid::SetPathOrientation(bool isReverse) {
	m_isPathReverse = isReverse;
}

void 
Boid::SetCurrentPathNode(int node) {
	m_currentPathNode = node;
}

void 
Boid::SetFleeObjective(Vector2* objective) {
	m_fleeObjective = objective;
}

void 
Boid::SetArriveObjective(Vector2* objective) {
	m_arriveObjective = objective;
}

void 
Boid::SetPursueObjective(Boid * objective) {
	m_pursueObjective = objective;
}

void 
Boid::SetEvadeObjective(Boid * objective) {
	m_evadeObjective = objective;
}

void 
Boid::SetPosition(int x, int y) {
	m_position.x = x;
	m_position.y = y;
}

Boid* 
Boid::Get(){
	return this;
}

Vector2 * Boid::GetDirection()
{
	return &m_direction;
}

Vector2 * Boid::GetVision()
{
	return &m_vision;
}

Vector2 * Boid::GetSteeringForce()
{
	return &m_steeringForce;
}

Vector2 * Boid::GetSteeringDirection()
{
	return &m_steeringDirection;
}

unsigned int * Boid::GetCurrentLap()
{
	return &m_currentLap;
}

EBehaviour*
Boid::GetCurrentState() {
	return &m_currentState;
}

Vector2 * Boid::GetSeekObjective()
{
	return m_seekObjective;
}

Vector2 * Boid::GetFleeObjective()
{
	return m_fleeObjective;
}

Vector2 * Boid::GetArriveObjective()
{
	return m_arriveObjective;
}

void 
Boid::SetCurrentState(EBehaviour state) {
	m_currentState = state;
}

void 
Boid::Render(RenderWindow& window) {
	//Getting the center of the agent's sprite
	m_sprite.setOrigin(m_texture.getSize().x * HALF, m_texture.getSize().y * HALF);
	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setRotation((atan(m_direction.y / m_direction.x) * 180.0f / PI) - 90.0f);

#ifdef DEBUG
	DrawLine(m_position, m_direction, window, m_speed);
#endif // DEBUG

	window.draw(m_sprite);
}

//Behaviours
Vector2 
Boid::Seek(const Vector2& position, const Vector2& objective, float magnitude) {
	Vector2 target = objective - position;
	target.Normalize();

	return target *= magnitude;
}

Vector2 Boid::Flock(const Vector2& position, AgentManager& agents, float separationRadius, float separationMagnitude,
float cohesionMagnitude, float averageDirectionMagnitude) {

	return Separation(position, agents, separationRadius, separationMagnitude) + 
	Cohesion(position, agents, cohesionMagnitude) + AvergeDirection(agents, averageDirectionMagnitude);
}
Vector2 Boid::Separation(const Vector2& position, AgentManager& agents, float radius, float magnitude) {

	Vector2 repulsion;
	Vector2 distance;

	for (int i = 0; i < agents.GetNumAgents(); i++)
	{
		distance = agents.GetAgentAt(i)->m_position - position;
		if(distance.Magnitude() < radius) {
			repulsion += distance.Normalized() * (1 - (distance.Magnitude() + 0.0000001f / radius) * magnitude);
		}
	}

	return repulsion;
}
Vector2 Boid::Cohesion(const Vector2& position, AgentManager& agents, float magnitude)
{
	Vector2 atraction;

	for (int i = 0; i < agents.GetNumAgents(); ++i) {
		atraction += agents.GetAgentAt(i)->m_position;
	}
	atraction /= agents.GetNumAgents();

	return Seek(position, atraction, magnitude);
}
Vector2 Boid::AvergeDirection(AgentManager& agents, float magnitude)
{
	Vector2 newDir;

	for (int i = 0; i < agents.GetNumAgents(); ++i) {
		newDir += agents.GetAgentAt(i)->m_direction;
	}
	newDir /= agents.GetNumAgents();


	return newDir.Normalized() * magnitude;
}

Vector2 
Boid::Flee(const Vector2& position, const Vector2& danger, const float& magnitude, const float& radius) {
	Vector2 target = position - danger;

	if (target.Magnitude() <= radius){
		return -Seek(position, danger, magnitude);
	}

	return Vector2();
}

Vector2 
Boid::Arrive(const Vector2& position, const Vector2& objective, float radius, float magnitude) {
	Vector2 target = objective - position;
	target.Normalize();
	target *= magnitude;

	if ((objective - position).Magnitude() <= radius){
		return target *= (objective - position).Magnitude() / radius;
	}
	return target;
}

Vector2 
Boid::Pursue(const Vector2& position, const Boid* objective, float magnitude, float projectedTime, float deltaTime) {
	Vector2 target = objective->m_position - position;

	Vector2 projectedPosition = objective->m_position + (objective->m_direction * objective->m_currentSpeed * projectedTime);

	if (target.Magnitude() <= projectedPosition.Magnitude()){
		projectedPosition = objective->m_position + (objective->m_direction * objective->m_currentSpeed * deltaTime);
	}

	return Seek(position, projectedPosition, magnitude);
}

Vector2 
Boid::Evade(const Vector2& position, const Boid* danger, float magnitude, float radius, float projectedTime, float deltaTime) {
	Vector2 target = position - danger->m_position;
	Vector2 projectedDanger = danger->m_position + (danger->m_direction * danger->m_currentSpeed * projectedTime * HALF);

	if (target.Magnitude() <= radius){
		return Flee(position, projectedDanger, magnitude, radius);
	}
	return Vector2();
}

Vector2 
Boid::Wander(const Vector2& position, const Vector2& direction, float magnitude, float distProj, float radius, int angle, float deltaTime, 
float& currentTime, float timeLimit) {
	currentTime += deltaTime;

	if (currentTime < timeLimit) {
		return direction * magnitude;
	}

	currentTime = 0.0f;

	Vector2 ProjectedPosition = position + (direction * distProj);

	float radians = Math::RandomNumber(0, angle) * (PI / 180);
	float finalAngle = (atan(direction.y / direction.x) - ((angle * PI / 180) * HALF)) + radians;

	ProjectedPosition.x += radius * cos(finalAngle);
	ProjectedPosition.y += radius * sin(finalAngle);

	return Seek(position, ProjectedPosition, magnitude);
}

Vector2
Boid::Wander(const Vector2& position, const Vector2& direction, int min, int max, float magnitude, float deltaTime, 
float& currentTime, float timeLimit) {
	currentTime += deltaTime;

	if (currentTime < timeLimit) {
		return direction * magnitude;
	}
	currentTime = 0.0f;
	return Wander(position, min, max, magnitude);
}

Vector2 
Boid::Wander(const Vector2& position, int min, int max, float magnitude) {
	Vector2 objective = Vector2(Math::RandomNumber(min, max), Math::RandomNumber(min, max));
	return Seek(position, objective, magnitude);
}

//Follow Path (common)
//Follow The leader

CircleObstacle* 
Boid::GetClosestObstacle(const Vector2& position, const float& detectionRadius, vector<CircleObstacle>* obstacles) {

	CircleObstacle* closest = nullptr;
	float minDistance = detectionRadius;
	float currentDistance = detectionRadius;

	for (size_t i = 0; i < obstacles->size(); i++) {

		currentDistance = (*obstacles[0][i].GetPosition() - position).Magnitude();

		if (currentDistance < detectionRadius && currentDistance < minDistance) {
			closest = &obstacles[0][i];
			minDistance = currentDistance;
		}
	}

	return closest;
}

Vector2 	
Boid::ObstacleAvoidance(const Vector2& position, const Vector2& direction, const float visionRange, CircleObstacle* obstacle,
const float& magnitude) {
	
	if (obstacle) {
		Vector2	vision = direction * visionRange, obstacleDistance;
		float	obstacleAngle = 0.0f;

		obstacleDistance = (*obstacle->GetPosition() - position);
		obstacleAngle = obstacleDistance.Dot(vision) / visionRange;

		if (obstacleAngle > 0 && obstacleAngle <= visionRange && obstacleDistance.Magnitude() <= visionRange) {
			return ((direction * obstacleAngle) - obstacleDistance).Normalized() * magnitude;
		}
	}
	return Vector2();
}

Vector2 
Boid::FollowCircuit(const Vector2& position, vector <PathNode>& path, int& currentNode, float&currentSpeed, float correctionMag, 
float magnitude,float deltaTime) {

	/*
#ifdef DEBUG
	path[currentNode].SetColor(Color{ 0, 0, 255, 64 });
#endif // DEBUG

	Vector2 destination = *path[((currentNode + 1) >= path.size()) ? 0 : currentNode + 1].GetPosition();
	Vector2 route = destination - *path[currentNode].GetPosition();

	//Vector from current path node to entity position projected on the vector from current to next path node
	Vector2 distance = (position - *path[currentNode].GetPosition()).Projection(route);

	//Get the closest position  in the road
	Vector2 offset = *path[currentNode].GetPosition() + distance;

	if ((offset - position).Magnitude() > path[currentNode].GetRoadLimit() && currentSpeed > path[currentNode].GetFriction()) {
		currentSpeed -= path[currentNode].GetFriction() * deltaTime;
	}

	//Then a subtract of the resulting vector and the one from current path node to entity
	distance -= (position - *path[currentNode].GetPosition());

	//Set same magnitude to both Seek and course correction
	distance.Normalize();
	distance *= correctionMag;

	if ((destination - position).Magnitude() < path[currentNode].GetSize()) {
#ifdef DEBUG
		path[currentNode].SetColor(Color{ 255, 0, 0, 64 });
#endif // DEBUG

		currentNode++;

		if (currentNode >= path.size()) {
			currentNode = 0;
		}
	}
	return Seek(position, destination, magnitude) + distance;
*/

#ifdef DEBUG
	path[currentNode].SetColor(Color{ 0, 0, 255, 64 });
#endif // DEBUG

	Vector2 destination = *path[((currentNode + 1) >= path.size()) ? 0 : currentNode + 1].GetPosition();
	Vector2 route = destination - *path[currentNode].GetPosition();

	Vector2 closestPointVector = (position - *path[currentNode].GetPosition()).Projection(route);
	Vector2 closestPointVectorWorld = *path[currentNode].GetPosition() + closestPointVector;

	float correctionMagnitude = ((closestPointVectorWorld - position).Magnitude() / path[currentNode].GetRoadLimit()) * magnitude;

	Vector2 courseCorrection = Seek(position, closestPointVectorWorld, correctionMagnitude);

	if ((destination - position).Magnitude() < path[currentNode].GetSize()) {

#ifdef DEBUG
		path[currentNode].SetColor(Color{ 255, 0, 0, 64 });
#endif // DEBUG

		currentNode++;
		if (currentNode >= path.size()) {
			currentNode = 0;
		}
	}

	return Seek(position, destination, magnitude) + courseCorrection;
}

float * Boid::GetSeekMagnitude()
{
	return &m_seekMagnitude;
}

float * Boid::GetFleeMagnitude()
{
	return &m_fleeMagnitude;
}

float * Boid::GetEvadeMagnitude()
{
	return &m_evadeMagnitude;
}

float * Boid::GetArriveMagnitude()
{
	return &m_arriveMagnitude;
}

float * Boid::GetPursueMagnitude()
{
	return &m_pursueMagnitude;
}

float * Boid::GetWanderMagnitude()
{
	return &m_wanderMagnitude;
}

float * Boid::GetWanderTMagnitude()
{
	return &m_wanderTMagnitude;
}

float * Boid::GetWanderRMagnitude()
{
	return &m_wanderRMagnitude;
}

float * Boid::GetVisionRange()
{
	return &m_visionRange;
}

float * Boid::GetPathMagnitude()
{
	return &m_pathMagnitude;
}

float * Boid::GetCourseCorrection()
{
	return &m_courseCorrection;
}

float * Boid::GetFlockMagnitude()
{
	return &m_flockMagnitude;
}

float * Boid::GetSeparationRadius()
{
	return &m_separationRadius;
}

float * Boid::GetSeparationMagnitude()
{
	return &m_separationMagnitude;
}

float * Boid::GetAverageDirectionMagnitude()
{
	return &m_averageDirectionMagnitude;
}

float * Boid::GetCohesionMagnitude()
{
	return &m_cohesionMagnitude;
}

float * Boid::GetObstacleVision()
{
	return &m_obstacleVision;
}

float * Boid::GetObstacleDetectionRadius()
{
	return &m_obstacleDetectionRadius;
}

float * Boid::GetObstacleAvoidanceMagnitude()
{
	return &m_obstacleAvoidanceMagnitude;
}

float * Boid::GetAcceleration()
{
	return &m_acceleration;
}

float * Boid::GetCurrentSpeed()
{
	return &m_currentSpeed;
}

float * Boid::GetWaitTime()
{
	return &m_waitTime;
}

float * Boid::GetTimer()
{
	return &m_timer;
}

float * Boid::GetSpeed()
{
	return &m_speed;
}

float * Boid::GetMass()
{
	return &m_mass;
}

Vector2 * Boid::GetPosition()
{
	return &m_direction;
}