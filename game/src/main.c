#include "raylib.h"
#include <world.h>

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
	InitWindow(800, 450, "raylib Physics");
	while (!WindowShouldClose())
	{
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            CreateBody();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Update / draw bodies
        Body* body = bodies;
        while (body) // do while we have a valid pointer, will be NULL at the end of the list
        {
           /*
            body->position.x = GetMouseX();
            body->position.y = GetMouseY();
           */ // Update body position (Mouse)

             // position random
              body->position.x = GetRandomValue(1,800);
            body->position.y = GetRandomValue(1,450);
            

            // Draw body (For now, draw a circle at body position)
            DrawCircle(body->position.x, body->position.y, 20, BLUE);

            body = body->next; // Move to the next body
        }

        EndDrawing();
    }

    while (bodies) {
        DestroyBody(bodies);
    }

	CloseWindow();

	return 0;
}


