#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <deque>
#include <string>
#include <time.h>
// #include <cmath>
#include <thread>
#include <chrono>

enum Alvos
{
    AGUA,          // 0
    NAVIO,         // 1
    AGUA_ATINGIDA, // 2
    NAVIO_ATINGIDO // 3
};

enum DisplayMapa
{
    NADA,         // 0
    ACERTOU_AGUA, // 1
    ACERTOU_NAVIO // 2
};

enum Navios
{
    PORTA_AVIOES = 5,
    CRUZADOR = 4,
    CONTRATORPEDEIRO = 3,
    SUBMARINO = 2
};

const int tamanho_mapa = 10;
const int qte_frota = 7;

Alvos mapa[tamanho_mapa][tamanho_mapa];
DisplayMapa display[tamanho_mapa][tamanho_mapa];

const Navios navios[qte_frota] = {PORTA_AVIOES, CRUZADOR, CONTRATORPEDEIRO, CONTRATORPEDEIRO, SUBMARINO, SUBMARINO, SUBMARINO};

struct Jogador
{
    Alvos mapa[tamanho_mapa][tamanho_mapa];
    DisplayMapa display[tamanho_mapa][tamanho_mapa];
    int pontos = qte_frota;
};

void gera_mapas(Jogador &jogador, Jogador &adversario)
{
    for (int i = 0; i < tamanho_mapa; i++)
    {
        for (int j = 0; j < tamanho_mapa; j++)
        {
            jogador.mapa[i][j] = AGUA;
            jogador.display[i][j] = NADA;

            adversario.mapa[i][j] = AGUA;
            adversario.display[i][j] = NADA;
        }
    }
}

void mostra_mapa(Alvos (&mapa)[tamanho_mapa][tamanho_mapa])
{
    for (int i = 0; i < tamanho_mapa; i++)
    {
        for (int j = 0; j < tamanho_mapa; j++)
        {
            std::cout << mapa[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool valida_pos_navios(int x, int y, Navios navio, bool em_pe, Alvos (&mapa)[tamanho_mapa][tamanho_mapa])
{
    if (mapa[x][y] == 1)
        return false;
    if (em_pe)
    {
        if ((x + navio) > 10)
            return false;
    }
    else
    {
        if ((y + navio) > 10)
            return false;
    }
    return true;
}

void coloca_navios(Navios navio, int x, int y, bool em_pe, Jogador &jogador)
{
    if (em_pe)
    {
        for (int i = 0; i < navio; i++)
        {
            jogador.mapa[x + i][y] = NAVIO;
        }
    }
    else
    {
        for (int i = 0; i < navio; i++)
        {
            jogador.mapa[x][y + i] = NAVIO;
        }
    }
}

void mapa_navios_teste(Jogador &jogador)
{
    coloca_navios(navios[0], 0, 0, false, jogador);
    coloca_navios(navios[1], 2, 0, true, jogador);
    coloca_navios(navios[2], 3, 4, false, jogador);
    coloca_navios(navios[3], 8, 9, true, jogador);
    coloca_navios(navios[4], 6, 7, false, jogador);
    coloca_navios(navios[5], 8, 2, true, jogador);
    coloca_navios(navios[6], 0, 9, true, jogador);
    
    
}

void escolha_quadrante_navios(Jogador &jogador)
{
    int x;
    int y;
    char em_pe_deitado;
    bool em_pe;

    std::cout << "Escolha a quadrante em que seus navios ficarao: " << std::endl;

    for (int i = 0; i < qte_frota; i++)
    {
        bool quadrante_navio_valida = false;
        while (!quadrante_navio_valida)
        {
            std::cout << navios[i] << ": " << std::endl;
            std::cout << "linha: ";
            std::cin >> x;
            std::cout << "coluna: ";
            std::cin >> y;
            std::cout << "em pe ou deitado (P/D): ";
            std::cin >> em_pe_deitado;

            while (em_pe_deitado != 'P' and em_pe_deitado != 'p' and em_pe_deitado != 'D' and em_pe_deitado != 'd')
            {
                std::cout << "Digite uma letra valida (P/D): ";
                std::cin >> em_pe_deitado;
            }
            if (em_pe_deitado == 'P' or em_pe_deitado == 'p')
            {
                em_pe = true;
            }
            else
            {
                em_pe = false;
            }
            quadrante_navio_valida = valida_pos_navios(x, y, navios[i], em_pe, jogador.mapa);
            if (!quadrante_navio_valida)
                std::cout << "Quadrante invalida." << std::endl;
        }
        coloca_navios(navios[i], x, y, em_pe, jogador);
    }
};

bool valida_tiro(int x, int y, Alvos (&mapa)[tamanho_mapa][tamanho_mapa])
{
    if (x >= tamanho_mapa or x < 0 or y >= tamanho_mapa or y < 0)
    {
        std::cout << "Tiro fora do mapa." << std::endl;
        return false;
    }
    if (mapa[x][y] == AGUA_ATINGIDA or mapa[x][y] == NAVIO_ATINGIDO)
    {
        std::cout << "Voce ja atirou neste lugar." << std::endl;
        return false;
    };
    return true;
}

void atira(Jogador &alvo, int x, int y)
{
    if (alvo.mapa[x][y] == AGUA)
    {
        std::cout << "Acertou Agua!" << std::endl;
        alvo.mapa[x][y] = AGUA_ATINGIDA;
        alvo.display[x][y] = ACERTOU_AGUA;
    }
    if (alvo.mapa[x][y] == NAVIO)
    {
        std::cout << "Acertou Navio!" << std::endl;
        alvo.mapa[x][y] = NAVIO_ATINGIDO;
        alvo.display[x][y] = ACERTOU_NAVIO;
    }
};

void atira_bot(Jogador &jogador)
{
    bool tiro_valido = false;
    int x;
    int y;

    while (!tiro_valido)
    {
        x = rand() % tamanho_mapa;
        y = rand() % tamanho_mapa;
        tiro_valido = valida_tiro(x, y, jogador.mapa);
    }
    atira(jogador, x, y);
}

void o_jogo(Jogador &jogador, Jogador &adversario)
{
    bool fim_jogo;
    int cont = 0; // limitar o numero de rodadas

    while (!fim_jogo)
    {
        int x;
        int y;
        bool tiro_valido = false;

        std::cout << "Onde vai atirar?: " << std::endl;

        while (!tiro_valido)
        {
            std::cout << "linha: ";
            std::cin >> x;
            std::cout << "coluna: ";
            std::cin >> y;
            tiro_valido = valida_tiro(x, y, adversario.mapa);
        };
        atira(adversario, x, y);
        atira_bot(jogador);
        cont++;
        if (cont == 10)
            fim_jogo = true;
    }
    std::cout << "Fim de jogo!" << std::endl;
    mostra_mapa(adversario.mapa);
    std::cout << std::endl;
    mostra_mapa(jogador.mapa);
}

int main()
{
    Jogador jogador;
    Jogador adversario;
    bool teste = true;
    srand(time(0));
    gera_mapas(jogador, adversario);
    mapa_navios_teste(adversario);
    if (teste)
    {
        mapa_navios_teste(jogador);
    }
    else
    {
        escolha_quadrante_navios(jogador);
    }

    mostra_mapa(adversario.mapa);
    std::cout << std::endl;
    mostra_mapa(jogador.mapa);

    o_jogo(jogador, adversario);
    return 0;
}
