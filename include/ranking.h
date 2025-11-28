#ifndef RANK_H
#define RANK_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct Score
{
    int sco;
    std::string nome;
};

extern std::vector<Score> score_table;

std::vector<Score>* get_rank();

void set_points(int points);

bool arquivoExiste(const std::string& caminho);

void get_player_name(int* scene);

void AddCsvLine(int points);

bool start_table();

void ordenar();

bool is_in_ranking();

void AddCsvLine(int points, std::string nome);

#endif