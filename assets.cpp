#include "assets.h"
#include <iostream>

static Assets assets = {0};

Assets* GetAssets(){
    return &assets;
}

void LoadAssets(){
    assets.seta = LoadTexture("img/seta.png");
    assets.pad1 = LoadTexture("img/pad1.png");
    assets.hor_walls = LoadTexture("img/wall4.png");
    assets.ver_walls = LoadTexture("img/wall_top.png");
    assets.background = LoadTexture("img/back1.png");
}

void UnloadAssets(){
    UnloadTexture(assets.seta);
    UnloadTexture(assets.pad1);
    UnloadTexture(assets.hor_walls);
    UnloadTexture(assets.ver_walls);
    UnloadTexture(assets.background);
}

