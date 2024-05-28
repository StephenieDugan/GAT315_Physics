#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "world.h"
#include "body.h"

ncBody* ncBodies = NULL;
int ncBodyCount = 0;

ncBody* CreateBody(Vector2 position, float mass, ncBodyType bodytype)
{
	// add element to linklist
	ncBody* body = (ncBody*)malloc(sizeof(ncBody));
	assert(body != NULL);

	memset(body, 0, sizeof(ncBody));
	body->position = position;
	body->mass = mass;
	body->inverseMass = (bodytype == BT_DYNAMIC) ? 1 / mass : 0;
	body->type = bodytype;


	return body;
}

void AddBody(ncBody* body)
{
	assert(body);

	body->prev = NULL;
	body->next = ncBodies;

	// If the list isn't empty, change previous pointer to current head
	if (ncBodies != NULL) {
		ncBodies->prev = body;
	}

	// Update head to the new body
	ncBodies = body;

	ncBodyCount++;

}

void DestroyBody(ncBody* body) {
	assert(body != NULL); // check if pointer is not NULL

	// if next pointer exists 
	if (body->prev != NULL) {
		body->prev->next = body->next;//changes to next pointer of previous body
	}

	// if previous pointer exists 
	if (body->next != NULL) {
		body->next->prev = body->prev;//changes to previous pointer of next body
	}

	// If body is the head, update
	if (body == ncBodies)
	{
		ncBodies = body->next;
	}

	ncBodyCount--;

	// free memory
	free(body);
}
/*
void DestroyAllBodies()
{
	if (!*ncBodies) return;

	ncBodies* body = *bodies;

	while (body)
	{
		ncBodies* next = body->next;
		free(body);
		body = next;
	}
	*bodies = NULL;
}

*/