#include <iostream>
#include <vector>
#include <raylib.h> // Lib de criacao do jogo
#include "geraEntidades.hpp"
#include "regras.hpp"
#include "canvas.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Inicializacao do jogo
    TelaJogo tela_atual = MENU;
    
    int timeout_message = 0;
    int timeout_play = 0;
    
    
    std::vector<Jogador> jogadores;
    prepara_jogo(CPU, jogadores);
    Jogador &player = jogadores[0];
    Jogador &vscpu = jogadores[1];
    coloca_navios_aleatorios(player);
    coloca_navios_aleatorios(vscpu);

    std::vector<Jogador> jogador_sozinho;
    prepara_jogo(SP, jogador_sozinho);
    Jogador &sozinho = jogador_sozinho[0];
    coloca_navios_aleatorios(sozinho);

    Botao botao_iniciar = gera_botoes("Iniciar", (largura_tela - largula_botao) / 2, 250, ESCOLHER_MODO_JOGO);
    Botao botao_sair = gera_botoes("Sair", (largura_tela - largula_botao) / 2, 400, FECHA_JOGO);
    Botao botao_singleplayer = gera_botoes("Singleplayer", (largura_tela - largula_botao) / 2, 250, SINGLEPLAYER);
    Botao botao_vsCPU = gera_botoes("Vs CPU", (largura_tela - largula_botao) / 2, 400, VSCPU);
    Botao botao_voltar = gera_botoes("Menu Inicial", (largura_tela - largula_botao) / 2, altura_tela - 100, MENU);
    
    bool gerou_estrutura_mapa = true;

    InitWindow(largura_tela, altura_tela, "Batalha Naval");
    SetTargetFPS(30);
    //--------------------------------------------------------------------------------------

    // loop principal do jogo
    while (!WindowShouldClose())    // Detecta se fechou a janela ou a tecla ESC foi apertada.
    {
        // Update das variáveis
        switch(tela_atual){
            case MENU: // Area do menu inicial do jogo
            {
                if(!gerou_estrutura_mapa){
                    jogadores.clear();
                    jogador_sozinho.clear();
                    prepara_jogo(CPU, jogadores);
                    player = jogadores[0];
                    vscpu = jogadores[1];
                    coloca_navios_aleatorios(player);
                    coloca_navios_aleatorios(vscpu);

                    prepara_jogo(SP, jogador_sozinho);
                    sozinho = jogador_sozinho[0];
                    coloca_navios_aleatorios(sozinho);

                    gerou_estrutura_mapa = true;
                }
                reage_mouse_botao(botao_iniciar, tela_atual);
                reage_mouse_botao(botao_sair, tela_atual);
                break;
            }
            case ESCOLHER_MODO_JOGO: // Area de onde escolhe o modo de jogo
            {
                reage_mouse_botao(botao_singleplayer, tela_atual);
                reage_mouse_botao(botao_vsCPU, tela_atual);
                gerou_estrutura_mapa = false;
                break;
            }
            case SINGLEPLAYER: // Area do jogo Singleplayer
            {
                if(vez_jogador){
                    interacao_mapa(sozinho);
                } if (!vez_jogador){
                    timeout_play++;
                    if(timeout_play == 10){
                        vez_jogador = true;
                        timeout_play = 0;
                    }
                }
                reage_mouse_botao(botao_voltar, tela_atual);
                
                if(sozinho.pontos == 0){
                    tela_atual = FIM_DE_JOGO_DERROTA;
                }
                if(conta_navios_restantes(sozinho) == 0){
                    tela_atual = FIM_DE_JOGO_VITORIA;
                }
                break;
            }
            case VSCPU: // Area do jogo vs CPU
            {
            if(vez_jogador){
                interacao_mapa(vscpu);
            } 
            if (!vez_jogador){
                timeout_play++;
                if(timeout_play == 75){
                    vez_jogador = true;
                    timeout_play = 0;
                }
            }
            if (!vez_jogador && timeout_play == 32){
                atira_bot(player);
                atualiza_pontuacao(player);
            } 
            reage_mouse_botao(botao_voltar, tela_atual);
            
            if(conta_navios_restantes(player) == 0){
                tela_atual = FIM_DE_JOGO_DERROTA;
                }
                if(conta_navios_restantes(vscpu) == 0){
                    tela_atual = FIM_DE_JOGO_VITORIA;
                }
                break;
            }
            case FIM_DE_JOGO_VITORIA: // Area da tela de vitoria
            {
                reage_mouse_botao(botao_voltar, tela_atual);
                break;
            }
            case FIM_DE_JOGO_DERROTA: // Area da tela de derrota
            {
                reage_mouse_botao(botao_voltar, tela_atual);
                break;
            }
            default: break;
        }

//----------------------------------------------------------------------------------

        // Desenha a tela
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(tela_atual){
            case MENU: // Tela do menu
            {
                escreve_texto_centralizado("Batalha Naval", 75, 40, BLACK);
                desenha_botao(botao_iniciar);
                desenha_botao(botao_sair);
                break;
            }
            case ESCOLHER_MODO_JOGO: // Tela de escolher modo de jogo
            {
                escreve_texto_centralizado("Batalha Naval", 75, 40, BLACK);
                desenha_botao(botao_singleplayer);
                desenha_botao(botao_vsCPU);
                break;
            }
            case SINGLEPLAYER: // Tela do modo Singleplayer
            {
                escreve_texto_centralizado("Batalha Naval", 10, 30, BLACK);
                desenha_mapa(sozinho.mapa, sozinho.eh_bot);
                escreve_placar_singleplayer(sozinho.pontos);
                escreve_navios_restantes(conta_navios_restantes(sozinho));

                if(ja_acertou){
                    escreve_texto_centralizado("Já atirou nesse alvo...", 450, 20, BLACK);
                    timeout_message++;
                    if(timeout_message == 75){
                        ja_acertou = false;
                        timeout_message = 0;
                    }
                }
            
                if(acertou_agua){
                    escreve_texto_centralizado("ÁGUA!", 450, 20, BLACK);
                    timeout_message++;
                    if(timeout_message == 75){
                        acertou_agua = false;
                        timeout_message = 0;
                    }
                }
            
                if(acertou_navio){
                    escreve_texto_centralizado("KABOOM!!", 450, 20, BLACK);
                    timeout_message++;
                    if(timeout_message == 75){
                        acertou_navio = false;
                        timeout_message = 0;
                    }
                }
                desenha_botao(botao_voltar);
                break;
            }
            case VSCPU: // Tela do modo vs CPU
            {
            
            escreve_texto_centralizado("Batalha Naval", 10, 30, BLACK);
            
            desenha_mapa(player.mapa, player.eh_bot);
            desenha_mapa(vscpu.mapa, vscpu.eh_bot);
            
            escreve_placar(player.pontos, vscpu.pontos);
            
            if(vez_jogador){
                escreve_texto_centralizado("Sua Vez...", 400, 20, BLACK);
            } else {
                escreve_texto_centralizado("Vez do adversário...", 400, 20, BLACK);
            }
            
            if(ja_acertou){
                escreve_texto_centralizado("Já atirou nesse alvo...", 450, 20, BLACK);
                timeout_message++;
                if(timeout_message == 75){
                    ja_acertou = false;
                    timeout_message = 0;
                }
            }
            
            if(acertou_agua){
                escreve_texto_centralizado("ÁGUA!", 450, 20, BLACK);
                timeout_message++;
                if(timeout_message == 75){
                    acertou_agua = false;
                    timeout_message = 0;
                }
            }
            
            if(acertou_navio){
                escreve_texto_centralizado("KABOOM!!", 450, 20, BLACK);
                timeout_message++;
                if(timeout_message == 75){
                    acertou_navio = false;
                    timeout_message = 0;
                }
            }
            desenha_botao(botao_voltar);
                break;
            }
            case FIM_DE_JOGO_VITORIA: // Tela da vitoria
            {
                escreve_texto_centralizado("VOCÊ VENCEU!", altura_tela / 2, 20, BLACK);
                desenha_botao(botao_voltar);
                break;
            }
            case FIM_DE_JOGO_DERROTA: // Tela da derrota
            {
                escreve_texto_centralizado("Você perdeu...", altura_tela / 2, 20, BLACK);
                desenha_botao(botao_voltar);
                break;
            }
            case FECHA_JOGO: // Fechando jogo
            {
                CloseWindow();
                break;
            }
            default: break;
        }
        
        EndDrawing(); // Fim do desenho da tela
    }

    // Finalizacao
    CloseWindow(); // Fecha a janela do jogo e o contexto do OpenGL 
    return 0;
}