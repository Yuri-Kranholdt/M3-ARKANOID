//#include "raylib.h"
//#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "map.h"
//#include "config.h"
#include "game_loop.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

//int screenWidth = 800;
//int screenHeight = 450;


int per_line = 10;

int bloco_h = 30;

int wall_width = bloco_h;

int bloco_w = (SCREEN_WIDTH - (wall_width * 2)) / per_line;

int n_lines = 3;

int start_from = n_lines * bloco_h;

bool starting = true;

int tile_size = 5;
int tile_height = 5;

std::vector<Bloco> blocos;

Bloco placa = {1, SCREEN_WIDTH/2, SCREEN_HEIGHT-20, 80, 20, true, false, MAROON, 5};
Vector2 ballPosition = { 0, 0 };


int vx = 0;
int vy = 0;

void block_colision(Bloco *bloco){

    if(ballPosition.x + RAIO >= bloco->x && 
       ballPosition.x - RAIO <= bloco->x + bloco->w &&
       ballPosition.y + RAIO >= bloco->y && 
       ballPosition.y - RAIO <= bloco->y + bloco->h){

        if(!bloco->is_wall){
            if(bloco->vida - 1 <= 0){
                bloco->is_dead = true;
            }
            else {
                bloco->vida--;
            }
        }
       
       int overlap_left = (ballPosition.x + RAIO) - bloco->x;
       int overlap_right = (bloco->x + bloco->w) - (ballPosition.x - RAIO);
       int overlap_top = (ballPosition.y + RAIO) - bloco->y;
       int overlap_bottom = (bloco->y + bloco->h) - (ballPosition.y - RAIO);

       int touched = std::min({overlap_left, overlap_right, overlap_top, overlap_bottom});

       if(touched == overlap_left){
            vx = -vx;
            ballPosition.x = bloco->x - RAIO;
       }
       else if (touched == overlap_right) {
            vx = abs(vx);
            ballPosition.x = bloco->x + bloco->w + RAIO;
       }
       else if (touched == overlap_top){
             vy = -vy;
            ballPosition.y = bloco->y - RAIO;
       }
       else if (touched == overlap_bottom) {
            vy = abs(vy);
            ballPosition.y = bloco->y + bloco->h + RAIO;
       }

       else {
            vx = -vx;
            vy = -vy;
       }

    }

}

Color cor_aleatoria(){
    unsigned char r = rand() % 256;
    unsigned char g = rand() % 256;
    unsigned char b = rand() % 256;

    return {r, g, b, 255};
}

void read_map(const Mapa& matriz){
    int total_lines = (SCREEN_HEIGHT-(bloco_h*2))/bloco_h;

    for(int i=0; i<total_lines; i++){
        for(int j=0; j<per_line; j++){
            int index = matriz[i][j];
            if(index != 0){
                Color cor = cores[index-1];
                int life = index == 8 or index == 9 ? 2 : 1;
                bool is_wall = index == 8 ? true : false;

                blocos.push_back({
                    life, 
                    wall_width+(j*bloco_w),
                    bloco_h + (i*bloco_h),
                    bloco_w,
                    bloco_h,
                    is_wall,
                    false,
                    cor,
                    0
                });
            }
        }
    }
}

void init_walls(){
    blocos.push_back({1, 0, bloco_h, wall_width, SCREEN_HEIGHT-bloco_h, true, false, Color{137, 137, 137, 255}, 0});
    blocos.push_back({1, SCREEN_WIDTH-wall_width, bloco_h, wall_width, SCREEN_HEIGHT-bloco_h, true, false, Color{137, 137, 137, 255}, 0});
    blocos.push_back({1, 0, 0, SCREEN_WIDTH, bloco_h, true, false, Color{137, 137, 137, 255}, 0});
}

void draw_blocks(){
    for(Bloco &block : blocos){
        if(!block.is_dead){
            DrawRectangle(block.x, block.y, block.w, block.h, block.color);
            if(!block.is_wall) DrawRectangleLinesEx((Rectangle){block.x, block.y, block.w, block.h}, 1.5, BLACK);
            block_colision(&block);
        }
    }
}

void draw_background(){
    for(int i=0; i<SCREEN_HEIGHT/tile_height;i++){
        for(int j=0; j<SCREEN_WIDTH/tile_size; j++){
            Color color = (i+j)%2==0 ? Color{0, 0, 255, 255} : BLACK;
            DrawRectangle(j*tile_size, i*tile_height, tile_size, tile_height, color);
        }
    }
}

void game_loop(int &scene, int* level)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    //init_walls();

    //read_map(GetMapa(2));              
    if (IsKeyDown(KEY_RIGHT)) placa.x += placa.velocity;
    if (IsKeyDown(KEY_LEFT)) placa.x -= placa.velocity;
    if (IsKeyDown(KEY_ESCAPE)) {
        scene = 2;
        return;
    }
        draw_background();

        DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

        DrawCircleV(ballPosition, RAIO, MAROON);
        DrawRectangle(placa.x, placa.y, placa.w, placa.h, MAROON);
        draw_blocks();

        if(ballPosition.y <= 0 || ballPosition.y >= SCREEN_HEIGHT){
            vy = -vy;
        }

        block_colision(&placa);

        if(IsKeyDown(KEY_SPACE) && starting){
            vy = 4;
            vx = 1;
            starting = false;
        }

        if(starting){
            ballPosition.x = placa.x +(placa.w/ 2);
            ballPosition.y = placa.y - RAIO;
        }


        if(placa.x+placa.w >= SCREEN_WIDTH-wall_width){
            placa.x = (SCREEN_WIDTH-wall_width)-placa.w;
        }

        if(placa.x <= wall_width){
            placa.x = wall_width;
        }

        if(ballPosition.x <= 0 || ballPosition.x >= SCREEN_WIDTH){
            vx = -vx;
        }

        ballPosition.x += vx;
        ballPosition.y += vy;

}