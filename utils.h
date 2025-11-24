#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"

Vector2 DrawTextCenter(const char *text, int fontSize, int y, Color color, int real_w, int fake_w=0);
bool delay(double value, Color *cor);

#endif