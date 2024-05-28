#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"
#define EDITOR_DATA(data) TextFormat("%0.2f", data), &data
bool ncEditorActive = true;
bool ncEditorIntersect = false;
ncEditorData_t ncEditorData;

Rectangle editorRect;

Texture2D cursorTexture;

void InitEditor()
{
	GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");
	Image image = LoadImage("resources/reticle.png");
	cursorTexture = LoadTextureFromImage(image);
	cursorTexture.height = 50;
	cursorTexture.width = 50;
	UnloadImage(image);
	HideCursor();

	ncEditorData.anchor01 = (Vector2){ 950,50 };

	ncEditorData.EditorBoxActive = true;
	ncEditorData.SimulateToggleActive = true;
	ncEditorData.BodyTypeEditMode = false;
	ncEditorData.BodyTypeActive = 0;
	ncEditorData.MassValue = 0.1f;
	ncEditorData.DampingValue = 1;
	ncEditorData.GravityScaleValue = 1;
	ncEditorData.GravityValue = -1;
	ncEditorData.StiffnessValue = 20;
	ncEditorData.RestitutionValue = 0.3f;

	ncEditorData.GravitationValue = 2;
	ncEditorData.TimeStepValue = 60;
	ncEditorData.FixedTimeStep = 1.0f/ncEditorData.TimeStepValue;

	editorRect = (Rectangle){ ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 304, 616 };
}

void UpdateEditor(Vector2 position)
{
	if (IsKeyPressed(KEY_TAB)) ncEditorData.EditorBoxActive = !ncEditorData.EditorBoxActive;

	ncEditorIntersect = ncEditorData.EditorBoxActive && CheckCollisionPointRec(position, editorRect);
}

void DrawEditor(Vector2 position)
{
	if (ncEditorData.BodyTypeEditMode) GuiLock();
	if (ncEditorData.EditorBoxActive)
	{
		ncEditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 304, 616 }, "Editor");
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 90, 120, 16 }, "Mass", EDITOR_DATA(ncEditorData.MassValue), 0, 10);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 120, 120, 16 }, "Damping", EDITOR_DATA(ncEditorData.DampingValue), 0, 10);
		//GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 120, 120, 16 }, "Mass Max", NULL, & ncEditorData.MassMaxValue, 0, 10);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 150, 120, 16 }, "Gravity Scale", EDITOR_DATA(ncEditorData.GravityScaleValue), 0, 100);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 180, 120, 16 }, "Stiffness (k)", EDITOR_DATA(ncEditorData.StiffnessValue), 0, 30);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 210, 120, 16 }, "Restitution", EDITOR_DATA(ncEditorData.RestitutionValue), 0, 1);
		if (GuiDropdownBox((Rectangle) { ncEditorData.anchor01.x + 80, ncEditorData.anchor01.y + 50, 120, 24 }, "STATIC;KINEMATIC;DYNAMIC", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
		GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 20, ncEditorData.anchor01.y + 40, 256, 220 }, "Body");
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 300, 120, 16 }, "Gravity", EDITOR_DATA(ncEditorData.GravityValue), -1, 0);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 330, 120, 16 }, "Gravitation", EDITOR_DATA(ncEditorData.GravitationValue), 0, 10);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 360, 120, 16 }, "Time Step", EDITOR_DATA(ncEditorData.TimeStepValue), 20, 120);
		GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 20, ncEditorData.anchor01.y + 280, 256, 144 }, "World");
		GuiToggle((Rectangle) { ncEditorData.anchor01.x + 180, ncEditorData.anchor01.y + 550, 88, 24 }, "Simulate", & ncEditorData.SimulateToggleActive);
		ncEditorData.ClearButtonPressed = GuiButton((Rectangle) { ncEditorData.anchor01.x + 32, ncEditorData.anchor01.y + 550, 120, 24 }, "Clear Screen");
	}

	DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, WHITE);

	GuiUnlock();
}

ncBody* GetBodyIntersect(ncBody* bodies, Vector2 position)
{
	for (ncBody* body = bodies; body; body = body->next)
	{
		Vector2 screen = ConvertWorldToScreen(body->position);
		if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass)))
		{
			return body;
		}
	}

	return NULL;
}

void DrawLineBodyToPosition(ncBody* body, Vector2 position)
{
	Vector2 screen = ConvertWorldToScreen(body->position);
	DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}