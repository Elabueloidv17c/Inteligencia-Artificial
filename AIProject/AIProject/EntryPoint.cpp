#include "Headers.h"
#include "Vector2.h"
#include "Boid.h"

void main()
{
	Boid Entity;

	Vector2 position(4.0f, 4.0f);
	Vector2 danger(5.0f, 5.0f);

	Vector2 Final = Entity.Evade(position, 2, danger, 3, 1, 2);
}