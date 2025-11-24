#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game_loop.h"
#include "assets.h"
#include <cmath>

int pontuação = 0;

int per_line = 10;

int bloco_h = 30;

int wall_width = 15;

int bloco_w = (SCREEN_WIDTH - (wall_width * 2)) / per_line;

int n_lines = 3;

int start_from = n_lines * bloco_h;

bool starting = true;

int tile_size = 5;
int tile_height = 5;

std::vector<Bloco> blocos;

Bloco placa = {1, SCREEN_WIDTH/2, SCREEN_HEIGHT-bloco_h, 80, bloco_h, true, false, 0, 5};
Vector2 ballPosition = { 0, 0 };

Rectangle hor_src_wall;
Rectangle ver_src_wall;

float speed = 0.0;

float vx = 0.0;
float vy = 0.0;

void start_velocity(){
    speed = 250.0f;
    vx = 0.7f;
    vy = 0.7f;
    float len = pow(vx*vx + vy*vy, 1/2);
    vx = vx/len;
    vy = vy/len;
}

void block_colision(Bloco *bloco){

    if(ballPosition.x + RAIO >= bloco->x && 
       ballPosition.x - RAIO <= bloco->x + bloco->w &&
       ballPosition.y + RAIO >= bloco->y && 
       ballPosition.y - RAIO <= bloco->y + bloco->h){

        if(!bloco->is_wall && !bloco->is_steel){
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
            vx = -fabs(vx);
            ballPosition.x = bloco->x - RAIO;
       }
       else if (touched == overlap_right) {
            vx = fabs(vx);
            ballPosition.x = bloco->x + bloco->w + RAIO;
       }
       else if (touched == overlap_top){
             vy = -fabs(vy);
            ballPosition.y = bloco->y - RAIO;
       }
       else if (touched == overlap_bottom) {
            vy = fabs(vy);
            ballPosition.y = bloco->y + bloco->h + RAIO;
       }

       else {
            vx = -fabs(vx);
            vy = -fabs(vy);
       }

    }

}

float get_difficulty(int difficulty){
    float value = 0.0;

    if(difficulty == 1) value = 0.25f;
    if (difficulty == 2) value = 0.50f;

    return value;
}

Color cor_aleatoria(){
    unsigned char r = rand() % 256;
    unsigned char g = rand() % 256;
    unsigned char b = rand() % 256;

    return {r, g, b, 255};
}

void read_map(const Mapa& matriz){
    int total_lines = matriz.size();

    for(int i=0; i<total_lines; i++){
        for(int j=0; j<per_line; j++){
            int index = matriz[i][j];
            if(index != 0){
                int life = index == 8 or index == 9 ? 2 : 1;
                bool is_steel = index == 8 ? true : false;

                blocos.push_back({
                    life, 
                    wall_width+(j*bloco_w),
                    bloco_h + (i*bloco_h),
                    bloco_w,
                    bloco_h,
                    false,
                    false,
                    index-1,
                    0,
                    is_steel
                });
            }
        }
    }
}

void deallocate_map(){
    placa.x = SCREEN_WIDTH/2;
    placa.y = SCREEN_HEIGHT-bloco_h;
    starting = true;
    std::vector<Bloco>().swap(blocos);
}

void load_map(int level){
    read_map(GetMapa(level));
    init_walls();
}

void init_walls(){
    hor_src_wall = {0, 0, (float)GetAssets()->hor_walls.width, (float)GetAssets()->hor_walls.height};
    ver_src_wall = {0, 0, (float)GetAssets()->ver_walls.width, (float)GetAssets()->ver_walls.height};
    blocos.push_back({1, 0, wall_width, wall_width, SCREEN_HEIGHT-wall_width, true, false, 0, 0, false});
    blocos.push_back({1, SCREEN_WIDTH-wall_width, wall_width, wall_width, SCREEN_HEIGHT-wall_width, true, false, 0, 0, false});
    blocos.push_back({1, 0, 0, SCREEN_WIDTH, wall_width, true, false, 0, 0, false});
}

void draw_blocks(){
    for(Bloco &block : blocos){
        if(!block.is_dead){
            Rectangle dst = { block.x, block.y, block.w, block.h };
            if(!block.is_wall){
                Texture2D asset = Get_BlockText(block.sprite_index);
                Rectangle src = {0, 0, asset.width, asset.height};
                DrawTexturePro(asset, src, dst, {0,0}, 0.0f, WHITE);
            }
            else {
                if(block.y == 0){
                    DrawTexturePro(GetAssets()->ver_walls, ver_src_wall, dst, {0,0}, 0.0f, WHITE);
                }else {
                    DrawTexturePro(GetAssets()->hor_walls, hor_src_wall, dst, {0,0}, 0.0f, WHITE);
                }
            }
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

void game_loop(int &scene, int *difficulty)
{
    float dt = GetFrameTime();              
    if (IsKeyDown(KEY_RIGHT)) placa.x += placa.velocity;
    if (IsKeyDown(KEY_LEFT)) placa.x -= placa.velocity;
    if (IsKeyDown(KEY_ESCAPE)) {
        scene = 2;
        return;
    }

        ballPosition.x += vx * speed * dt;
        ballPosition.y += vy * speed * dt;
        //draw_background();
        DrawTexture(GetAssets()->background, 0, 0, WHITE);

        //sombra das paredes
        DrawRectangleGradientV(
            0, 0, bloco_h, SCREEN_HEIGHT,
            { 0, 0, 0, 100 },   // topo mais opaco
            { 0, 0, 0,   50 }    // base transparente
        );

        //sombra das paredes
        DrawRectangleGradientV(
            bloco_h, 0, SCREEN_WIDTH, bloco_h,
            { 0, 0, 0, 100 },   // topo mais opaco
            { 0, 0, 0, 100}    // base transparente
        );

        DrawCircleV(ballPosition, RAIO, WHITE);
        DrawCircleV(ballPosition, RAIO-2, GREEN);

        Rectangle src = {0, 0, (float)GetAssets()->pad1.width, (float)GetAssets()->pad1.height};
        Rectangle dst = { placa.x, placa.y, placa.w, placa.h };
        DrawTexturePro(GetAssets()->pad1, src, dst, {0,0}, 0.0f, WHITE);
        draw_blocks();

        block_colision(&placa);

        if(IsKeyDown(KEY_SPACE) && starting){
            start_velocity();
            speed += speed * get_difficulty(*difficulty);
            starting = false;
        }

        if(starting){
            ballPosition.x = placa.x +(placa.w/ 2);
            ballPosition.y = placa.y - RAIO;
        }


        if(placa.x+placa.w > SCREEN_WIDTH-wall_width){
            placa.x = (SCREEN_WIDTH-wall_width)-placa.w;
        }

        if(placa.x < wall_width){
            placa.x = wall_width;
        }

}