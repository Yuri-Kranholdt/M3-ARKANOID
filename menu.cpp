#include "config.h"
#include "utils.h"
#include "assets.h"
#include "menu.h"
#include "map.h"
#include "game_loop.h"
#include <vector>

// se tiver um ponto no final então é um selecionavel

namespace {
    std::vector<std::string> dificuldade = {"FÁCIL", "MÉDIO", "DIFICIL"};

    std::vector<std::string> niveis = {"1", "2", "3"};

    //std::vector<std::string> opcoes = {"JOGAR", "NIVEL.", "DIFICULDADE.", "SAIR"};
    std::vector<options> opcoes = {{"JOGAR", false}, {"NIVEL",true}, {"DIFICULDADE",true}, {"SAIR", false}};

    int selecionada = 0;
    int select2 = 0;
    int padding = F_SIZE * 2;
    bool apertou = false;
    Color corAtual = WHITE;
}


void update_change(int index, std::vector<std::string> values_list, int *variable){
    select2 = *variable;
    if(selecionada == index){

        if (IsKeyPressed(KEY_RIGHT)) {
            select2 = (select2 + 1) % values_list.size();
        }

        if (IsKeyPressed(KEY_LEFT)) {
            select2 = (select2 - 1 + values_list.size()) % values_list.size();
        }

        *variable = select2;

        opcoes[index].phrase = values_list[select2];
    }
}


void menu_loop(int* scene, int *level, int *difficulty, int *score, bool *exit){
              
    if (IsKeyDown(KEY_ENTER)) *scene = 0;

    if (IsKeyPressed(KEY_DOWN)) {
        selecionada = (selecionada + 1) % opcoes.size();
    }

    if (IsKeyPressed(KEY_UP)) {
        selecionada = (selecionada - 1 + opcoes.size()) % opcoes.size();
    }

    bool exit_code = delay(0.1, &corAtual);

    if(exit_code){

        if(selecionada == 0) {
            load_map(*level, score);
            //printf("level ->%d\n", *level);
            *scene = 0;
        }
        else if(selecionada == 3){
            *exit = true;
        }
    }
    
    update_change(2, dificuldade, difficulty);
    update_change(1, niveis, level);
    ClearBackground(BLACK);

    DrawTextCenter("ARKANOID", F_SIZE*2, SCREEN_HEIGHT/4, WHITE, REAL_WIDTH);

    for (int i = 0; i<opcoes.size(); i++) {
        int h_positon = (SCREEN_HEIGHT/2 + (i * padding));
        std::string phrase = i == selecionada && opcoes[i].can_change ? "< " + opcoes[i].phrase + " >" : opcoes[i].phrase;
        Color cor = (i == selecionada) ? corAtual : WHITE;
        Vector2 pos = DrawTextCenter(phrase.c_str(), F_SIZE, h_positon, cor, REAL_WIDTH);
        if(i == selecionada) DrawTextureEx(GetAssets()->seta, {pos.x-30, (float)h_positon}, 0.0f, 0.1f, WHITE);

    }
}