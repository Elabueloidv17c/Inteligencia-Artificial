#include "Headers.h"
#include "World.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main(){

	World 
  instance;

	instance.Initialize(WindowData{ "IA Project" , 1280, 720, sf::Style::Titlebar | sf::Style::Close });
	instance.Update();

	return 0;
}