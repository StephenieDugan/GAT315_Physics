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
#include "../../raygui/src/raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    Vector2 anchor01 = { 776, 56 };
    
    bool EditorBoxActive = true;
    float MassMinValue = 0.0f;
    float MassMaxValue = 0.0f;
    float GravitationValue = 0.0f;
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

        UpdateEditor(position);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (EditorBoxActive)
            {
                EditorBoxActive = !GuiWindowBox((Rectangle){ ncEditorData.anchor01.x + 0, anchor01.y + 0, 304, 616 }, "Editor");
                GuiSliderBar((Rectangle){ anchor01.x + 80, anchor01.y + 80, 120, 16 }, "Mass Min", NULL, &MassMinValue, 0, 100);
                GuiSliderBar((Rectangle){ anchor01.x + 80, anchor01.y + 120, 120, 16 }, "Mass Max", NULL, &MassMaxValue, 0, 100);
                GuiSliderBar((Rectangle){ anchor01.x + 80, anchor01.y + 168, 120, 16 }, "Gravitation", NULL, &GravitationValue, 0, 100);
            }
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

