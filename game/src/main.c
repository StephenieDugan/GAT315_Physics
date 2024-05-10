#include "body.h"
#include "mathf.h"
#include "world.h"
#include "Force.h"
#include "Integrator.h"
#include "render.h"
#include "editor.h"

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>
#include "../raygui-master/src/raygui.h"

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
	InitWindow(1500, 1200, "raylib Physics");
	InitEditor();
	SetTargetFPS(60);



	//initialize world
	ncGravity = (Vector2){ 0, -1 };

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);

		UpdateEditor(position);

		if (IsKeyDown(KEY_W))
		{
			for (int i = 0; i < 1; i++) 
			{
				ncBody* body = CreateBody(ConvertScreenToWorld(position), ncEditorData.MassMinValue, ncEditorData.BodyTypeActive);
				body->damping = ncEditorData.DampingValue;
				body->gravityScale = ncEditorData.GravityScaleValue;
				body->color = ColorFromHSV(GetRandomFloatValue(0, 90), 1, 1);
				Vector2 force = Vector2Scale(GetVector2FromAngle(GetRandomFloatValue(0, 360) * DEG2RAD), GetRandomFloatValue(1000, 2000));
				ApplyForce(body, force, FM_IMPULSE);
				AddBody(body);
			}
		}

		if (!ncEditorIntersect && IsMouseButtonDown(0))
		{
			float angle = GetRandomFloatValue(0, 360);
			for (int i = 0; i < 1; i++) 
			{
				ncBody* body = CreateBody(ConvertScreenToWorld(position), ncEditorData.MassMinValue, ncEditorData.BodyTypeActive);
				body->damping = ncEditorData.DampingValue;
				body->gravityScale = ncEditorData.GravityScaleValue;
				body->color = ColorFromHSV(GetRandomFloatValue(90, 180), 1, 1);

				//Vector2 force = Vector2Scale(GetVector2FromAngle((angle + GetRandomFloatValue(-30, 30)) * DEG2RAD), GetRandomFloatValue(1000, 2000));
				//ApplyForce(body, force, FM_IMPULSE);
			}
		}

		if (IsKeyDown(KEY_S))
		{
			for (int i = 0; i < 100; i++)
			{
				ncBody* body = CreateBody(ConvertScreenToWorld(position), ncEditorData.MassMinValue, ncEditorData.BodyTypeActive);
				body->damping = ncEditorData.DampingValue;
				body->gravityScale = ncEditorData.GravityScaleValue;
				body->color = ColorFromHSV(GetRandomFloatValue(180, 270), 1, 1);

				ApplyForce(body, (Vector2) { GetRandomFloatValue(-100, 100), GetRandomFloatValue(-100, 100) }, FM_IMPULSE);
			}
		}

		//ApplyForce
		ApplyGravitationForce(ncBodies, ncEditorData.GravitationValue);

		//update bodies
		for (ncBody* body = ncBodies; body != NULL; body = body->next)
		{
			Step(body, dt);
		}



		BeginDrawing();
		ClearBackground(BLACK);

		
		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000, fps), 10, 10, 20, WHITE);
		DrawText(TextFormat("FRAME: %.4f ", dt), 10, 30, 20, LIME);

		//if(!ncEditorIntersect) DrawCircle((int)position.x, (int)position.y, 10, RED);
		// draw bodies
		ncBody* body = ncBodies;
		for (ncBody* body = ncBodies; body; body = body->next)
		{
			// Draw body 
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), body->color);
		}
		DrawEditor(position);


		EndDrawing();
	}

	while (ncBodies) {
		DestroyBody(ncBodies);
	}

	CloseWindow();

	return 0;
}


