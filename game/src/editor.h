#pragma once
#include "raylib.h"

typedef struct ncEditorData
{
	Vector2 anchor01;

	bool EditorBoxActive;
	float MassValue;
	float DampingValue;
	float GravityScaleValue;
	float StiffnessValue;
	float RestitutionValue;
	float GravityValue;
	float GravitationValue;
	float TimeStepValue;
	float FixedTimeStep;
	bool BodyTypeEditMode;
	int BodyTypeActive;
	bool SimulateToggleActive;
	bool ClearButtonPressed;

} ncEditorData_t;

extern ncEditorData_t ncEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor(Vector2 position);

struct ncBody* GetBodyIntersect(struct ncBody* bodies, Vector2 position); 
void DrawLineBodyToPosition(struct ncBody* body, Vector2 position);