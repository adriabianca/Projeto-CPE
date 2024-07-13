#ifndef ENTIDADES
#define ENTIDADES

#include <vector>
#include <array>
#include <string>
#include <raylib.h>

/*
  Esse arquivo onde as variaveis globais são inicializadas e todas as entidades definidas.
*/
// Dimensoes da tela do jogo.
const int largura_tela = 800;
const int altura_tela = 600;
// A altura em relacao a tela, os mapas comecam a ser desenhados.
const float altura_mapa_na_tela = 50.0;
// Dimensoes do botao.
const int largula_botao = 175;
const int altura_botao = 75;
// Dimensao dos quandrantes dos mapas
const int tamanho_lado_quadrante = 20;
// constantes relacionadas ao jogo
const int tamanho_mapa = 10;
const int qte_frota = 7;
const int tentativas_singleplayer = 20;
const int qte_jogadores = 2;

// Indicadores para manipulacao de mensagens e delay
bool ja_acertou = false;
bool acertou_agua = false;
bool acertou_navio = false;
bool vez_jogador = true;

enum Alvos
{
    AGUA,  // 0
    NAVIO, // 1
};

enum ModoJogo{
    SP, //singleplayer (0)
    CPU, // Vs CPU (1)
};

typedef enum telaJogo {
    MENU,
    ESCOLHER_MODO_JOGO,
    SINGLEPLAYER,
    VSCPU,
    FIM_DE_JOGO_VITORIA,
    FIM_DE_JOGO_DERROTA,
    FECHA_JOGO
} TelaJogo; // Tipos de estados do jogo.

typedef struct botao
{
    char* nome_botao;
    Rectangle espaco_botao;
    Vector2 posicao;
    Vector2 dimensoes = {largula_botao, altura_botao};
    bool mouse_em_cima = false;
    TelaJogo vai_para;

} Botao;


typedef struct quadrante
{
    Rectangle quadrado;
    Vector2 posicao;
    Vector2 dimensoes = {tamanho_lado_quadrante, tamanho_lado_quadrante};
    Alvos alvo;
    bool acertou;
} Quadrante;

typedef struct navio
{
    std::string modelo;
    int tamanho;
    std::vector<quadrante *> localizacao;
    bool destruido;
} Navio;

typedef struct jogador
{
    Quadrante mapa[tamanho_mapa][tamanho_mapa];
    std::array<Navio, qte_frota> frota;
    int pontos;
    bool eh_bot;
    ModoJogo modo_de_jogo;
} Jogador;

#endif
