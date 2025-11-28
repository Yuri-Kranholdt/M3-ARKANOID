#include "map.h"
#include "config.h"
#include "pause.h"
#include "utils.h"
#include "assets.h"
#include "game_loop.h"
#include "ranking.h"
#include "rank_screen.h"

namespace {
    int padding = F_SIZE * 2;
}

void rank_loop(int* scene){
              
    if (IsKeyDown(KEY_ENTER)) {
        *scene = 1;
        return;
    }

    std::vector<Score>* rank = get_rank();

    ClearBackground(BLACK);

    DrawTextCenter("-  TOP 5 JOGADORES  -", F_SIZE*1.5, SCREEN_HEIGHT/4, GREEN, REAL_WIDTH);

    for(int i=0; i<5; i++){
        int h_positon = (SCREEN_HEIGHT/3 + (i * padding));
        Score pontos = (*rank)[i];
        std::string linha = std::to_string(i+1) + "\t\t\t" + std::to_string(pontos.sco) + "\t\t" + pontos.nome;
        DrawTextCenter(linha.c_str(), F_SIZE*1.5, h_positon, WHITE, REAL_WIDTH);
    }

}