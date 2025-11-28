#include <vector>
#include <iostream>
#include "config.h"
#include "game_loop.h"
#include <cmath>
#include "boss.h"


bool voltando;
float angle;
float wave;
float v;
std::deque<Vector2> pos;
float raio;
int boss_vida;
bool is_dead;
float wave_h;
float amp;

// f(x) = a + b * sin(c*x + d)
// a -> deslocamento vertical
// b -> freq
// c -> deslocamento horizontal

float rad(float degree){
    return (PI * degree) / 180;
}

float distance(Vector2 a, Vector2 b){
    // só desenha a bola se a distância da proxima bola for igual ao diametro
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void start_balls(){
    // 6 bolas
    pos.clear();
    for(int i=7; i>0; i--){
        pos.push_front({(raio * 2)*i, SCREEN_HEIGHT/2});
    }
}

void init_boss(){

    start_balls();
    voltando = false;
    angle = 0;
    wave = 0;
    v = 60;
    raio = 20;
    boss_vida = 40;
    is_dead = false;
    wave_h = 4.0;
    amp = 10;
}

void decrement_life(){
    if(boss_vida - 2 <= 0){
        is_dead = true;
        return;
    }
    boss_vida -= 2;

    if(wave_h > 2.0){
        wave_h -= 0.5;
    }

    if(boss_vida < 15){
        if(amp > 4.0){
            amp -= 2.0;
        }

        if(fabs(v) < 100){
            v += v > 0 ? 10 : -10;
        }
    }
}

void draw_balls(){
    for (size_t i = 0; i < pos.size(); ++i){
        int new_r = raio/4;
        Vector2 shadow = {pos[i].x+new_r, pos[i].y+new_r};
        DrawCircleV(shadow, raio, { 0, 0, 0, 180 });

        Rectangle src = {0, 0, (float)GetAssets()->Ball.width, (float)GetAssets()->Ball.height};
        Rectangle dst = { pos[i].x-raio, pos[i].y-raio, raio*2, raio*2 };
        DrawTexturePro(GetAssets()->Ball, src, dst, {0,0}, 0.0f, WHITE);
        //DrawCircleV(pos[i], raio, RED);
    }
}

void update_boss(){
    angle += v * 0.10;

    float rad_ang = rad(angle);

    if(!voltando){
        wave = sin(1.2 * rad_ang);
    }
    else{
        // se estiver voltando coloca a onda de cabeça para baixo
        wave = -sin(1.2 * rad_ang);
    }

    if(angle >= SCREEN_WIDTH-25){
        v = -v;
        voltando = true;
    }

    if(angle < 0){
        v = fabs(v);
        voltando = false;
    }

    float new_y = (SCREEN_HEIGHT / wave_h) + ((SCREEN_HEIGHT / amp) * wave);
    float new_x = angle;

    Vector2 head = pos[0];

    if(distance(head, {new_x, new_y}) > raio * 2){
        Vector2 new_pos = {new_x, new_y};
        pos.push_front(new_pos);
        pos.pop_back();
    }

    draw_balls();

}

void boss(){
    std::cout << boss_vida << std::endl;
    if(!is_dead) update_boss();
}

void boss_collision(){
    if(!is_dead){
        for (size_t i = 0; i < pos.size(); ++i){
            int diametro = raio*2;
            // sair do centro do circulo para o canto superior esquerdo
            Bloco new_b = {0, pos[i].x-raio, pos[i].y-raio, diametro, diametro, true};
            if(block_colision(&new_b)){
                decrement_life();
            }
        }
    }
}