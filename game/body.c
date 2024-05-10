#include "body.h"

void Step(ncBody* body, float timestep)
{
	ExplicitEuler(body, dt);
	ClearForce(body);
}
