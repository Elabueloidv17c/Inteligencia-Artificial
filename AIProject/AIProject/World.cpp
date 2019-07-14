#include "World.h"

void 
World::Initialize(WindowData window) {

	//--------------------------------------------------------------------------------
	//Window
	//--------------------------------------------------------------------------------
	m_window.create(VideoMode(window.width, window.heigh), window.name, window.style);

	//--------------------------------------------------------------------------------
	//Track
	//--------------------------------------------------------------------------------	
	Path track;	{
		Color color = Color(255, 0, 0, 64);

		track.AddNode(PathNode(Vector2(77, 390),  100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(92, 145),  100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(208, 68),  100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(324, 127), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(425, 300), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(620, 300), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(716, 80),  100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(893, 97),  100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(948, 206), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(930, 377), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(465, 525), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(375, 594), 100.0f, 55.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(465, 642), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(630, 632), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(832, 629), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(950, 712), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(943, 833), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(860, 923), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(645, 933), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(609, 831), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(480, 820), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(324, 955), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(216, 980), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(139, 940), 100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(86, 801),  100.0f, 40.0f, 150.0f, color));
		track.AddNode(PathNode(Vector2(81, 670),  100.0f, 40.0f, 150.0f, color));
	}
	m_paths.push_back(track);

	//--------------------------------------------------------------------------------
	//Track
	//--------------------------------------------------------------------------------	
	m_obstacles; {
		Color color = Color(0, 255, 0, 64);

		m_obstacles.push_back(CircleObstacle(Vector2(795, 235), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(781, 321), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(682, 371), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(564, 388), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(410, 400), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(278, 402), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(223, 217), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(218, 327), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(218, 480), 60.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(202, 600), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(208, 722), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(256, 788), 70.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(241, 890), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(360, 750), 40.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(440, 750), 40.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(530, 745), 40.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(620, 748), 40.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(710, 751), 40.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(789, 779), 50.0f, color));

		m_obstacles.push_back(CircleObstacle(Vector2(998, 518), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(939, 524), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(885, 522), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(835, 520), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(779, 533), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(727, 537), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(679, 535), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(649, 552), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(605, 568), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(563, 569), 20.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(519, 570), 20.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(482, 570), 20.0f, color));

		m_obstacles.push_back(CircleObstacle(Vector2(200, 399), 50.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(487, 388), 20.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(516, 178), 60.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(511, 100), 60.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(346, 400), 40.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(511, 0), 60.0f, color));
		
		m_obstacles.push_back(CircleObstacle(Vector2(516, 903), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(520, 948), 30.0f, color));
		m_obstacles.push_back(CircleObstacle(Vector2(518, 990), 30.0f, color));
	}

#ifdef DEBUG
	m_levelDesigner.Initialize("../Level.txt");
#endif

	//--------------------------------------------------------------------------------
	//Agents																		 
	//--------------------------------------------------------------------------------
	vector <AgentData> agents; {
		agents.push_back(AgentData{
		"..\\Textures\\zerg.png",			//texturePath
		Vector2(65, 512),							//position
		Vector2(0.0f, -1.0f), 				//direction
		40.0f, 									      //acceleration
		180.0f,												//Speed
		100.0f, 									    //Mass
		1.0f, 									      //waitTime
		100.0f,								        //seekMagnitude
		1.0f,									        //fleeMagnitude
		50.0f,									      //arriveMagnitude
		4.0f,									        //pursueMagnitude
		3.0f,									        //evadeMagnitude
		0.0f,									        //wanderMagnitude
		0.0f,								          //wanderTimeMagnitude
		0.0f,									        //wanderRandomMagnitude
		300.0f,												//Path Magnitude
		2.0f,													//Course Correction
		0.0f,													//Flock Magnitude
		30.0f,												//Separation Radius
		10.0f,												//Separation Magnitude
		0.0f,													//Average Direction Magnitude
		0.0f,													//CohesionMagnitude
		50.0f,												//Obstacle Vision
		100.0f,												//Obstacle Detection Radius
		400.0f												//Obstacle Avoidance Magnitude;
			});
		agents.push_back(AgentData{
		"..\\Textures\\marine.png",		//texturePath
		Vector2(90, 512),							//position
		Vector2(0.0f, -1.0f), 				//direction
		50.0f, 									      //acceleration
		190.0f,												//Speed
		140.0f, 									    //Mass
		1.0f, 									      //waitTime
		100.0f,								        //seekMagnitude
		1.0f,									        //fleeMagnitude
		50.0f,									      //arriveMagnitude
		4.0f,									        //pursueMagnitude
		3.0f,									        //evadeMagnitude
		0.0f,									        //wanderMagnitude
		0.0f,								          //wanderTimeMagnitude
		0.0f,									        //wanderRandomMagnitude
		300.0f,												//Path Magnitude
		2.0f,													//Course Correction
		0.0f,													//Flock Magnitude
		30.0f,												//Separation Radius
		10.0f,												//Separation Magnitude
		0.0f,													//Average Direction Magnitude
		0.0f,													//CohesionMagnitude
		50.0f,												//Obstacle Vision
		100.0f,												//Obstacle Detection Radius
		400.0f												//Obstacle Avoidance Magnitude;
			});
		agents.push_back(AgentData{
		"..\\Textures\\zealot.png",		//Texture Path
		Vector2(115, 512),						//Position
		Vector2(0.0f, -1.0f), 				//Direction
		40.0f, 									      //Acceleration
		200.0f,												//Speed
		160.0f, 									    //Mass
		1.0f, 									      //Wait Time
		0.0f,												  //Seek Magnitude
		1.0f,									        //Flee Magnitude
		50.0f,									      //Arrive Magnitude
		4.0f,									        //Pursue Magnitude
		3.0f,									        //Evade Magnitude
		0.0f,									        //Wander Magnitude
		0.0f,								          //Wander Time Magnitude
		0.0f,									        //Wander Random Magnitude
		300.0f,												//Path Magnitude
		2.0f,													//Course Correction
		0.0f,													//Flock Magnitude
		30.0f,												//Separation Radius
		10.0f,												//Separation Magnitude
		0.0f,													//Average Direction Magnitude
		150.0f,												//CohesionMagnitude
		60.0f,												//Obstacle Vision
		100.0f,												//Obstacle Detection Radius
		400.0f												//Obstacle Avoidance Magnitude;
			});
	}

	m_agents.Initialize(agents);

	for (int i = 0; i < m_agents.GetNumAgents(); i++)
	{
		m_agents.GetAgentAt(i)->SetPath(m_paths[0].GetPath());
		m_agents.GetAgentAt(i)->SetFlock(&m_agents);
		m_agents.GetAgentAt(i)->SetObstacles(&m_obstacles);
	}

	m_timer.Start();

	if (!m_backGroundexture.loadFromFile("..\\Textures\\Track.png")) {
		return;
	}

	m_backgroundSprite.setTexture(m_backGroundexture);
	m_backgroundSprite.setPosition(0, 0);
}

void 
World::CatchMessages() {
	while (m_window.pollEvent(m_envent)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			m_levelDesigner.AddNode(sf::Mouse::getPosition(m_window));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	
		}
		if (Event::Closed == m_envent.type) {
			m_window.close();
		}
		if (m_envent.type == Event::Resized){
			FloatRect newSize(0, 0, m_envent.size.width, m_envent.size.height);
			m_window.setView(View(newSize));
		}
	}
}

void 
World::Update() {
	while (m_window.isOpen()) {
		CatchMessages();
		
    m_agents.Update(m_agents, m_timer.GetDeltaTime());
	
		Render();
	}
}

void 
World::Render() {
	//Clear screen
	m_window.clear();

	//--------------------------------------------------------------------
	//Prepare frame
	//--------------------------------------------------------------------
	
	//Draw Backgrond
	m_backgroundSprite.setPosition(0, 0);
	m_window.draw(m_backgroundSprite);
	
#ifdef DEBUG
	//Draw Shapes
	for (size_t i = 0; i < m_paths[0].GetPath()->size(); i++)
	{
		m_paths[0].GetNodeAt(i)->GetShape()->setPosition(Vector2f(m_paths[0].GetNodeAt(i)->GetPosition()->x, m_paths[0].GetNodeAt(i)->GetPosition()->y));
		m_window.draw(*m_paths[0].GetNodeAt(i)->GetShape());
	}
	//Draw Obstacles
	for (size_t i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles[i].GetShape()->setPosition(Vector2f(m_obstacles[i].GetPosition()->x, m_obstacles[i].GetPosition()->y));
		m_window.draw(*m_obstacles[i].GetShape());
	}
#endif // DEBUG

	//Draw Agents
	m_agents.Render(m_window);

	//Present frame
	m_window.display();
}
