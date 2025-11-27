#include "ranking.h"
#include "raylib.h"
#include "utils.h"
#include "config.h"

std::vector<Score> score_table;
std::string caminho = "ranking.csv";
std::string nome = "";
const int MAX_CHARS = 3;
int pontos = 0;

void set_points(int points){
    pontos = points;
}

bool arquivoExiste(const std::string& caminho) {
    std::ifstream f(caminho);
    return f.good();
}

std::vector<Score>* get_rank(){
    return &score_table;
}

bool start_table(){

    if (!arquivoExiste(caminho)) {
        return false;  
    } 

    std::ifstream arquivo("ranking.csv");

    if (!arquivo.is_open()) {
        std::cout << "Não foi possível abrir o arquivo!\n";
        return false;
    }

    score_table.clear();

    std::string linha;

    while (std::getline(arquivo, linha)) {
        // fazer o parse da linha para pegar os campos de pontos e nome
        std::stringstream ss(linha);
        std::string points, nome;

        std::getline(ss, points, ',');
        std::getline(ss, nome, ',');

        score_table.push_back({std::stoi(points), nome});
    }

    arquivo.close();

    ordenar();

    return true;
}

void ordenar(){
    return std::sort(score_table.begin(), score_table.end(),
    //  regra para ordenar, coloca o elemento a antes de b se a > b
    [](const Score& a, const Score& b) {
        return a.sco > b.sco;
    });
}

bool is_in_ranking(){
    if (!pontos){
        return false; // não faça nada se a pontuação for zero
    }

    if (score_table.size() < 5){
        return true;
    }

    // top 5
    if (pontos <= score_table[4].sco){
        return false;
    }

    return true;
}

void get_player_name(int* scene){
    int k = GetCharPressed();

    while(k > 0){
        // excluir caracteres especiais, apenas letras de numeros
        // não adiciona se ultrapassar o tamanho da string
        if(k >= 32 && k <= 125 && nome.size() < MAX_CHARS){
            nome.push_back((char)k);
        }
        k = GetCharPressed();
    }

    ClearBackground(BLACK);

    DrawTextCenter("VOCÊ ENTROU NO TOP 5!!", F_SIZE*2, SCREEN_HEIGHT/4, GREEN, REAL_WIDTH);

    DrawTextCenter("- Digite seu nick (no máximo 3 caracteres) -", F_SIZE, SCREEN_HEIGHT/3, WHITE, REAL_WIDTH);

    DrawTextCenter(nome.c_str(), F_SIZE*1.5, SCREEN_HEIGHT/2, YELLOW, REAL_WIDTH);

    // apagar com backspace
    if (IsKeyPressed(KEY_BACKSPACE) && !nome.empty()) {
        nome.pop_back();
    }

    if(IsKeyPressed(KEY_ENTER) && !nome.empty()){
        AddCsvLine(pontos);
        *scene = 1; // voltar pro menu
    }

}

void AddCsvLine(int points){

    std::ofstream arquivo(caminho, std::ios::app); // APP = acrescentar no fim

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo!\n";
        return;
    }
    std::string points_str = std::to_string(points);

    arquivo << points_str << "," << nome << "\n"; // adiciona nova linha

    arquivo.close();

    start_table();
}


