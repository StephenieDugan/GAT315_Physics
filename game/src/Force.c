#include "Force.h"
#include "body.h"
#include "raymath.h"

void ApplyGravitationForce(ncBody* bodies, float strength)
{
	for (ncBody* body1 = bodies; body1; body1 = body1->next)
	{
		for (ncBody* body2 = bodies; body2; body2 = body2->next)
		{
			//<if bodies are the same, continue>
			if (body1 == body2) continue;
				//< calculate direction(body position - body position)
			Vector2 direction = Vector2Subtract(body1->position, body2->position);
			float distance = Vector2Length(direction);

			distance = fmaxf(1, distance);
			float force = (body1->mass * body2->mass / (distance * distance)) * strength;
			//<scale normalized direction vector by force>
			direction = Vector2Scale(direction, force);

			ApplyForce(body1, Vector2Negate(direction), FM_FORCE);
			ApplyForce(body2, direction, FM_FORCE);
		}
	}
}
