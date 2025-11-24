#ifndef PAUSE_H
#define PAUSE_H
#include "raylib.h"
#include <vector>
#include <iostream>

extern Vector2 pos;
extern std::vector<std::string> opcoes;
extern int selecionada;
extern Texture2D textura;
extern int f_size;
extern int padding;
extern bool apertou;

void LoadAssets(void);
void UnloadAssets(void);
void pause_loop(int* scene);
void DrawTextCenter(const char *text, int fontSize, Color color);

#endif