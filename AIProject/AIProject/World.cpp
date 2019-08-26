#include "PathFinding.h"
#include "World.h"

void
World::Initialize(WindowData window) {

	//--------------------------------------------------------------------------------
	//Window
	//--------------------------------------------------------------------------------
	m_window.create(VideoMode(window.width, window.heigh), window.name, window.style);

	//--------------------------------------------------------------------------------
	//Scene
	//--------------------------------------------------------------------------------
	m_scene = new PathFinding();
	m_scene->Initialize(Vector2f(m_window.getSize().x, m_window.getSize().y));

	//--------------------------------------------------------------------------------
	//Timer
	//--------------------------------------------------------------------------------
	m_timer.Start();
}

void
World::ShutDown() {
	if (m_scene) {
		delete m_scene;
		m_scene = nullptr;
	}
}

void
World::CatchMessages() {
	while (m_window.pollEvent(m_event)) {
		m_scene->ProcessMessages(m_event, m_window);
	}
}

void
World::Update() {
	while (m_window.isOpen()) {
		m_scene->Update();
		CatchMessages();
		Render();
	}
}

void
World::Render() {

	//--------------------------------------------------------------------
	//Prepare frame
	//--------------------------------------------------------------------
	m_window.clear();
	m_scene->Render(m_window);

	//--------------------------------------------------------------------
	//Present frame
	//--------------------------------------------------------------------
	m_window.display();
}
