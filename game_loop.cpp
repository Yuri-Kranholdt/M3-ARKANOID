#include "game_loop.h"
#include "boss.h"
#include "ranking.h"

//int pontuação = 0;

int vida = 3;

int *pontuação;

int per_line = 10;

int bloco_h = 30;

int wall_width = 15;

int bloco_w = (SCREEN_WIDTH - (wall_width * 2)) / per_line;

int n_lines = 3;

int start_from = n_lines * bloco_h;

bool starting = true;

int tile_size = 5;
int tile_height = 5;

int power_up_velocity = 3;

float multiplicador = 1.0;

int pad_width = 80;

int expand_counter = 0;
int pad_vel = 5;

int blocks_dead_num;

std::vector<Bloco> blocos;
std::vector<Power_Up> powers;

Bloco placa = {3, SCREEN_WIDTH/2, SCREEN_HEIGHT-bloco_h, pad_width, bloco_h, true, false, 0, pad_vel};
Vector2 ballPosition = { 0, 0 };

Rectangle hor_src_wall;
Rectangle ver_src_wall;

bool laser = false;
float laser_w = 4;
float laser_h = 8;
Rectangle laser1 = {0, 0, laser_w, laser_h};
Rectangle laser2 = {0, 0, laser_w, laser_h};

float speed = 0.0;

float vx = 0.0;
float vy = 0.0;

bool start_boss = false;

void laser_update(Rectangle *laser, int new_x){
    int height = placa.y - laser->height;
    DrawRectangleRec(*laser, YELLOW);
    laser->y -= 7;
    for(Bloco &block : blocos){

        if(block.is_dead) continue;

        Rectangle block_rect = {block.x, block.y, block.w, block.h};
        if(CheckCollisionRecs(block_rect, *laser)){
            laser->y = height;
            laser->x = new_x;
            update_block(&block);
        }

    }
    // desenhar o laser
}

void start_velocity(){
    speed = 250.0f;
    vx = 0.7f;
    vy = 0.7f;
    float len = pow(vx*vx + vy*vy, 1/2);
    vx = vx/len;
    vy = vy/len;
}

void gen_power(Bloco *bloco){
    int gerar_ou_nao = rand() % 2;
    if(gerar_ou_nao){
        int index = rand() % 4;
        int power_size = bloco->w/2;
        int power_height = bloco->h/2;
        int power_x = bloco->x + (power_size/2);
        int power_y = bloco->y + power_height;
        powers.push_back({power_x, power_y, power_size, power_height, index});
    }

}

void update_block(Bloco *bloco){
    if(!bloco->is_wall && !bloco->is_steel){
        if(bloco->vida - 1 <= 0){
            bloco->is_dead = true;
            blocks_dead_num += 1;
            *pontuação += Get_BlockAttr(bloco->sprite_index).points * multiplicador;
            gen_power(bloco);
        }
        else {
            bloco->vida--;
        }
    }
}

bool block_colision(Bloco *bloco){

    if(ballPosition.x + RAIO >= bloco->x && 
       ballPosition.x - RAIO <= bloco->x + bloco->w &&
       ballPosition.y + RAIO >= bloco->y && 
       ballPosition.y - RAIO <= bloco->y + bloco->h){

       update_block(bloco);
       
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

       return true;
    }

    return false;
}

float get_difficulty(int difficulty){
    float value = 0.0;

    if(difficulty == 1) value = 0.25f;
    if (difficulty == 2) value = 0.50f;

    return value;
}

void read_map(const Mapa& matriz){
    int total_lines = matriz.size();

    for(int i=0; i<total_lines; i++){
        for(int j=0; j<per_line; j++){
            int index = matriz[i][j];
            if(index != 0){
                int life = index == 8 || index == 9 ? 4 : 1;

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
                    false
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
    std::vector<Power_Up>().swap(powers);
    *pontuação = 0;
}

void load_map(int level, int *score,  bool spawn_boss){
    if(!spawn_boss){
        read_map(GetMapa(level));
    } else {
        init_boss();
    }
    pontuação = score;
    placa.vida = 3;
    blocks_dead_num = 0;
    //reset_power_ups();
    init_walls();
    start_boss = spawn_boss;
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

void interpret_power(Power_Up *power){
    int index = power->pow_index+1;
    int max_expand = 4;

     switch (index) {
        case 1:
            if(placa.velocity < pad_vel*2) placa.velocity += 1;
            break;
        case 2:
            if(expand_counter <= max_expand) placa.w += 10;
            expand_counter += 1;
            break;
        case 3:
            placa.vida += 1;
            break;
        case 4:
            laser = true;
            multiplicador += 0.5;
            break;
        default:
            break;
    }
}

void draw_power_ups(){
    for(Power_Up &power : powers){
        Texture2D *tex = Get_Power(power.pow_index);
        Rectangle dst = {power.x, power.y, power.w, power.h};
        Rectangle src = {0, 0, tex->width, tex->height};
        DrawTexturePro(*tex, src, dst, {0,0}, 0.0f, WHITE);
        power.y += power_up_velocity;
    }
}

void reset_power_ups(){
    //starting = true;
    placa.velocity = pad_vel;
    expand_counter = 0;
    placa.w = pad_width;
    multiplicador = 1;
    laser = false;
}

void power_update(){
    for (size_t i = 0; i < powers.size(); i++) {
        Power_Up power = powers[i];
        Rectangle power_convert = {power.x, power.y, power.w, power.h};
        Rectangle placa_convert = {placa.x, placa.y, placa.w, placa.h};

        if(power.y >= SCREEN_HEIGHT){
            powers.erase(powers.begin() + i);
        }

        if(CheckCollisionRecs(placa_convert, power_convert)){
            powers.erase(powers.begin() + i);
            interpret_power(&power);
        }
    }
}

void game_loop(int &scene, int *difficulty, int *high_score, int* level)
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

        if(start_boss) {
            boss_collision();
            boss();
        }

        draw_blocks();
        draw_power_ups();
        power_update();

        block_colision(&placa);

        // ir para tela de game over
        if(placa.vida <= 0){
            scene = 5;
            return;
        }

        // trocar de level ao vencer
        // -3 para desconsiderar os 3 muros
        //blocos.size()-3 && 
        if(blocos.size()-3 && blocks_dead_num == (int)blocos.size()-3){
            if(*level+1 <= MAPAS.size()-1){
                reset_power_ups();
                int temp = *pontuação;
                deallocate_map();
                *pontuação = temp;
                *level += 1;
                load_map(*level, pontuação);
            }
            else{
                // voltar ao menu se tiver vencido o level final
                scene = 1;
                // verificar se deve ir primeiro para tela de cadastro de pontos
                set_points(*pontuação);
                if(is_in_ranking()){
                    scene = 7;
                }
                deallocate_map();
            }
            
        }

        if(laser){
            laser_update(&laser1, placa.x);
            laser_update(&laser2, (placa.x+placa.w)-laser2.width);
        }

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

        // saiu da tela por baixo
        if(ballPosition.y >= SCREEN_HEIGHT){
            starting = true;
            reset_power_ups();
            placa.vida -= 1;
        }

        DrawTextCenter("ARKANOID", 30, SCREEN_HEIGHT/6, RED, REAL_WIDTH, SCREEN_WIDTH);

        DrawTextCenter("HIGH SCORE", 20, SCREEN_HEIGHT/3, RED, REAL_WIDTH, SCREEN_WIDTH);

        DrawTextCenter(std::to_string(*high_score).c_str(), 20, (SCREEN_HEIGHT/3)+20, WHITE, REAL_WIDTH, SCREEN_WIDTH);


        DrawTextCenter("SCORE", 20, SCREEN_HEIGHT/2, RED, REAL_WIDTH, SCREEN_WIDTH);

        DrawTextCenter(std::to_string(*pontuação).c_str(), 20, (SCREEN_HEIGHT/2)+20, WHITE, REAL_WIDTH, SCREEN_WIDTH);


        DrawTextCenter("VIDAS", 20, SCREEN_HEIGHT/1.5, RED, REAL_WIDTH, SCREEN_WIDTH);

        DrawTextCenter(std::to_string(placa.vida).c_str(), 20, (SCREEN_HEIGHT/1.5)+20, WHITE, REAL_WIDTH, SCREEN_WIDTH);

        ClearBackground(BLACK);
}