#include "config.h"
#include <iostream>

std::vector<Block_Texture> blocks_texture;
std::vector<Texture2D> powers_texture;

void init_blockTexures() {

    const int base_point = 50;
    
    const char* arquivosTextura[9] = {
        "img/blocks/azul.png",
        "img/blocks/verde.png",
        "img/blocks/laranja.png",
        "img/blocks/vermelho.png",
        "img/blocks/ciano.png",
        "img/blocks/magenta.png",
        "img/blocks/amarelo.png",
        "img/blocks/prata.png",
        "img/blocks/ouro.png"
    };

    for (int i = 0; i < 9; i++) {
        int block_points = i != 9 ? base_point + (i*10) : 0; // bloco dourado n tem pontos(indestrutivel)
        blocks_texture.push_back({LoadTexture(arquivosTextura[i]), block_points});
    }
}

void init_powerTextures(){

    const char* arquivosTextura[4] = {
        "img/power/c.png",
        "img/power/e.png",
        "img/power/l.png",
        "img/power/s.png",
    };

    for (int i = 0; i < 4; i++) {
        // bloco dourado n tem pontos(indestrutivel)
        powers_texture.push_back({LoadTexture(arquivosTextura[i])});
    }
}

Texture2D* Get_Power(int i ){
    return &powers_texture[i];
}

Texture2D Get_BlockText(int i){
    return blocks_texture[i].tex;
}

Block_Texture Get_BlockAttr(int i){
    return blocks_texture[i];
}

void UnloadBlocks(){
    for (int i = 0; i < 9; i++) {
        UnloadTexture(blocks_texture[i].tex);
    }
}


const Color cores[9] = {
    {0,   162,   255, 255},  // azul
    {0,   255, 0,   255},  // verde
    {255, 165, 0,   255},  // laranja
    {255, 0,   0,   255},  // vermelho
    {0,   255, 255, 255},  // ciano
    {255, 0,   255, 255},  // magenta
    {255, 255, 0,   255},  // amarelo
    {192, 192, 192, 255},  // prata
    {255, 215, 0,   255}   // ouro
};
