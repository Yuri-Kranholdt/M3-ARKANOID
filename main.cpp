#include "raylib.h"
#include "config.h"
#include "game_loop.h"
#include "game_over.h"
#include "pause.h"
#include "assets.h"
#include "menu.h"
#include <cstdlib>
#include <ctime>

int nivel = 0;

int difficulty = 0;

int high_score = 0;

int score = 0;

int main(void)
{
    int scene = 1;
    bool exit = false;

    InitWindow(REAL_WIDTH, SCREEN_HEIGHT, "Arkanoid M3");

    LoadAssets();
    init_blockTexures();
    init_powerTextures();

    srand(static_cast<unsigned int>(time(0)));
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !exit)    // Detect window close button or ESC key
    {
        
        BeginDrawing();
        if(!scene){
            game_loop(scene, &difficulty, &high_score, &nivel);
        }
        else if(scene == 1){
            menu_loop(&scene, &nivel, &difficulty, &score, &exit);
        }
        else if(scene == 2){
            pause_loop(&scene, &score, &high_score);
        }
        else if(scene == 5){
            game_over_loop(&scene, &score, &high_score);
        }
        EndDrawing();
    }
    UnloadAssets();
    UnloadBlocks();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}