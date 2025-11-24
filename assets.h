#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

struct Assets {
    Texture2D seta;
    Texture2D pad1;
    Texture2D hor_walls;
    Texture2D ver_walls;
    Texture2D background; 
};

Assets* GetAssets();
void LoadAssets();
void UnloadAssets();

#endif