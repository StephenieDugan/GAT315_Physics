/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    Vector2 anchor01 = { 832, 72 };
    Vector2 anchor02 = { 832, 112 };
    Vector2 anchor03 = { 832, 320 };
    Vector2 anchor04 = { 928, 200 };
    
    bool EditorBoxActive = true;
    float MassMinValue = 0.0f;
    float MassMaxValue = 0.0f;
    float GravityScaleValue = 0.0f;
    float DampingValue = 0.0f;
    float GravitationValue = 0.0f;
    bool BodyTypeEditMode = false;
    int BodyTypeActive = 0;
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (BodyTypeEditMode) GuiLock();

            if (EditorBoxActive)
            {
                EditorBoxActive = !GuiWindowBox((Rectangle){ 800, 104, 320, 504 }, "Editor");
            }
            GuiSliderBar((Rectangle){ anchor01.x + 96, anchor01.y + 96, 120, 16 }, "Mass Min", NULL, &MassMinValue, 0, 100);
            GuiSliderBar((Rectangle){ anchor01.x + 96, anchor01.y + 128, 120, 16 }, "Mass Max", NULL, &MassMaxValue, 0, 100);
            GuiSliderBar((Rectangle){ anchor01.x + 96, anchor01.y + 160, 120, 16 }, "Gravity Scale", NULL, &GravityScaleValue, 0, 100);
            GuiGroupBox((Rectangle){ anchor01.x + 0, anchor01.y + 40, 256, 192 }, "Body");
            GuiSliderBar((Rectangle){ anchor01.x + 96, anchor01.y + 192, 120, 16 }, "Damping", NULL, &DampingValue, 0, 100);
            GuiGroupBox((Rectangle){ anchor01.x + 0, anchor01.y + 248, 256, 144 }, "SAMPLE TEXT");
            GuiSliderBar((Rectangle){ anchor01.x + 96, anchor01.y + 272, 120, 16 }, "Gravitation", NULL, &GravitationValue, 0, 100);
            if (GuiDropdownBox((Rectangle){ anchor01.x + 72, anchor01.y + 56, 120, 24 }, "STATIC;KINEMATIC;DYNAMIC", &BodyTypeActive, BodyTypeEditMode)) BodyTypeEditMode = !BodyTypeEditMode;
            
            GuiUnlock();
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

