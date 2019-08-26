#include "Button.h"

void 
Button::Initialize(Color color, Color textColor, sf::Font* font, string name, unsigned int fontSize, Vector2f position, Vector2f size) {
	
	m_position = position;

	m_background.setOutlineColor(Color(64, 64, 64, 255));
	m_background.setOutlineThickness(2);
	m_background.setPosition(position);
	m_background.setFillColor(color);
	m_background.setSize(size);

	m_bounds = Bounds(position.y, position.y + size.y, position.x, position.x + size.x);

	m_font = font;
	m_text.setFont(*m_font);
	m_text.setFillColor(textColor);
	m_text.setString(name);
	m_text.setCharacterSize(fontSize);
	m_text.setPosition(position + Vector2f(2, 2));
	m_text.setStyle(sf::Text::Bold);
}

void 
Button::Initialize(Color color, Color textColor, sf::Font* font, string name, unsigned int fontSize, Vector2f position, float radius) {
	m_position = position;

	m_cBackground.setOutlineColor(Color(64, 64, 64, 255));
	m_cBackground.setOutlineThickness(2);
	m_cBackground.setPosition(position);
	m_cBackground.setFillColor(color);
	m_cBackground.setRadius(radius);

	m_bounds = Bounds(position.y, position.y + (radius * 2), position.x, position.x + (radius * 2));

	m_font = font;
	m_text.setFont(*m_font);
	m_text.setFillColor(textColor);
	m_text.setString(name);
	m_text.setCharacterSize(fontSize);
	m_text.setPosition(position + Vector2f(2, 2));
	m_text.setStyle(sf::Text::Bold);
}

bool
Button::IsPressed(Vector2f& mousePosition) {
	if (m_bounds.isColliding(mousePosition)) {
		m_isPressed = false;
		return true;
	}
	return false;
}

void
Button::Render(RenderWindow& window) {
	if (m_cBackground.getRadius() > 0) {
		window.draw(m_cBackground);
	}
	else {
		window.draw(m_background);
	}
	window.draw(m_text);
}

void
Button::ShutDown() {

}

const Bounds*
Button::GetBounds() {
	return &m_bounds;
}

Button::Button() {

}

Button::~Button() {

}
