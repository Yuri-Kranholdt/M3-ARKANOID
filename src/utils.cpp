#include "raylib.h"
#include <cstdlib>
#include "utils.h"


Vector2 DrawTextCenter(const char *text, int fontSize, int y, Color color, int real_w, int fake_w) {
    int sidewidth = real_w-fake_w;

    int textWidth = MeasureText(text, fontSize);
    int x = fake_w + (sidewidth - textWidth) / 2;

    DrawText(text, x, y, fontSize, color);

    return Vector2{(float)x, (float)y};
}

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

void up_high_score(int *high_score, int* score, int* scene){
    if(*high_score < *score) *high_score = *score; // se superar o recorde salva em high_score
            *score = 0;
            *scene = 1;
}

