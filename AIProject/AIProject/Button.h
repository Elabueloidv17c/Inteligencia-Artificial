#pragma once
#include "Headers.h"

class Button {

	CircleShape								m_cBackground;
	RectangleShape						m_background;
	Vector2f									m_position;
	Bounds										m_bounds;
	sf::Text									m_text;
	sf::Font*									m_font;
	bool											m_isPressed;

public:

	void Initialize(Color color, Color textColor, sf::Font* font, string name, unsigned int fontSize, Vector2f position, Vector2f size);
	void Initialize(Color color, Color textColor, sf::Font* font, string name, unsigned int fontSize, Vector2f position, float radius);
	bool IsPressed(Vector2f& mousePosition);
	void Render(RenderWindow& window);
	void ShutDown();

	const Bounds* GetBounds();

	Button();
	~Button();
};

