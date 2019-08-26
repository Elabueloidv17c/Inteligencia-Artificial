#pragma once
#include "Headers.h"
#include "UserInterface.h"

class Scene {

public:
	
	virtual void				ProcessMessages(Event& event, RenderWindow& window);
	virtual void				Initialize(Vector2f windowSize);
	virtual void				Render(RenderWindow& window);
	virtual void				ShutDown();
	virtual void				Update();

	Scene();
	virtual ~Scene();
};

