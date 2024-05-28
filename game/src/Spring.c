#include "Spring.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

ncSpring_t* ncSprings = NULL;

ncSpring_t* CreateSpring(struct ncBody* body1,struct ncBody* body2, float restLength, float k)
{
	// add element to linklist
	ncSpring_t* spring = (ncSpring_t*)malloc(sizeof(ncSpring_t));
	assert(spring);

	memset(spring, 0, sizeof(ncSpring_t));
	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->k = k;


	return spring;
}

void AddSpring(ncSpring_t* spring)
{
	assert(spring);

	spring->prev = NULL;
	spring->next = ncSprings;

	// If the list isn't empty, change previous pointer to current head
	if (ncSprings) {
		ncSprings->prev = spring;
	}

	// Update head to the new spring
	ncSprings = spring;
}

void DestroySpring(ncSpring_t* spring)
{
	assert(spring); // check if pointer is not NULL

	// if next pointer exists 
	if (spring->prev) {
		spring->prev->next = spring->next;//changes to next pointer of previous spring
	}

	// if previous pointer exists 
	if (spring->next) {
		spring->next->prev = spring->prev;//changes to previous pointer of next spring
	}

	// If spring is the head, update
	if (spring == ncSprings)
	{
		ncSprings = spring->next;
	}

	// free memory
	free(spring);
}

void ApplySpringForce(ncSpring_t* springs)
{
	for (ncSpring_t* spring = springs; spring; spring = spring->next)
	{
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position);//<get direction vector from body2 to body1>
			if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction); //<get length from direction>
		float x = length - spring->restLength; // <compute displacement from current length to resting length>;
		float force = -spring->k * x; //<(f = -kx) compute force using product of displacement and stiffness(k)>;

		Vector2 ndirection = Vector2Normalize(direction); //<get direction normal>

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}
}

void ApplyDraggingForce(struct Vector2 position, struct ncBody* dragbody, float restLength, float k, float damping)
{
	Vector2 direction = Vector2Subtract(position, dragbody->position);//<get direction vector from body2 to body1>
	if (direction.x == 0 && direction.y == 0) return;

	float length = Vector2Length(direction); //<get length from direction>
	float x = length - restLength; // <compute displacement from current length to resting length>;
	float force = -k * x; //<(f = -kx) compute force using product of displacement and stiffness(k)>;

	Vector2 ndirection = Vector2Normalize(direction); //<get direction normal>

	float dampingForce = damping * Vector2DotProduct(dragbody->velocity, ndirection);
	float totalForce = force + dampingForce;

	ApplyForce(dragbody, Vector2Scale(ndirection, -totalForce), FM_FORCE);
}
