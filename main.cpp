#include "raylib.h"
#include "config.h"
#include "game_loop.h"
#include "pause.h"
#include "assets.h"
#include "menu.h"
#include <cstdlib>
#include <ctime>

int nivel = 0;

int difficulty = 0;

int main(void)
{
    int scene = 1;

    init_walls();

    //read_map(GetMapa(nivel));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - input keys");

    LoadAssets();
    init_blockTexures();

    srand(static_cast<unsigned int>(time(0)));
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        BeginDrawing();
        if(!scene){
            game_loop(scene, &difficulty);
        }
        else if(scene == 1){
            menu_loop(&scene, &nivel, &difficulty);
        }
        else if(scene == 2){
            pause_loop(&scene);
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