#include "raylib.h"
#include "config.h"
#include "game_loop.h"
#include "rank_screen.h"
#include "game_over.h"
#include "pause.h"
#include "assets.h"
#include "menu.h"
#include <cstdlib>
#include <ctime>
#include "ranking.h"

int nivel = 0;

int difficulty = 0;

int high_score = 50000;

int score = 0;

int main(void)
{
    int scene = 1;
    bool exit = false;

    InitWindow(REAL_WIDTH, SCREEN_HEIGHT, "Arkanoid M3");

    LoadAssets();
    init_blockTexures();
    init_powerTextures();
    start_table();

    srand(static_cast<unsigned int>(time(0)));
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !exit)    // Detect window close button or ESC key
    {
        std::cout << "score ->" << score << std::endl;
        
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
        else if (scene == 6){
            rank_loop(&scene);
        }
        else if(scene == 7){
            get_player_name(&scene);
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