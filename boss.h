#ifndef BOSS_H
#define BOSS_H

#include <deque>
#include "raylib.h"

// Variáveis globais
extern bool voltando;
extern float angle;
extern float wave;
extern float v;
extern std::deque<Vector2> pos;
extern float raio;
extern int boss_vida;
extern bool is_dead;
extern float wave_h;
extern float amp;

// Declarações de funções
float rad(float degree);
float distance(Vector2 a, Vector2 b);

void start_balls();
void init_boss();
void decrement_life();
void draw_balls();
void update_boss();
void boss();
void boss_collision();

#endif
