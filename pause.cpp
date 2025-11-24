#include "map.h"
#include "config.h"
#include "pause.h"

std::vector<std::string> opcoes = {"VOLTAR", "SAIR"};
int selecionada = 0;

Texture2D textura;

int f_size = 20;
int padding = f_size*2;

bool apertou = false;
double proximaTroca = 0;
int contadorPisca = 0; 
Color corAtual = WHITE;

bool delay(double value, Color *cor){
    static bool state = false;
    bool finish = false;
    static double next_change = 0;
    static int counter = 0;

    if(IsKeyDown(KEY_SPACE) && !state){
        state = true;
        counter = 0;
        next_change = GetTime();
    }

    if(state){
        double agora = GetTime();

        if(agora>=next_change){
            if(cor->r == 255){
                *cor = BLACK;
            }else *cor = WHITE;

            counter++;
            next_change = agora + value;
        }

        if(counter >= 10){
            state = false;
            finish = true;
            *cor = WHITE;
        }
    }
    return finish;
}

void DrawTextCenter(const char *text, int fontSize, int y, Color color) {
    int screenWidth = GetScreenWidth();

    int textWidth = MeasureText(text, fontSize);
    int x = (screenWidth - textWidth) / 2;

    DrawText(text, x, y, fontSize, color);
}

void LoadAssets(void) {
    Image img = LoadImage("img/seta.png");

    if (img.data == NULL) {
        printf("Falha ao carregar imagem!\n");
    } else {
        printf("Imagem carregada: %d x %d\n", img.width, img.height);
    }
    
    ImageResize(&img, 15, 15);
    
    textura = LoadTextureFromImage(img);

    UnloadImage(img);
}

void UnloadAssets(void) {
    UnloadTexture(textura);
}


void pause_loop(int* scene){
              
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
    }

    ClearBackground(BLACK);

    DrawTextCenter("PAUSADO", 30+10, SCREEN_HEIGHT/4, WHITE);

    for (int i = 0; i<opcoes.size(); i++) {
        Color cor = (i == selecionada) ? corAtual : WHITE;
        if(i == selecionada) DrawTexture(textura, (SCREEN_WIDTH/2)-80, SCREEN_HEIGHT/2 + (i * padding), WHITE);
        DrawTextCenter(opcoes[i].c_str(), f_size, SCREEN_HEIGHT/2 + (i * padding), cor);

    }

}