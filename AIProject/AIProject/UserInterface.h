#pragma once
#include "Headers.h"

class UserInterface {
	
protected:

	vector <sf::Font>		m_fonts;

public:

	virtual void				Render(RenderWindow& window);
	virtual void				Initialize(Vector2f&	position);
	virtual void				ShutDown();
	virtual void				Update();

	UserInterface();
	virtual ~UserInterface();
};

