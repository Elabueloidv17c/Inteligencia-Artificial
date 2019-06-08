#include "Math.h"

float Math::RandomNumber(int min, int max)
{
	if (max != 0)
	{
		if (min < 0)
		{
			max += abs(min);
		}
		
		return rand() % max + min;
	}

	return 0;
}

Math::Math()
{
	srand(time(NULL));
}

Math::~Math()
{
}
