# Arkanoid - Algoritmos 2

Este é um clone do clássico jogo **Arkanoid**, desenvolvido em C++ utilizando a biblioteca **Raylib**. O projeto foi feito como parte da disciplina **Algoritmos 2**.

## Sobre o Jogo

O objetivo do jogo é controlar a barra na parte inferior da tela para rebater a bola e destruir todos os blocos na tela. O jogador perde se a bola passar pela barra. O jogo termina quando todos os niveis são concluídos ou o jogador perde todas as vidas.

### Funcionalidades

- Movimentação da barra com o teclado.
- Rebote da bola nos blocos e nas paredes.
- Sistema de pontuação e ranking.
- Vidas do jogador.
- sistema de power ups
- um boss utilizando equações trigonométricas

## Tecnologias Utilizadas

- **C++17**
- **Raylib 4.x**
- **Makefile** (via quickstart do Raylib)

O projeto foi baseado no **Raylib Quickstart** para C++:  
[https://github.com/raylib-extras/raylib-quickstart](https://github.com/raylib-extras/raylib-quickstart)

## Como Compilar

### Requisitos

- C++17 compatível (GCC, Clang ou MSVC)
- Raylib (já incluído via Quickstart)

### Passos


1. execute o arquivo build-MinGW-W64.bat na raiz do projeto
```bash
    ./build-MinGW-W64.bat  
```

2. escreva o seguinte com a raiz do projeto aberta em algum terminal
```bash
    make
```

3. entre na pasta bin e então debug, agora execute o executável dentro da pasta

