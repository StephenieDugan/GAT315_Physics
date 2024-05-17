#include "body.h"
#include "mathf.h"
#include "world.h"
#include "Force.h"
#include "Integrator.h"
#include "render.h"
#include "editor.h"
#include "Spring.h"
#include "contact.h"
#include "collision.h"

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

	ncBody* selectedBody = NULL;
	ncBody* connectBody = NULL;
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

		selectedBody = GetBodyIntersect(ncBodies, position);
		if (selectedBody)
		{
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines(screen.x, screen.y, ConvertWorldToPixel(selectedBody->mass) + 5, YELLOW);
		}
		//create bodies
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
		
		if (!ncEditorIntersect && IsMouseButtonDown(0) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL)))
		{
			float angle = GetRandomFloatValue(0, 360);
			for (int i = 0; i < 1; i++) 
			{
				ncBody* body = CreateBody(ConvertScreenToWorld(position), ncEditorData.MassMinValue, ncEditorData.BodyTypeActive);
				body->damping = ncEditorData.DampingValue;
				body->gravityScale = ncEditorData.GravityScaleValue;
				body->color = ColorFromHSV(GetRandomFloatValue(90, 180), 1, 1);
				body->restitution = 0.3f;

				Vector2 force = Vector2Scale(GetVector2FromAngle((angle + GetRandomFloatValue(-30, 30)) * DEG2RAD), GetRandomFloatValue(1000, 2000));
				ApplyForce(body, force, FM_FORCE);
				AddBody(body);
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

		//connect spring
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody)
		{
			connectBody = selectedBody;
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody)
		{
			DrawLineBodyToPosition(connectBody, position);
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody)
		{
			if (selectedBody && selectedBody != connectBody)
			{
				ncSpring_t* spring = CreateSpring(connectBody, selectedBody,Vector2Distance(connectBody->position,selectedBody->position), 20);
				AddSpring(spring);
			}
		}
		//ApplyForce
		ApplyGravitationForce(ncBodies, ncEditorData.GravitationValue);
		ApplySpringForce(ncSprings);

		//update bodies
		for (ncBody* body = ncBodies; body != NULL; body = body->next)
		{
			Step(body, dt);
		}

		//collision
		ncContact_t* contacts = NULL;
		CreateContacts(ncBodies, &contacts);
		SeparateContacts(contacts);
		//ResolveContacts(contacts);

		BeginDrawing();
		ClearBackground(BLACK);

		
		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000, fps), 10, 10, 20, WHITE);
		DrawText(TextFormat("FRAME: %.4f ", dt), 10, 30, 20, LIME);

		//if(!ncEditorIntersect) DrawCircle((int)position.x, (int)position.y, 10, RED);
		// draw bodies
		//ncBody* body = ncBodies;
		for (ncBody* body = ncBodies; body; body = body->next)
		{
			// Draw body 
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), body->color);
		}
		// draw springs
		//ncSpring_t* spring = ncSprings;
		for (ncSpring_t* spring = ncSprings; spring; spring = spring->next)
		{
			// Draw body 
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine((int)screen1.x, (int)screen1.y, (int)screen2.x, (int)screen2.y, YELLOW);
		}
		// draw contacts 
		for (ncContact_t* contact = contacts; contact; contact = contact->next)
		{
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircle(screen.x, screen.y, ConvertWorldToPixel(contact->body1->mass * 1.0f), RED);
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


