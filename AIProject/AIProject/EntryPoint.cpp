#include "Headers.h"
#include "World.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main(){

	World 
  instance;

	instance.Initialize(WindowData{ "IA Project" , 1024, 1024, sf::Style::Default });
	instance.Update();

	return 0;
}