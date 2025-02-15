#define _POSIX_C_SOURCE 200809L
#define K 0, 0000000000899
#define G 0, 0000000000667

#include "cli.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../controllers/App.h"
#include "../models/app_components.h"
#include "../utils/hash_table.h"
#include "../utils/list.h"

void print_simulation_title(FILE *file) {
    fprintf(file, "t, px ,py ,pz ,vx ,vy ,vz ,ax ,ay ,az , fgx ,fgy ,fgz ,fex ,fey ,fez ,fx ,fy ,fz\n");  // cabeçalho do arquivo
}

void fprint_simulation_title(char *filename) {
    FILE *file = fopen(filename, "a");
    print_simulation_title(file);
    fclose(file);
}

void print_simulation_step(pSim simulation, FILE *file) {
    fprintf(file, "%d, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e\n",  // imprime os dados no arquivo
            simulation->instant_time,
            simulation->p2[0], simulation->p2[1], simulation->p2[2],
            simulation->velocidade[0], simulation->velocidade[1], simulation->velocidade[2],
            simulation->aceleracao[0], simulation->aceleracao[1], simulation->aceleracao[2],
            simulation->forca_gravitica[0], simulation->forca_gravitica[1], simulation->forca_gravitica[2],
            simulation->forca_eletrica[0], simulation->forca_eletrica[1], simulation->forca_eletrica[2],
            simulation->forca_resultante[0], simulation->forca_resultante[1], simulation->forca_resultante[2]);
}

void fprint_simulation_step(pSim simulation, char *filename) {
    FILE *file = fopen(filename, "a");
    print_simulation_step(simulation, file);
    fclose(file);
}

/**
 * @brief This function registers a user in the application if it does not exist.
 *
 * @param aplication The application.
 */
void RJ(pApp aplication) {
    char *name = strtok(NULL, " ");
    if (user_exist(aplication, name)) {
        printf("Utilizador existente.\n");

    } else {
        regist_user(aplication, name);
        printf("Utilizador registado com sucesso.\n");
    }
}

/**
 * @brief This function removes a user from the application if it exists, if he doesn't have simulation spaces with 0 simulations.
 *
 * @param aplication The application.
 */
void EJ(pApp aplication) {
    char *name = strtok(NULL, " ");
    if (user_exist(aplication, name) == false) {
        printf("Utilizador não existente.\n");

    } else if (space_with_zero_sim(aplication, name) == true) {
        printf("Utilizador tem espaços de simulação sem simulações realizadas.\n");
    } else {
        remove_user(aplication, name);
        printf("Utilizador removido com sucesso.\n");
    }
}

/**
 * @brief This function lists all users in the application in alphabetical order with their simulation spaces and simulations played.
 *
 * @param aplication The application.
 */
void LJ(pApp aplication) {
    if (hash_table_size(aplication->users) <= 0) {
        printf("Não existem utilizadores registados.\n");

    } else {
        pUser *users = users_list(aplication);
        for (int i = 0; i < hash_table_size(aplication->users); i++) {
            printf("%s %d %d\n", users[i]->name, hash_table_size(users[i]->spaces), users[i]->total_num_simulations);
        }
        free(users);
    }
}

/**
 * @brief This function registers a simulation space, wiht an id, in the user chosen by the input if it does not exist.
 *
 * @param aplication The application.
 */
void RE(pApp aplication) {
    char *name = strtok(NULL, " ");
    if (user_exist(aplication, name)) {
        int id = regist_simulation_space(aplication, name);
        printf("Espaço de simulação registado com identificador %d.\n", id);

    } else {
        printf("Utilizador inexistente.\n");
    }
}

/**
 * @brief This function removes a simulation space, from the user and the id chosen by the input if it exists.
 *
 * @param aplication The application.
 */
void EE(pApp aplication) {
    char *name = strtok(NULL, " ");
    char *identifier1 = strtok(NULL, " ");
    if (user_exist(aplication, name) == false) {
        printf("Utilizador inexistente.\n");

    } else if (space_exist(aplication, name, identifier1) == false) {
        printf("Espaço de simulação inexistente.\n");

    } else {
        remove_simulation_space(aplication, name, identifier1);
        printf("Espaço de simulação removido com sucesso.\n");
    }
}

/**
 * @brief This function registers a particle in the simulation space chosen by the input if the user and the simulation space exist.
 *
 * @param aplication The application.
 */
void RP(pApp aplication) {
    char *name = strtok(NULL, " ");
    char *identifier1 = strtok(NULL, " ");
    char *input2 = NULL;
    size_t space2 = 0;
    char *input3 = NULL;
    size_t space3 = 0;
    char *input4 = NULL;
    size_t space4 = 0;

    getline(&input2, &space2, stdin);
    input2[strlen(input2) - 1] = '\0';
    if (strlen(input2) == 0) {
        free(input2);
        return;
    }

    getline(&input3, &space3, stdin);
    input3[strlen(input3) - 1] = '\0';

    getline(&input4, &space4, stdin);
    input4[strlen(input4) - 1] = '\0';

    if (user_exist(aplication, name) == false) {
        printf("Utilizador inexistente.\n");

    } else if (space_exist(aplication, name, identifier1) == false) {
        printf("Espaço de simulação inexistente.\n");
    } else {
        int id = regist_particle(aplication, name, identifier1, input2, input3, input4);
        if (id == -1) {
            printf("Instrução inválida.\n");
        } else if (id == -2) {
            printf("Massa inválida.\n");
        } else {
            printf("Partícula registada com identificador %d.\n", id);
        }
    }
    free(input2);
    free(input3);
    free(input4);
}

/**
 * @brief This function changes a particle in the simulation space chosen by the input if the user, the simulation space and the particle exist, and removes it if the input of the position is empty.
 *
 * @param aplication The application.
 */
void AP(pApp aplication) {
    char *name = strtok(NULL, " ");
    char *identifier1 = strtok(NULL, " ");  // space
    char *identifier2 = strtok(NULL, " ");  // particle
    char *input2 = NULL;
    size_t space2 = 0;
    char *input3 = NULL;
    size_t space3 = 0;
    char *input4 = NULL;
    size_t space4 = 0;

    getline(&input2, &space2, stdin);
    input2[strlen(input2) - 1] = '\0';
    if (strlen(input2) == 0) {
        free(input2);
        return;
    }

    getline(&input3, &space3, stdin);
    input3[strlen(input3) - 1] = '\0';

    getline(&input4, &space4, stdin);
    input4[strlen(input4) - 1] = '\0';

    if (user_exist(aplication, name) == false) {
        printf("Utilizador inexistente.\n");

    } else if (space_exist(aplication, name, identifier1) == false) {
        printf("Espaço de simulação inexistente.\n");

    } else if (particle_exist(aplication, name, identifier1, identifier2) == false) {
        printf("Partícula inexistente.\n");

    } else {
        int id = change_particle(aplication, name, identifier1, identifier2, input2, input3, input4);
        if (id == -1) {
            remove_particle(aplication, name, identifier1, identifier2);
            printf("Partícula removida com sucesso.\n");
        } else if (id == -2) {
            printf("Massa inválida.\n");
        } else {
            printf("Partícula alterada com sucesso.\n");
        }
    }
    free(input2);
    free(input3);
    free(input4);
}

/**
 * @brief This function simulates the particles in the simulation space chosen by the input if the user, the simulation space and the particle exist, and the parameters are valid.
 * The simulation is printed in the terminal and in a file if the user wants.
 *
 * @param aplication The application.
 */
void S(pApp aplication, pSim simulation) {
    char *name = strtok(NULL, " ");
    char *identifier1 = strtok(NULL, " ");  // space
    char *identifier2 = strtok(NULL, " ");  // particle
    char *filename;
    char *input2 = NULL;
    size_t space2 = 0;
    char *input3 = NULL;
    size_t space3 = 0;

    getline(&input2, &space2, stdin);  // time e step_time
    input2[strlen(input2) - 1] = '\0';
    if (strlen(input2) == 0) {
        free(input2);
        return;
    }

    char *time_in_char = strtok(input2, " ");     // time
    char *step_time_in_char = strtok(NULL, " ");  // step_time

    getline(&input3, &space3, stdin);  // file
    input3[strlen(input3) - 1] = '\0';
    if (strlen(input3) == 0) {
        free(input3);
        return;
    }

    filename = strtok(input3, " ");

    if (user_exist(aplication, name) == false) {  // verificar se o user existe
        printf("Utilizador inexistente.\n");

    } else if (space_exist(aplication, name, identifier1) == false) {  // verificar se o espaço existe
        printf("Espaço de simulação inexistente.\n");

    } else {
        if ((particle_exist(aplication, name, identifier1, identifier2) == false) || (parameters(simulation, time_in_char, step_time_in_char) == true)) {  // verificar parametros
            particle_to_sim(aplication, simulation, name, identifier1, identifier2);
            print_simulation_title(stdout);

            pUser user = hash_table_get(aplication->users, name);
            pSpace space1 = hash_table_get(user->spaces, identifier1);
            FILE *file;

            if (strcmp(filename, "-") != 0) {
                file = fopen(filename, "w");
                print_simulation_title(file);
            }

            for (int i = 0; i < simulation->num_steps; i++) {  // simular
                simulation_step(simulation, space1, identifier2);
                print_simulation_step(simulation, stdout);

                if (strcmp(filename, "-") != 0) {
                    print_simulation_step(simulation, file);
                }
                simulation->instant_time += simulation->step_time;  // atualiza o tempo
            }

            space1->num_simulations++;
            user->total_num_simulations++;

            if (strcmp(filename, "-") != 0) {
                fclose(file);
            }

        } else {
            printf("Parâmetros inválidos.\n");
        }
        free(input2);
        input2 = NULL;
        free(input3);
        input3 = NULL;
    }
}

void run_cli() {
    char *input = NULL;
    size_t space = 0;
    pApp aplication = app_create();
    pSim simulation = simulation_create();
    while (true) {
        getline(&input, &space, stdin);
        input[strlen(input) - 1] = '\0';
        if (strlen(input) == 0) {
            free(input);
            break;
        }
        char *command = strtok(input, " ");

        if (strcmp(command, "RJ") == 0) {  // Registar um Utilizador
            RJ(aplication);
        } else if (strcmp(command, "EJ") == 0) {  // Remover um Utilizador
            EJ(aplication);
        } else if (strcmp(command, "LJ") == 0) {  // Mostrar a lista de users por ordem alfabética com as suas vitórias e simulaçõess jogados
            LJ(aplication);
        } else if (strcmp(command, "RE") == 0) {  // Registar um Utilizador
            RE(aplication);
        } else if (strcmp(command, "EE") == 0) {
            EE(aplication);
        } else if (strcmp(command, "RP") == 0) {
            RP(aplication);
        } else if (strcmp(command, "AP") == 0) {
            AP(aplication);
        } else if (strcmp(command, "S") == 0) {
            S(aplication, simulation);
        } else {  // Comando introdusido incorretamente
            printf("Instrução inválida.\n");
        }
        free(input);
        input = NULL;
    }
    destroy_App(aplication);
    destroy_Sim(simulation);
}
