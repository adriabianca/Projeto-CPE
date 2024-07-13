#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <string>
#include <raylib.h>

#include "entidades.hpp"

/*
  Esse arquivo contem as funcoes geradoras de todas as entidades do jogo.
*/

Quadrante gera_quadrante(float x, float y)
{   // Gera o tipo quadrante
    Quadrante quadrante;
    quadrante.quadrado = {x, y, tamanho_lado_quadrante, tamanho_lado_quadrante};
    quadrante.posicao = {x, y};
    quadrante.alvo = AGUA;
    quadrante.acertou = false;

    return quadrante;
}


std::array<Navio, qte_frota> gera_frota()
{   // Gera lista de navios
    std::array<Navio, qte_frota> navios;
    
    navios[0].modelo = "PORTA AVIOES";
    navios[0].tamanho = 5;
    navios[0].destruido = false;
    
    navios[1].modelo = "CRUZADOR";
    navios[1].tamanho = 4;
    navios[1].destruido = false;
    
    navios[2].modelo = "CONTRATORPEDEIRO";
    navios[2].tamanho = 3;
    navios[2].destruido = false;
    
    navios[3].modelo = "CONTRATORPEDEIRO";
    navios[3].tamanho = 3;
    navios[3].destruido = false;
    
    navios[4].modelo = "SUBMARINO";
    navios[4].tamanho = 2;
    navios[4].destruido = false;
    
    navios[5].modelo = "SUBMARINO";
    navios[5].tamanho = 2;
    navios[5].destruido = false;
    
    navios[6].modelo = "SUBMARINO";
    navios[6].tamanho = 2;
    navios[6].destruido = false;
    
    return navios;
}

Jogador gera_jogador(bool eh_bot, ModoJogo modo_jogo)
{   // Gera jogadores
    Jogador jogador;
    jogador.frota = gera_frota();
    jogador.eh_bot = eh_bot;
    if(modo_jogo == SP)
        jogador.pontos = tentativas_singleplayer;
    else
        jogador.pontos = qte_frota;
    
    jogador.modo_de_jogo = modo_jogo;

    return jogador;
}

void gera_mapa(Jogador &jogador, float pos_mapa_x, float pos_mapa_y){
    // Gera os mapas vazios do jogdor e do bot adversário
    int pos_quadrante_x;
    int pos_quadrante_y;
    for (int i = 0; i < tamanho_mapa; i++)
    {
        for (int j = 0; j < tamanho_mapa; j++)
        {
            pos_quadrante_x = pos_mapa_x + (i * tamanho_lado_quadrante);
            pos_quadrante_y = pos_mapa_y + (j * tamanho_lado_quadrante);
            
            Quadrante quadrante = gera_quadrante(pos_quadrante_x, pos_quadrante_y);

            jogador.mapa[i][j] = quadrante;
        }
    }
}

Botao gera_botoes(char* nome_botao, float posicao_x, float posicao_y, TelaJogo vai_para){
    // Gera os botões do jogo
    Botao botao;

    botao.nome_botao = nome_botao;
    botao.espaco_botao = {posicao_x, posicao_y, largula_botao, altura_botao};
    botao.posicao = {posicao_x, posicao_y};
    botao.vai_para = vai_para;

    return botao;
    
}
void prepara_jogo(ModoJogo modo_jogo, std::vector<Jogador> &jogadores){
    // Prepara a inicio do jogo dependendo do modo de jogo escolhido
    if(jogadores.size() > 0)
        jogadores.clear();
    
    switch (modo_jogo)
    {
    case SP:
        {
            jogadores.push_back(gera_jogador(true, modo_jogo));

            float pos_mapa_jogador_x = (largura_tela / 2.0) - tamanho_lado_quadrante * 5;

            gera_mapa(jogadores[0], pos_mapa_jogador_x, altura_mapa_na_tela);

            break;
        }
    case CPU:
        {
            jogadores.push_back(gera_jogador(false, modo_jogo));
            jogadores.push_back(gera_jogador(true, modo_jogo));

            float pos_mapa_jogador_x = (largura_tela / 4.0) - tamanho_lado_quadrante * 5;
            float pos_mapa_adv_x = (3 * largura_tela / 4.0) - tamanho_lado_quadrante * 5;

            gera_mapa(jogadores[0], pos_mapa_jogador_x, altura_mapa_na_tela);
            gera_mapa(jogadores[1], pos_mapa_adv_x, altura_mapa_na_tela);

            break;
        }
    default:
       break;
    }
}
