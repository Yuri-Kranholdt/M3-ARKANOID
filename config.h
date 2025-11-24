#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"
#include <iostream>

struct options {
    std::string phrase;
    bool can_change;
};

extern const Color cores[9];

constexpr int SCREEN_WIDTH  = 600;
constexpr int SCREEN_HEIGHT = 600;

constexpr int F_SIZE = 20;

constexpr int FPS = 60;

constexpr int RAIO = 5;

#endif