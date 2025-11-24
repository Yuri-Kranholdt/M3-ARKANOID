#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <vector>
#include "map.h"
#include "config.h"

struct Bloco {
  int vida;
  int x;
  int y;
  int w;
  int h;
  bool is_wall;
  bool is_dead;
  Color color;
  int velocity;
  bool is_steel;
};

extern int per_line;
extern int bloco_h;
extern int wall_width;
extern int bloco_w;
extern int n_lines;
extern int start_from;
extern bool starting;

extern std::vector<Bloco> blocos;

extern Bloco placa;
extern Vector2 ballPosition;

extern float vx;
extern float vy;


// -------------------------------------------------
// Declarações das funções
// -------------------------------------------------

void block_colision(Bloco* bloco);
Color cor_aleatoria();
void read_map(const Mapa& matriz);
void init_walls();
void draw_blocks();
void game_loop(int &scene, int* level);
void load_map(int level);
void deallocate_map();

#endif