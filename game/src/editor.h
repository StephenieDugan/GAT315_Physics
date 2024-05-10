#pragma once
#include "raylib.h"

typedef struct ncEditorData
{
	Vector2 anchor01;

	bool EditorBoxActive;
	float MassMinValue;
	float MassMaxValue;
	float GravitationValue;
	bool BodyTypeEditMode;
	int BodyTypeActive;
	float DampingValue;
	float GravityScaleValue;

} ncEditorData_t;

extern ncEditorData_t ncEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor(Vector2 position);