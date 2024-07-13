#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <string>
#include <raylib.h>

#include "entidades.hpp"

/*
  Esse arquivo guarda todas as funcoes relacionadas a desenho de tela e suas interacoes com o jogador.
*/

void reage_mouse_botao(Botao &botao, TelaJogo &modo_tela){
    /*
    Funcao que verifica a interacao do mouse com o botao que esta na tela.
    */
    if (CheckCollisionPointRec(GetMousePosition(), botao.espaco_botao)) {
        botao.mouse_em_cima = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            modo_tela = botao.vai_para;
                        }
    } else {
        botao.mouse_em_cima = false;
    }
}

void interacao_mapa(Jogador &jogador){
    /*
    Funcao que verifica a interacao do mouse com os quadrantes do mapa.
    */
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
        if (CheckCollisionPointRec(GetMousePosition(), jogador.mapa[i][j].quadrado)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if(valida_tiro(jogador.mapa[i][j])){
                    jogador.mapa[i][j].acertou = true;
                                
                    if(jogador.mapa[i][j].alvo == AGUA){
                        acertou_agua = true;
                        atualiza_pontuacao(jogador);
                    }
                    if(jogador.mapa[i][j].alvo == NAVIO){
                        acertou_navio = true;
                        if(jogador.modo_de_jogo != SP){
                            atualiza_pontuacao(jogador);
                        }
                    }
                    
                    vez_jogador = false;
                    
                } else if(jogador.mapa[i][j].acertou)
                    ja_acertou = true;
            }
        }
        }
    }
}

Color cor_botao(bool intera_mouse){
    /*
    Retorna a cor do botao caso o mouse está em cima dele ou nao
    */
    if (intera_mouse){
        return GREEN;
    }
    return LIME;
}

void desenha_botao(Botao botao){
    /*
    Desenha o botão com texto dentro
    */
    DrawRectangleRec(botao.espaco_botao, cor_botao(botao.mouse_em_cima));
    DrawRectangleLinesEx(botao.espaco_botao, 1, BLACK);
    // Calcula a posição central para o texto
    int textX = botao.posicao.x + (botao.dimensoes.x - MeasureText(botao.nome_botao, 20)) / 2;
    int textY = botao.posicao.y + (botao.dimensoes.y - 20) / 2;

    DrawText(botao.nome_botao, textX, textY, 20, BLACK); // Escreve o texto
}

Color cor_quadrante(Quadrante quadrante, bool eh_bot){
    /*
    Retorna as cores dos quadrantes dos mapas de acordo com seu estado.
    */
    if(quadrante.alvo == AGUA && quadrante.acertou) return BLUE;
    if(quadrante.alvo == AGUA && (!quadrante.acertou)) return SKYBLUE;
    if(quadrante.alvo == NAVIO && quadrante.acertou) return RED;
    if(quadrante.alvo == NAVIO && (!quadrante.acertou) && eh_bot) return SKYBLUE;
    if(quadrante.alvo == NAVIO && (!quadrante.acertou) && (!eh_bot)) return MAGENTA;
    return WHITE;
}

void desenha_mapa(Quadrante (&mapa)[tamanho_mapa][tamanho_mapa], bool eh_bot){
    /*
    Desenha os mapas do jogo.
    */
    Quadrante quadrante;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            quadrante = mapa[i][j];
            DrawRectangleRec(quadrante.quadrado, cor_quadrante(quadrante, eh_bot));
            DrawRectangleLinesEx(quadrante.quadrado, 1, BLACK);
        }
    }
}

void escreve_texto_centralizado(const char* titulo, float altura, int tamanho, Color color){
    /*
    Funcao para centralizar textos em geral.
    */
    int titulo_x = (largura_tela - MeasureText(titulo, tamanho)) / 2;
    int titulo_y = altura;

    DrawText(titulo, titulo_x, titulo_y, tamanho, color);
}

void escreve_placar(int pontos_jogador, int pontos_adversario){
    /*
    Monta o placar do jogo para mostrar na tela, no modo vs CPU.
    */
    std::string texto = "Você " + std::to_string(pontos_jogador) + " X " + std::to_string(pontos_adversario) + " CPU";
    
    escreve_texto_centralizado(texto.c_str(), 300, 20, BLACK);
}

void escreve_placar_singleplayer(int tentativas_faltantes_jogador){
    /*
    Monta o placar do jogo para mostrar na tela, no modo singleplayer.
    */
    std::string texto = "Tentativas: " + std::to_string(tentativas_faltantes_jogador);
    escreve_texto_centralizado(texto.c_str(), 400, 20, BLACK);
}

void escreve_navios_restantes(int navios_restantes){
    /*
    Monta quantos navios faltam para mostrar na tela, no modo singleplayer.
    */
    std::string texto = "Navios restantes: " + std::to_string(navios_restantes);
    escreve_texto_centralizado(texto.c_str(), 425, 20, BLACK);
}

