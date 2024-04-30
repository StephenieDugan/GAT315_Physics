#include <stdlib.h>
#include <assert.h>
#include <world.h>
#include <assert.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* CreateBody() {
    // make space for body
    Body* newBody = (Body*)malloc(sizeof(Body));
    assert(newBody != NULL);

    newBody->prev = NULL;
    newBody->next = bodies;

    // If the list isn't empty, change previous pointer to current head
    if (bodies != NULL) {
        bodies->prev = newBody;
    }

    // Update head to the new body
    bodies = newBody;

    bodyCount++;

    return newBody;
}

void DestroyBody(Body* body) {
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
    if (body == bodies) {
        bodies = body->next;
    }

    bodyCount--;

    // free memory
    free(body);
}

