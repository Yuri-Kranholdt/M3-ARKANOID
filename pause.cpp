#include "map.h"
#include "config.h"
#include "pause.h"
#include "utils.h"
#include "assets.h"
#include "game_loop.h"
#include "ranking.h"

namespace {
    std::vector<std::string> opcoes = {"RETOMAR", "MENU"};
    int selecionada = 0;
    int padding = F_SIZE * 2;
    bool apertou = false;
    Color corAtual = WHITE;
}

void pause_loop(int* scene, int *score, int *high_score){
              
    if (IsKeyDown(KEY_ENTER)) *scene = 0;

    if (IsKeyPressed(KEY_DOWN)) {
        selecionada = (selecionada + 1) % opcoes.size();
    }

    if (IsKeyPressed(KEY_UP)) {
        selecionada = (selecionada - 1 + opcoes.size()) % opcoes.size();
    }

    bool exit_code = delay(0.1, &corAtual);

    if(exit_code){
        if(selecionada == 0) *scene = 0;
        else if (selecionada ==1) {
            // setar os pontos no arquivo
            set_points(*score);

            deallocate_map();
            up_high_score(high_score, score, scene);

            // verificar se merece entrar no ranking
            if(is_in_ranking()){
                *scene= 7;
            }
        }
        
    }

    ClearBackground(BLACK);

    DrawTextCenter("PAUSADO", F_SIZE*2, SCREEN_HEIGHT/4, WHITE, REAL_WIDTH);

    for (int i = 0; i<opcoes.size(); i++) {
        int h_positon = (SCREEN_HEIGHT/2 + (i * padding));
        Color cor = (i == selecionada) ? corAtual : WHITE;
        Vector2 pos = DrawTextCenter(opcoes[i].c_str(), F_SIZE, h_positon, cor, REAL_WIDTH);
        if(i == selecionada) DrawTextureEx(GetAssets()->seta, {pos.x-30, (float)h_positon}, 0.0f, 0.1f, WHITE);

    }

}