#include "game_over.h"

namespace {
    std::vector<std::string> opcoes = {"VOLTAR AO MENU"};
    int selecionada = 0;
    int padding = F_SIZE * 2;
    bool apertou = false;
    Color corAtual = WHITE;
}

void game_over_loop(int* scene, int *score, int *high_score){

    if (IsKeyPressed(KEY_DOWN)) {
        selecionada = (selecionada + 1) % opcoes.size();
    }

    if (IsKeyPressed(KEY_UP)) {
        selecionada = (selecionada - 1 + opcoes.size()) % opcoes.size();
    }

    bool exit_code = delay(0.1, &corAtual);

    if(exit_code){
        if (selecionada == 0) {
            deallocate_map();

            up_high_score(high_score, score, scene);
        }
        
    }

    ClearBackground(BLACK);

    DrawTextCenter("GAME OVER!", F_SIZE*2, SCREEN_HEIGHT/4, RED, REAL_WIDTH);

    for (int i = 0; i<opcoes.size(); i++) {
        int h_positon = (SCREEN_HEIGHT/2 + (i * padding));
        Color cor = (i == selecionada) ? corAtual : WHITE;
        Vector2 pos = DrawTextCenter(opcoes[i].c_str(), F_SIZE, h_positon, cor, REAL_WIDTH);
        if(i == selecionada) DrawTextureEx(GetAssets()->seta, {pos.x-30, (float)h_positon}, 0.0f, 0.1f, WHITE);

    }

}