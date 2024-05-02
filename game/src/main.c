#include "raylib.h"
#include "raymath.h"
#include <world.h>
#include <stdlib.h>
#include <assert.h>
#include "Integrator.h"
#include "body.h"
#include "mathf.h"


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
	InitWindow(800, 450, "raylib Physics");
	SetTargetFPS(60);


	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();


		if (IsMouseButtonDown(0))
		{
			ncBody* body = CreateBody();
			body->position = position;
			body->mass = GetRandomValue(1, 10);
		
		}

		//ApplyForce
		ncBody* body = ncBodies;
		while (body) 
		{
			ApplyForce(body, CreateVector2(0, -50));

			body = body->next; // Move to the next body
		}

		//update bodies
		body = ncBodies;
		while (body) 
		{
			ExplicitEuler(body, dt);
			ClearForce(body);

			body = body->next; // Move to the next body
		}


		BeginDrawing();
		ClearBackground(BLACK);
		DrawCircle((int)position.x, (int)position.y, 20, RED);
		// draw bodies
		body = ncBodies;
		while (body) 
		{
			// Draw body 
			DrawCircle(body->position.x, body->position.y, body->mass, BLUE);

			body = body->next; // Move to the next body
		}

		EndDrawing();
	}

	while (ncBodies) {
		DestroyBody(ncBodies);
	}

	CloseWindow();

	return 0;
}


