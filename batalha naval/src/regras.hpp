#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <string>

#include "entidades.hpp"

/*
  Esse arquivo contem todas as funcoes resposaveis pelas regras do jogo.
*/

bool valida_pos_navios(int x_pretendido, int y_pretendido, bool em_pe, Navio navio_pretendido, Jogador &jogador){
    // Valida o lugar onde o navio será colocado no mapa
    if (jogador.mapa[x_pretendido][y_pretendido].alvo == NAVIO)
        return false;

    if (em_pe)
    {
        if ((y_pretendido + navio_pretendido.tamanho) > tamanho_mapa)
            return false;
        for (int i = 1; i < navio_pretendido.tamanho; i++)
        {
            if (jogador.mapa[x_pretendido][y_pretendido + i].alvo == NAVIO)
                return false;
        }
    }
    else
    {
        if ((x_pretendido + navio_pretendido.tamanho) > tamanho_mapa)
            return false;
        for (int i = 1; i < navio_pretendido.tamanho; i++)
        {
            if (jogador.mapa[x_pretendido + i][y_pretendido].alvo == NAVIO)
                return false;
        }
    }
    return true;
}

void coloca_navios(int x_pretendido, int y_pretendido, bool em_pe, int id_navio_pretendido, Jogador &jogador){
    // Coloca os navios nos locais definidos e guarda a localizacao em jogador
    int tamanho_navio = jogador.frota[id_navio_pretendido].tamanho;

    if (em_pe)
    {
        for (int i = 0; i < tamanho_navio; i++)
        {
            Quadrante &quadrante = jogador.mapa[x_pretendido][y_pretendido + i];

            quadrante.alvo = NAVIO;
            jogador.frota[id_navio_pretendido].localizacao.push_back(&quadrante);
        }
    }
    else
    {
        for (int i = 0; i < tamanho_navio; i++)
        {
            Quadrante &quadrante = jogador.mapa[x_pretendido + i][y_pretendido];

            quadrante.alvo = NAVIO;
            jogador.frota[id_navio_pretendido].localizacao.push_back(&quadrante);
        }
    }
}

void coloca_navios_aleatorios(Jogador &jogador){
    // funcao que posiciona os navios de forma aleatoria.
    srand(time(0));
    for(int i=0; i < qte_frota; i++){
        bool valido = false;
        int x;
        int y;
        bool em_pe;
        int cont = 0;
        while(!valido){
            x = rand() % tamanho_mapa;
            y = rand() % tamanho_mapa;
            em_pe = rand() % 2;
            valido = valida_pos_navios(x, y, em_pe, jogador.frota[i], jogador);
            cont++;
        }
    coloca_navios(x, y, em_pe, i, jogador);
    }
}


bool valida_tiro(Quadrante quadrante){
    // Valida o tiro, caso quadrante já não tenha sido acertado antes.
    if (quadrante.acertou)
    {
        return false;
    };
    return true;
}

 void atira_bot(Jogador &alvo){
    // Simula o computador atirando. Os tiros são aleatorios.
    bool tiro_valido = false;
    int x;
    int y;

    while (!tiro_valido)
    {
        x = rand() % tamanho_mapa;
        y = rand() % tamanho_mapa;
        tiro_valido = valida_tiro(alvo.mapa[x][y]);
    }
    
    alvo.mapa[x][y].acertou = true;
}

void verifica_destroi_navio(Navio &navio){
    // Verifica se um certo navio foi destruido completamente
    std::vector<quadrante *> localizacao_navio = navio.localizacao;
    
    for(int i = 0; i < navio.tamanho; i++){
        if(!(localizacao_navio[i]->acertou)){
            navio.destruido = false;
            break;
        }
        navio.destruido = true;
    }
}

int conta_navios_restantes(Jogador jogador){
    // Retorna quantos navios nao afundados restam 
    std::array<Navio, qte_frota> frota_jogador = jogador.frota;
    int pontos = 0;
    
    for(int i = 0; i < qte_frota; i++){
        verifica_destroi_navio(frota_jogador[i]);
        if(!frota_jogador[i].destruido)
            pontos++;
    }
    return pontos;
    
}

void atualiza_pontuacao(Jogador &jogador){
    // atualiza a pontuacao do jogo, dependendo do seu modo.
    if(jogador.modo_de_jogo == SP){
        jogador.pontos--;
    } else {
        jogador.pontos = conta_navios_restantes(jogador);
    }
}

