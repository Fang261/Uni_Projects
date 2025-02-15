#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numpl;

typedef struct
{  // jogador
    char name[128];
    int gamesplayed;
    int wins;
    int *specas_do_player;    // peças especiais do player
    int num_specialp_player;  // numero de peças especiais do player
} tplayer, *pplayer;

typedef struct
{  // jogo
    pplayer *players;
    int numerop;
    pplayer player1;
    pplayer player2;
    bool run;
    int comprimento;
    int altura;
    int tamsequencia;
    int *specas;       // peças especiais
    int num_specialp;  // numero de peças especiais
    pplayer **board;
} tjogo, *pjogo;

pplayer get_player(pjogo game, char *name) {  // função para obter o  player
    for (int i = 0; i < game->numerop; i++) {
        if (strcmp(game->players[i]->name, name) == 0) {
            return game->players[i];
        }
    }
}

bool player_exist(pjogo game, char *name) {  // função para saber se o player existe
    for (int i = 0; i < game->numerop; i++) {
        if (strcmp(game->players[i]->name, name) == 0) {
            return true;
        }
    }

    return false;
}

int get_player_position(pjogo game, char *name) {  // função para obter a posiçâo do player no array
    for (int i = 0; i < game->numerop; i++) {
        if (strcmp(game->players[i]->name, name) == 0) {
            return i;
        }
    }
}

bool engenharia_das_pecas(pjogo game) {  // verificação se as peças cumprem os parâmetros :)
    int confirmer = 0;

    if (game->specas[0] <= 0) {
        return true;
    }

    for (int i = 0; i < game->num_specialp; i++) {
        if ((game->specas[i] > 0) && (game->specas[i] < game->tamsequencia)) {
            confirmer++;
        }
    }

    if (confirmer == game->num_specialp) {  // se o confirmar for igual ao strlen do array significa que todas as peças especiais cumprem os parametros requisitados
        return true;
    } else {
        return false;
    }
}

void print_players(pjogo game) {
    for (int i = 0; i < game->numerop; i++) {
        printf("%s %d %d\n", game->players[i]->name, game->players[i]->gamesplayed, game->players[i]->wins);
    }
}

void organizar_pecas(pjogo game) {
    for (int i = 0; i < game->num_specialp; i++) {
        numpl = 1;  // variável onde se começa a verificação, não se quer pegar sempre na peça da posição dois mas sim sempre uma para a frente
        for (int j = 0; j < game->num_specialp - i - 1; j++) {
            if (game->specas[j] > game->specas[j + 1]) {
                int varnp = game->specas[numpl];  // variavel para guardar a posição que vai ser substituida
                game->specas[numpl] = game->specas[j];
                game->specas[j] = varnp;
            }
            numpl++;
        }
    }
}

int *leitor_de_pecas(pjogo game, int *contador) {  // return arr de peças dif e de
    int *tipo_pecas = NULL;
    *contador = 0;
    if (game->num_specialp > 0) {
        tipo_pecas = malloc(sizeof(int));
        tipo_pecas[0] = game->specas[0];
        *contador = 1;

        for (int i = 0; i < game->num_specialp - 1; i++) {
            if (game->specas[i] != game->specas[i + 1]) {
                *contador++;
                tipo_pecas = realloc(tipo_pecas, sizeof(int) * *contador);
                tipo_pecas[*contador - 1] = game->specas[i];
            }
        }

        if (game->specas[game->num_specialp - 2] != game->specas[game->num_specialp - 1]) {
            *contador++;
            tipo_pecas = realloc(tipo_pecas, sizeof(int) * *contador);
            tipo_pecas[*contador - 1] = game->specas[game->num_specialp - 1];
        }
    }
    return tipo_pecas;
}

bool peca_valida(pjogo game, char *name, char *input_peca) {
    int peca = atoi(input_peca);
    pplayer player = get_player(game, name);
    if (peca != 1) {
        for (int i = 0; i < player->num_specialp_player; i++) {
            if (peca == player->specas_do_player[i]) {
                return true;
            }
        }
        return false;
    } else {
        return true;
    }
}

void checkwin(pjogo game, char *name) {
    int wincond = 0;
    bool won = false;
    for (int i = 0; i < game->altura; i++) {
        for (int j = 0; j < game->comprimento; j++) {
            if (game->board[i][j] == NULL) {
                wincond = 0;
            } else if (strcmp(game->board[i][j]->name, name) == 0) {
                wincond++;
            } else {
                wincond = 0;
            }
            if (wincond == game->tamsequencia) {
                won = true;
            }
        }
    }
    if (won == false) {  // se não ganhou na horizontal
        for (int k = 0; k < game->comprimento; k++) {
            for (int l = 0; l < game->altura; l++) {
                if (game->board[l][k] == NULL) {
                    wincond = 0;
                } else if (strcmp(game->board[l][k]->name, name) == 0) {
                    wincond++;
                } else {
                    wincond = 0;
                }
                if (wincond == game->tamsequencia) {
                    won = true;
                    break;
                }
            }
        }
    }

    if (won == false) {                                    // se não ganhou na vertical nem na horizontal
        for (int m = game->altura - 1; m >= 0; m--) {      // encontrar uma peça no jogo
            for (int n = 0; n < game->comprimento; n++) {  //
                if (game->board[m][n] == NULL) {
                    wincond = 0;
                } else if (strcmp(game->board[m][n]->name, name) == 0) {  // ver se a peça no jogo é do player introduzido
                    wincond = 1;
                    int p = m - 1;  // para o for, começar a verificar se a peça na diagonal é do mesmo player
                    for (int o = (n + 1); o < game->comprimento; o++) {
                        if (p >= 0 && game->board[p][o] == NULL) {
                            wincond = 0;
                        } else if (p >= 0 && strcmp(game->board[p][o]->name, name) == 0) {
                            wincond++;
                        } else if (wincond == game->tamsequencia) {
                            won = true;
                        } else {
                            wincond = 0;
                        }
                        p--;
                    }
                    p = m - 1;
                    wincond = 1;
                    for (int q = (m - 1); q >= 0; q--) {
                        if (q >= 0 && p >= 0 && game->board[q][p] == NULL) {
                            wincond = 0;
                        } else if (q >= 0 && p >= 0 && strcmp(game->board[q][p]->name, name) == 0) {
                            wincond++;
                        } else if (wincond == game->tamsequencia) {
                            won = true;
                        } else {
                            wincond = 0;
                        }
                        p--;
                    }
                }
            }
        }
    }

    if (won == true) {
        printf("Sequência conseguida. Jogo terminado.\n");
        if (strcmp(game->player1->name, name) == 0) {
            game->player1->wins++;
        } else {
            game->player2->wins++;
        }
        game->run = false;
        game->player1->gamesplayed++;
        game->player2->gamesplayed++;
        game->run = false;
        game->player1 = NULL;
        game->player2 = NULL;
        game->specas = NULL;
        free(game->specas);
        game->num_specialp = 0;
        game->comprimento = 0;
        game->altura = 0;
        game->tamsequencia = 0;
    } else {
        printf("Peça colocada.\n");
    }
}

void registar_jogador(pjogo game, char *name) {
    pplayer player = (pplayer)malloc(sizeof(tplayer));  // cria a struct player com o tamanho de p variavel
    strcpy(player->name, name);                         // igualar o player name ao name
    player->wins = 0;                                   //
    player->gamesplayed = 0;                            //

    game->numerop++;                                                            //
    game->players = realloc(game->players, (sizeof(pplayer) * game->numerop));  // mais um espaco para players na memoria
    game->players[game->numerop - 1] = player;                                  // guardaer player no array players
}

void remover_jogador(pjogo game, char *name) {
    int arrfixer = get_player_position(game, name);
    free(game->players[arrfixer]);
    for (int j = arrfixer; j < game->numerop - 1; j++) {  // função para tirar o espaço vazio do array
        game->players[j] = game->players[j + 1];
    }
    game->players[game->numerop - 1] = NULL;
    game->numerop--;
    game->players = realloc(game->players, sizeof(pplayer) * game->numerop);  // menos um espaco para players na memoria
}

void start_game(pjogo game, char *name, char *name2) {
    size_t space2 = 0;
    int ticktack_confirm = 0;
    char *input = NULL;

    getline(&input, &space2, stdin);  // segunda linha
    char *comp = strtok(input, " ");
    char *alt = strtok(NULL, " ");
    char *tamseq = strtok(NULL, " ");
    game->comprimento = atoi(comp);
    game->altura = atoi(alt);
    game->tamsequencia = atoi(tamseq);
    free(input);
    input = NULL;

    getline(&input, &space2, stdin);  // terceira linha
    game->num_specialp = 0;
    char *specialp = strtok(input, " ");
    while (specialp != NULL) {
        game->num_specialp++;
        game->specas = realloc(game->specas, sizeof(int) * game->num_specialp);
        game->specas[game->num_specialp - 1] = atoi(specialp);
        specialp = strtok(NULL, " ");
    }
    free(input);

    if (game->run == true) {
        printf("Existe um jogo em curso.\n");
    } else if ((player_exist(game, name) == false) || (player_exist(game, name2) == false)) {
        printf("Jogador não registado.\n");
    } else if ((game->comprimento <= 0) || ((game->comprimento / 2) > game->altura) || (game->altura > game->comprimento)) {
        printf("Dimensões de grelha inválidas.\n");
    } else if ((game->tamsequencia <= 0) || (game->tamsequencia >= game->comprimento)) {
        printf("Tamanho de sequência inválido.\n");
    } else if (engenharia_das_pecas(game) == false) {
        printf("Dimensões de peças especiais inválidas.\n");
    } else {
        organizar_pecas(game);

        if (strcmp(name, name2) < 0) {
            game->player1 = get_player(game, name);
            game->player2 = get_player(game, name2);
        } else {
            game->player1 = get_player(game, name2);
            game->player2 = get_player(game, name);
        }

        game->player1->specas_do_player = malloc(sizeof(int) * game->num_specialp);
        game->player1->num_specialp_player = game->num_specialp;
        memcpy(game->player1->specas_do_player, game->specas, sizeof(int) * game->num_specialp);

        game->player2->specas_do_player = malloc(sizeof(int) * game->num_specialp);
        game->player2->num_specialp_player = game->num_specialp;
        memcpy(game->player2->specas_do_player, game->specas, sizeof(int) * game->num_specialp);

        game->board = malloc(sizeof(pplayer *) * game->altura);
        for (int i = 0; i < game->altura; i++) {
            game->board[i] = malloc(sizeof(pplayer) * game->comprimento);
        }

        game->run = true;

        printf("Jogo iniciado entre %s e %s.\n", game->player1->name, game->player2->name);
    }
}

void player_list(pjogo game) {
    for (int i = 0; i < game->numerop - 1; i++) {      //
        numpl = 1;                                     // variável onde se começa a verificação, não se quer pegar sempre no player da posição dois mas sim sempre um para a frente
        for (int j = 0; j < game->numerop - 1; j++) {  //
            if (strcmp(game->players[j]->name, game->players[numpl]->name) > 0) {
                pplayer varpl = game->players[numpl];  // struct para guardar a posição que vai ser substituida
                game->players[numpl] = game->players[j];
                game->players[j] = varpl;
            }
            numpl++;
        }
    }
}

void desistir(pjogo game, char *name, char *name2) {
    bool check = false;
    if (name2 == NULL) {
        if ((strcmp(game->player1->name, name) != 0 && strcmp(game->player2->name, name) != 0)) {
            printf("Jogador não participa no jogo em curso.\n");
            return;
        }

    } else if (name2 != NULL) {
        if ((strcmp(game->player1->name, name) != 0 && strcmp(game->player1->name, name2) != 0) || (strcmp(game->player2->name, name) != 0 && strcmp(game->player2->name, name2) != 0)) {
            printf("Jogador não participa no jogo em curso.\n");
            return;
        }
        check = true;
    }
    if ((strcmp(game->player1->name, name) == 0) && (strcmp(game->player2->name, name) == 0) || (strcmp(game->player2->name, name) == 0) && (strcmp(game->player1->name, name) == 0)) {
    } else if (check == false && strcmp(game->player1->name, name) == 0) {  // player1 desiste e player2 ganha
        get_player(game, game->player2->name)->wins++;

    } else if (check == false && strcmp(game->player2->name, name) == 0) {  // player2 desiste e p1 ganha
        get_player(game, game->player1->name)->wins++;
    }

    game->player1->gamesplayed++;
    game->player2->gamesplayed++;

    game->run = false;
    game->player1 = NULL;
    game->player2 = NULL;
    game->specas = NULL;
    free(game->specas);
    game->num_specialp = 0;
    game->comprimento = 0;
    game->altura = 0;
    game->tamsequencia = 0;
    printf("Desistência com sucesso. Jogo terminado.\n");
}

void game_details(pjogo game) {
    int contador;
    int *tipo_pecas = leitor_de_pecas(game, &contador);

    printf("%d %d\n", game->comprimento, game->altura);

    printf("%s\n", game->player1->name);
    for (int i = 0; i <= contador; i++) {
        int num_repeticoes = 0;
        for (int j = 0; j < game->player1->num_specialp_player; j++) {
            if (tipo_pecas[i] == game->player1->specas_do_player[j]) {
                num_repeticoes++;
            }
        }
        printf("%d %d\n", tipo_pecas[i], num_repeticoes);
    }

    printf("%s\n", game->player2->name);
    for (int i = 0; i < contador; i++) {
        int num_repeticoes = 0;
        for (int j = 0; j < game->player2->num_specialp_player; j++) {
            if (tipo_pecas[i] == game->player2->specas_do_player[j]) {
                num_repeticoes++;
            }
        }
        printf("%d %d\n", tipo_pecas[i], num_repeticoes);
    }
}

void visualizar_resultado(pjogo game) {
    if (game->run == false) {
        printf(" Não existe jogo em curso.\n");
    }
    for (int i = 0; i < game->altura; i++) {  // altura = linha, comprimento = coluna
        for (int j = 0; j < game->comprimento; j++) {
            printf("%d %d ", i + 1, j + 1);
            if (game->board[i][j] == NULL) {
                printf("Vazio\n");
            } else if (strcmp(game->board[i][j]->name, game->player1->name) == 0) {
                printf("%s\n", game->player1->name);
            } else if (strcmp(game->board[i][j]->name, game->player2->name) == 0) {
                printf("%s\n", game->player2->name);
            }
        }
    }
}

void colocar_peca_tamanho_1(pjogo game, char *name, char *input_posicao) {
    int posicao = atoi(input_posicao);                                                             //[altura][compriento]
    if (game->board[0][posicao - 1] == NULL) {                                                     // altura = arr em forma de coluna, comprimento = arr em forma de linha
        for (int i = 0; i < game->altura - 1; i++) {                                               // peca a ser colocada
            if (game->board[i][posicao - 1] == NULL && game->board[i + 1][posicao - 1] != NULL) {  // ve tudo até aá penultima linha
                game->board[i][posicao - 1] = get_player(game, name);                              // nome do jogador a servir de peça
                checkwin(game, name);
                return;
            }
        }
        game->board[game->altura - 1][posicao - 1] = get_player(game, name);  // peca numa linha vazia
        checkwin(game, name);
    } else {
        printf("Posição irregular.\n");
    }
}

void retirar_peca_especial(pjogo game, char *name, int peca) {
    int po = get_player_position(game, name);
    game->players[po]->num_specialp_player--;

    for (int i = 0; i < game->players[po]->num_specialp_player; i++) {
        if (game->specas[i] == peca) {
            for (int j = i; j < game->players[po]->num_specialp_player - 1; j++) {
                game->players[po]->specas_do_player[j] = game->players[po]->specas_do_player[j + 1];
                return;
            }
        }
    }
}

void colocar_peca_especial(pjogo game, char *name, int posicao, int peca) {
    if (peca && game->board[0][posicao - 1] == NULL) {                                             // altura = arr em forma de coluna, comprimento = arr em forma de linha  //[altura][compriento]
        for (int i = 0; i < game->altura - 1; i++) {                                               // peca a ser colocada
            if (game->board[i][posicao - 1] == NULL && game->board[i + 1][posicao - 1] != NULL) {  // ve tudo até aá penultima linha
                game->board[i][posicao - 1] = get_player(game, name);                              // nome do jogador a servir de peça
                return;
            }
        }
        game->board[game->altura - 1][posicao - 1] = get_player(game, name);  // peca numa linha vazia
    }
}

void tabuleiro(pjogo game) {
    for (int i = 0; i < game->altura; i++) {  // altura = arr em forma de coluna, comprimento = arr em forma de linha
        for (int j = 0; j < game->comprimento; j++) {
            if (game->board[i][j]->name == NULL) {
                printf("0 ");
            } else if (strcmp(game->board[i][j]->name, game->player1->name) == 0) {
                printf("1 ");  // print se a posição tiver o p1
            } else if (strcmp(game->board[i][j]->name, game->player2->name) == 0) {
                printf("2 ");  // print se a posição tiver o p2
            }
        }
        printf("\n");
    }
}

// void save(pjogo game) {
//     FILE *save;
//     save = fopen("data.txt", "w");  // definir o tipo de ação do ficheiro (wb) e o nome (data.txt)
//
//     for (int i = 0; i < game->numerop; i++){
//         fprintf(save, "%s\n", game->players[i]->name);
//         fprintf(save, "%d\n", game->players[i]->gamesplayed);
//         fprintf(save, "%d\n", game->players[i]->wins);
//         fprintf(save, "%d\n", game->players[i]->num_specialp_player);
//         for (int i = 0; i < game->players[i]->num_specialp_player; i++) {
//             fprintf(save, "%d\n", game->players[i]->specas_do_player[i]);
//         }
//     }
//
//     if (game->run == true) {
//         fprintf(save, "1\n");
//         fprintf(save, "%d\n", game->numerop);
//         fprintf(save, "%s\n", game->player1->name);
//         fprintf(save, "%s\n", game->player2->name);
//         fprintf(save, "%d\n", game->altura);
//         fprintf(save, "%d\n", game->comprimento);
//
//         for (int i = 0; i < game->altura; i++) {
//             for (int j = 0; j < game->comprimento; j++) {
//                 if (game->board[i][j] == NULL) {
//                     fprintf(save, "0\n");
//                 } else if (strcmp(game->board[i][j]->name, game->player1->name) == 0) {
//                     fprintf(save, "1\n");
//                 } else if (strcmp(game->board[i][j]->name, game->player2->name) == 0) {
//                     fprintf(save, "2\n");
//                 }
//             }
//         }
//
//     } else {
//         fprintf(save, "%d\n", game->numerop);
//         fprintf(save, "0\n");
//     }
//
//     // fwrite(game->players, sizeof(tplayer) * game->numerop, 1, save);  // guardar o numero de players
//     // for (int i = 0; i < game->numerop; i++) {
//     //     fwrite(game->players[i]->name, sizeof(char) * 128, 1, save);                                               // guardar o nome do player
//     //     fwrite(&game->players[i]->gamesplayed, sizeof(int), 1, save);                                              // guardar o numero de jogos jogados
//     //     fwrite(&game->players[i]->wins, sizeof(int), 1, save);                                                     // guardar o numero de vitorias
//     //     fwrite(game->players[i]->specas_do_player, sizeof(int) * game->players[i]->num_specialp_player, 1, save);  // guardar o numero de pecas especiais do player
//     //     fwrite(&game->players[i]->num_specialp_player, sizeof(int), 1, save);
//     // }
//     // fwrite(&game->numerop, sizeof(int), 1, save);                         // guardar o numero de jogadores
//     // fwrite(&game->run, sizeof(bool), 1, save);                            // se o jogo está a correr ou não
//     // if (game->run == true) {                                              // se o jogo estiver a correr
//     //     fwrite(game->player1, sizeof(tplayer), 1, save);                  // escrever o jogador 1
//     //     fwrite(game->player2, sizeof(tplayer), 1, save);                  // guardar o jogador 2
//     //     fwrite(&game->comprimento, sizeof(int), 1, save);                 // guardar o comprimento do tabuleiro
//     //     fwrite(&game->altura, sizeof(int), 1, save);                      // guardar a altura do tabuleiro
//     //     fwrite(&game->tamsequencia, sizeof(int), 1, save);                // guardar o tamanho da sequencia
//     //     fwrite(game->specas, sizeof(int) * game->num_specialp, 1, save);  // guardar as pecas especiais
//     //     fwrite(&game->num_specialp, sizeof(int), 1, save);                // guardar o numero de pecas especiais
//     //     for (int j = 0; j < game->num_specialp; j++) {
//     //         fwrite(&game->specas[j], sizeof(int), 1, save);  // guardar as pecas especiais
//     //     }
//     //     fwrite(game->board, sizeof(pplayer) * game->altura * game->comprimento, 1, save);  // guardar o tabuleiro
//     //     for (int l = 0; l < game->altura; l++) {
//     //         fwrite(game->board[l], sizeof(int), game->comprimento, save);  // guardar o tabuleiro
//     //     }
//     // }
//     printf("Jogo gravado.\n");
//
//     fclose(save);
// }
//
// pjogo load(pjogo game) {
//     FILE *load;
//     load = fopen("data.bin", "rb");  // definir o tipo de ação do ficheiro (rb) e o nome (data.txt)
//
//     // for (int i = 0; i < game->altura; i++) {  // altura = arr em forma de coluna, comprimento = arr em forma de linha
//     //     for (int j = 0; j < game->comprimento; j++) {
//     //         free(game->board[i][j]);
//     //     }
//     //
//     //    for (int i = 0; i < game->numerop; i++) {
//     //        free(game->players[i]);
//     //    }
//     //
//     //    free(game->board);
//     //    free(game->players);
//     //    free(game);
//     //
//     //    pjogo game = malloc(sizeof(tjogo));
//     //
//     //    fread(game->players, sizeof(tplayer) * game->numerop, 1, load);
//     //    for (int i = 0; i < game->numerop; i++) {
//     //        // char
//     //        fread(&game->players[i]->gamesplayed, sizeof(int), 1, load);                                              // int
//     //        fread(&game->players[i]->wins, sizeof(int), 1, load);                                                     // int
//     //        fread(game->players[i]->specas_do_player, sizeof(int) * game->players[i]->num_specialp_player, 1, load);  // int
//     //        fread(&game->players[i]->num_specialp_player, sizeof(int), 1, load);                                      // int
//     //    }
//     //    fread(&game->numerop, sizeof(int), 1, load);  // int
//     //    fread(&game->run, sizeof(bool), 1, load);     // bool
//     //    if (game->run == true) {
//     //        fread(game->player1, sizeof(tplayer), 1, load);                  // tplayer
//     //        fread(game->player2, sizeof(tplayer), 1, load);                  // tplayer
//     //        fread(&game->comprimento, sizeof(int), 1, load);                 // int
//     //        fread(&game->altura, sizeof(int), 1, load);                      // int
//     //        fread(&game->tamsequencia, sizeof(int), 1, load);                // int
//     //        fread(game->specas, sizeof(int) * game->num_specialp, 1, load);  // int
//     //        fread(&game->num_specialp, sizeof(int), 1, load);                // int
//     //        for (int j = 0; j < game->num_specialp; j++) {
//     //            fread(&game->specas[j], sizeof(int), 1, load);  // int
//     //        }
//     //        fread(game->board, sizeof(tplayer) * game->altura * game->comprimento, 1, load);  // tplayer
//     //        for (int l = 0; l < game->altura; l++) {
//     //            fread(game->board[l], sizeof(int), game->comprimento, load);  // int
//     //        }
//     //    }
//     //    return game;
//     //}
//     printf("Jogo carregado.\n");
// }

int main() {
    char *input = NULL;
    size_t space = 0;
    pjogo game = malloc(sizeof(tjogo));
    game->players = NULL;
    game->run = false;
    game->numerop = 0;
    while (0 == 0) {
        getline(&input, &space, stdin);
        input[strlen(input) - 1] = '\0';
        if (strlen(input) == 0) {
            free(input);
            break;
        }
        char *command = strtok(input, " ");
        char *name = strtok(NULL, " ");

        if (strcmp(command, "RJ") == 0) {  // Registar um jogador
            if (player_exist(game, name)) {
                printf("Jogador existente.\n");

            } else {
                registar_jogador(game, name);
                printf("Jogador registado com sucesso.\n");
            }
        } else if (strcmp(command, "EJ") == 0) {  // Remover um jogador
            if (player_exist(game, name) == false) {
                printf("Jogador não existente.\n");

            } else if (game->run == true && (strcmp(name, game->player1->name) == 0 || strcmp(name, game->player2->name) == 0)) {
                printf("\nJogador participa no jogo em curso.\n");

            } else {
                remover_jogador(game, name);
                printf("Jogador removido com sucesso.\n");
            }
        } else if (strcmp(command, "IJ") == 0) {  // Iniciar jogo
            char *name2 = strtok(NULL, " ");
            start_game(game, name, name2);
        } else if (strcmp(command, "LJ") == 0) {  // Mostrar a lista de jogadores por ordem alfabética com as suas vitórias e jogos jogados
            if (game->numerop <= 0) {
                printf("Não existem jogadores registados.\n");

            } else {
                player_list(game);
                print_players(game);
            }

        } else if (strcmp(command, "D") == 0) {  // desistir jogador
            char *name2 = NULL;
            name2 = strtok(NULL, " ");
            if (game->run != true) {
                printf("Não existe jogo em curso.\n");

            } else {
                desistir(game, name, name2);
            }
        } else if (strcmp(command, "DJ") == 0) {  // Iniciar jogo
            if (game->run) {                      // se o jogo estiver a correr
                game_details(game);               // mostrar detalhes do jogo
            } else {
                printf("Não existe jogo em curso.\n");
            }
        } else if (strcmp(command, "CP") == 0) {  // Colocar peça
            char *input_peca = strtok(NULL, " ");
            char *input_posicao = strtok(NULL, " ");
            int posicao = atoi(input_posicao);
            int peca = atoi(input_peca);
            if (game->run == false) {
                printf("Não existe jogo em curso.\n");
            } else if ((strcmp(game->player1->name, name) != 0) && (strcmp(game->player2->name, name) != 0)) {
                printf("Jogador não participa no jogo em curso.\n");
            } else if (peca_valida(game, name, input_peca) == false || peca < 0 || peca > game->tamsequencia) {
                printf("Tamanho de peça não disponível.\n");
            } else if (posicao < 0 || posicao > game->comprimento) {
                printf("Posição irregular.\n");
            } else if (peca == 1) {
                colocar_peca_tamanho_1(game, name, input_posicao);
            } else {
                char *sentido = strtok(NULL, " ");
                if (strcmp(sentido, "D") == 0 && (posicao + (peca - 1) <= game->comprimento)) {
                    int confirmer = 0;
                    for (int i = 0; i < peca; i++) {
                        if (posicao <= game->comprimento && game->board[0][posicao - 1] == NULL) {
                            posicao++;
                            confirmer++;
                        }
                    }
                    posicao -= peca;
                    if (confirmer == peca) {
                        for (int i = 0; i < peca; i++) {
                            colocar_peca_especial(game, name, posicao, peca);
                            posicao++;
                        }
                        retirar_peca_especial(game, name, peca);
                        checkwin(game, name);
                    } else {
                        printf("Posição irregular.\n");
                    }
                } else if (strcmp(sentido, "E") == 0 && (posicao - (peca - 1) >= 0)) {
                    int confirmer = 0;
                    for (int i = 0; i < peca; i++) {
                        if (posicao >= 0 && game->board[0][posicao - 1] == NULL) {
                            posicao--;
                            confirmer++;
                        }
                    }
                    posicao += peca;
                    if (confirmer == peca) {
                        for (int i = 0; i < peca; i++) {
                            colocar_peca_especial(game, name, posicao, peca);
                            posicao--;
                        }
                        retirar_peca_especial(game, name, peca);
                        checkwin(game, name);
                    } else {
                        printf("Posição irregular.\n");
                    }
                } else {
                    printf("Posição irregular.\n");
                }
            }
        } else if (strcmp(command, "VR") == 0) {
            if (game->run == false) {
                printf("Não existe jogo em curso.\n");
            } else {
                visualizar_resultado(game);
            }
        } else if (strcmp(command, "X") == 0) {
            if (game->run == false) {
                printf("Não existe jogo em curso.\n");
            } else {
                tabuleiro(game);
            }
        } else if (strcmp(command, "G") == 0) {  // Gravar o jogo
            // save(game);
        } else if (strcmp(command, "L") == 0) {  // Dar load ao jogo anteriormente gravado
            // load(game);
        } else {  // Comando introdusido incorretamente
            printf("Instrução inválida.\n");
        }
    }

    for (int i = 0; i < game->numerop; i++) {
        free(game->players[i]);
    }

    free(game->players);
    free(game);

    return 0;
}

// JOÃO MONIZ 20220550
// TIAGO ESTRELA 20220534
// TOMÁS SALGUEIRO 20220589