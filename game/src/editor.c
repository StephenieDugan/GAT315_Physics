#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

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
	ncEditorData.MassMinValue = 0.1f;
	ncEditorData.MassMaxValue = 1;
	ncEditorData.GravitationValue = 2;
	ncEditorData.BodyTypeEditMode = false;
	ncEditorData.BodyTypeActive = 0;
	ncEditorData.DampingValue = 1;
	ncEditorData.GravityScaleValue = 1;

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
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 80, 120, 16 }, "Mass Min", NULL, & ncEditorData.MassMinValue, 0, 10);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 120, 120, 16 }, "Mass Max", NULL, & ncEditorData.MassMaxValue, 0, 10);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 160, 120, 16 }, "Gravity Scale", NULL, & ncEditorData.GravityScaleValue, 0, 100);
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 200, 120, 16 }, "Damping", NULL, & ncEditorData.DampingValue, 0, 10);
		GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 20, ncEditorData.anchor01.y + 40, 256, 192 }, "Body");
		GuiSliderBar((Rectangle) { ncEditorData.anchor01.x + 100, ncEditorData.anchor01.y + 260, 120, 16 }, "Gravitation", NULL, & ncEditorData.GravitationValue, 0, 100);
		GuiGroupBox((Rectangle) { ncEditorData.anchor01.x + 20, ncEditorData.anchor01.y + 248, 256, 144 }, "World");
		if (GuiDropdownBox((Rectangle) { ncEditorData.anchor01.x + 80, ncEditorData.anchor01.y + 40, 120, 24 }, "STATIC;KINEMATIC;DYNAMIC", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
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