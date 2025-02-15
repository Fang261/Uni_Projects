#define _POSIX_C_SOURCE 200809L
#define K 8.988e9
#define G 6.674e-11

#include "App.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../models/app_components.h"
#include "../utils/hash_table.h"
#include "../utils/list.h"

void destroy_App(pApp aplication) {
    hash_table_destroy(aplication->users);
    free(aplication);
}

void destroy_User(pUser user) {
    hash_table_destroy(user->spaces);
    free(user->name);
    free(user);
}

void destroy_Space(pSpace space) {
    hash_table_destroy(space->particles);
    free(space->space_identifier);
    free(space);
}

void destroy_Particle(pParticle particle) {
    free(particle->particle_identifier);
    free(particle);
}

void destroy_Sim(pSim sim) {
    free(sim);
}

pApp app_create() {
    pApp aplication = (pApp)malloc(sizeof(tApp));                                               // cria a struct app
    aplication->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void*))destroy_User);  // cria a hash table dos users
    return aplication;
}

pSim simulation_create() {
    pSim simulation = (pSim)malloc(sizeof(tSim));  // cria a struct sim
    return simulation;
}

int user_names_equal(const void* a, const void* b) {
    pUser* ua = (pUser*)a;
    pUser* ub = (pUser*)b;
    return strcmp((*ua)->name, (*ub)->name);
}

bool user_exist(pApp aplication, char* name) {  // função para saber se o player existe
    if (hash_table_get(aplication->users, name) == NULL) {
        return false;
    } else {
        return true;
    }
}

bool space_exist(pApp aplication, char* name, char* identifier1) {
    pUser user1 = hash_table_get(aplication->users, name);  // cria um user temporario
    if (hash_table_get(user1->spaces, identifier1) == NULL) {
        return false;
    } else {
        return true;
    }
}

int space_with_zero_sim(pApp aplication, char* name) {
    pUser user1 = hash_table_get(aplication->users, name);  // cria um user temporario
    pSpace space1;
    char* key = malloc(sizeof(char) * 10);
    for (int j = 1; j <= hash_table_size(user1->spaces); j++) {
        sprintf(key, "%d", j);
        space1 = hash_table_get(user1->spaces, key);
        if (space1 != NULL && space1->num_simulations == 0) {
            free(key);
            return 1;
        }
    }
    free(key);
    return 0;
}

bool particle_exist(pApp aplication, char* name, char* identifier1, char* identifier2) {
    pUser user1 = hash_table_get(aplication->users, name);  // cria um user temporario
    pSpace space1 = hash_table_get(user1->spaces, identifier1);
    if (hash_table_get(space1->particles, identifier2) == NULL) {
        return false;
    } else {
        return true;
    }
}

bool parameters(pSim simulation, char* time_in_char, char* step_time_in_char) {
    double time = atoi(time_in_char);
    double step_time = atoi(step_time_in_char);

    if (time <= 0 || step_time <= 0 || step_time > time) {  // se o tempo ou o step time forem menores ou iguais a 0 ou se o step time for maior que o tempo
        return false;
    } else {
        double num_steps = time / step_time;  // numero de steps é igual ao tempo dividido pelo step time

        simulation->simulation_time = time;  // igualar o tempo da simulação ao tempo dado pelo utilizador
        simulation->num_steps = num_steps;   // igualar o numero de steps ao numero dado pelo utilizador
        simulation->step_time = step_time;   // igualar o step time ao tempo dado pelo utilizador dividido pelo numero de steps
        simulation->instant_time = 0;        // o tempo instantaneo começa a 0
        return true;
    }
}

void particle_to_sim(pApp aplication, pSim simulation, char* name, char* identifier1, char* identifier2) {
    pUser user1 = hash_table_get(aplication->users, name);  // cria um user temporario
    pSpace space1 = hash_table_get(user1->spaces, identifier1);
    pParticle particle1 = hash_table_get(space1->particles, identifier2);

    simulation->posicao[0] = particle1->posicao_Inicial[0];
    simulation->posicao[1] = particle1->posicao_Inicial[1];
    simulation->posicao[2] = particle1->posicao_Inicial[2];
    simulation->velocidade[0] = particle1->velocidade_Inicial[0];
    simulation->velocidade[1] = particle1->velocidade_Inicial[1];
    simulation->velocidade[2] = particle1->velocidade_Inicial[2];
    simulation->aceleracao[0] = particle1->aceleracao_Inicial[0];
    simulation->aceleracao[1] = particle1->aceleracao_Inicial[1];
    simulation->aceleracao[2] = particle1->aceleracao_Inicial[2];
}

void regist_user(pApp aplication, char* name) {
    pUser user = (pUser)malloc(sizeof(tUser));  // cria a struct player
    user->name = strdup(name);                  // igualar o player name ao name
    user->spaces = hash_table_create(0, NULL, NULL, NULL, (void (*)(void*))destroy_Space);
    hash_table_insert(aplication->users, user->name, user);
}

void remove_user(pApp aplication, char* name) {
    pUser user = hash_table_remove(aplication->users, name);
    destroy_User(user);
}

pUser* users_list(pApp aplication) {
    List list = hash_table_values(aplication->users);
    pUser* users = (pUser*)list_to_array(list);
    qsort(users, list_size(list), sizeof(pUser), user_names_equal);
    list_destroy(list, NULL);
    return users;
}

int regist_simulation_space(pApp aplication, char* name) {
    pUser user1 = hash_table_get(aplication->users, name);  // cria um user temporario para poder usar a hash table space do user
    pSpace space = (pSpace)malloc(sizeof(tSpace));          // cria a struct space
    char* identifier_of_space = malloc(sizeof(char) * 10);
    user1->num_spaces_ever_registed += 1;
    int identifier_to_struct = user1->num_spaces_ever_registed;  // identificador do espaço
    sprintf(identifier_of_space, "%d", identifier_to_struct);    // converter o identificador para string

    space->particles = hash_table_create(0, NULL, NULL, NULL, (void (*)(void*))destroy_Particle);
    space->num_simulations = 0;
    space->space_identifier = strdup(identifier_of_space);
    free(identifier_of_space);
    hash_table_insert(user1->spaces, space->space_identifier, space);

    return identifier_to_struct;
}

void remove_simulation_space(pApp aplication, char* name, char* identifier1) {
    pUser user1 = hash_table_get(aplication->users, name);  // cria um user temporario
    pSpace space = hash_table_remove(user1->spaces, identifier1);
    destroy_Space(space);
}

int regist_particle(pApp aplication, char* name, char* identifier1, char* input2, char* input3, char* input4) {
    pUser user1 = hash_table_get(aplication->users, name);       // cria um user temporario
    pSpace space1 = hash_table_get(user1->spaces, identifier1);  // cria um space temporario
    pParticle particle = (pParticle)malloc(sizeof(tParticle));   // cria a struct particula

    char* char_massa = strtok(input2, " ");
    char* char_carga = strtok(NULL, " ");
    double massa = atof(char_massa);
    double carga = atof(char_carga);

    particle->massa_Particula = massa;
    particle->carga_Particula = carga;

    char* char_posicaoX = strtok(input3, " ");
    char* char_posicaoY = strtok(NULL, " ");
    char* char_posicaoZ = strtok(NULL, " ");

    if (char_posicaoX == NULL || char_posicaoY == NULL || char_posicaoZ == NULL) {
        return -1;
    }

    if (massa < 0) {
        return -2;
    }

    particle->posicao_Inicial[0] = atof(char_posicaoX);
    particle->posicao_Inicial[1] = atof(char_posicaoY);
    particle->posicao_Inicial[2] = atof(char_posicaoZ);

    if (strlen(input4) == 0) {
        particle->velocidade_Inicial[0] = 0;
        particle->velocidade_Inicial[1] = 0;
        particle->velocidade_Inicial[2] = 0;
    } else {
        char* char_velocidadeX = strtok(input4, " ");
        char* char_velocidadeY = strtok(NULL, " ");
        char* char_velocidadeZ = strtok(NULL, " ");
        particle->velocidade_Inicial[0] = atof(char_velocidadeX);
        particle->velocidade_Inicial[1] = atof(char_velocidadeY);
        particle->velocidade_Inicial[2] = atof(char_velocidadeZ);
    }

    char* identifier_of_particle = malloc(sizeof(char) * 10);
    space1->num_particles_ever_registed += 1;
    int identifier_to_struct = space1->num_particles_ever_registed;  // identificador da particula
    sprintf(identifier_of_particle, "%d", identifier_to_struct);     // converter o identificador para string

    particle->particle_identifier = strdup(identifier_of_particle);
    hash_table_insert(space1->particles, particle->particle_identifier, particle);
    free(identifier_of_particle);

    return identifier_to_struct;
}

int change_particle(pApp aplication, char* name, char* identifier1, char* identifier2, char* input2, char* input3, char* input4) {
    pUser user1 = hash_table_get(aplication->users, name);                 // cria um user temporario
    pSpace space1 = hash_table_get(user1->spaces, identifier1);            // cria um space temporario
    pParticle particle1 = hash_table_get(space1->particles, identifier2);  // cria uma particula temporaria

    char* char_massa = strtok(input2, " ");
    char* char_carga = strtok(NULL, " ");
    double massa = atof(char_massa);
    double carga = atof(char_carga);

    particle1->massa_Particula = massa;
    particle1->carga_Particula = carga;

    char* char_posicaoX = strtok(input3, " ");
    char* char_posicaoY = strtok(NULL, " ");
    char* char_posicaoZ = strtok(NULL, " ");

    if (char_posicaoX == NULL || char_posicaoY == NULL || char_posicaoZ == NULL) {
        return -1;
    }

    if (massa < 0) {
        return -2;
    }

    particle1->posicao_Inicial[0] = atof(char_posicaoX);
    particle1->posicao_Inicial[1] = atof(char_posicaoY);
    particle1->posicao_Inicial[2] = atof(char_posicaoZ);

    if (strlen(input4) == 0) {
        particle1->velocidade_Inicial[0] = 0;
        particle1->velocidade_Inicial[1] = 0;
        particle1->velocidade_Inicial[2] = 0;
    } else {
        char* char_velocidadeX = strtok(input4, " ");
        char* char_velocidadeY = strtok(NULL, " ");
        char* char_velocidadeZ = strtok(NULL, " ");
        particle1->velocidade_Inicial[0] = atof(char_velocidadeX);
        particle1->velocidade_Inicial[1] = atof(char_velocidadeY);
        particle1->velocidade_Inicial[2] = atof(char_velocidadeZ);
    }

    hash_table_update(space1->particles, identifier2, particle1);

    return 0;
}

void remove_particle(pApp aplication, char* name, char* identifier1, char* identifier2) {
    pUser user1 = hash_table_get(aplication->users, name);                    // cria um user temporario
    pSpace space1 = hash_table_get(user1->spaces, identifier1);               // cria um space temporario
    pParticle particle1 = hash_table_remove(space1->particles, identifier2);  // cria uma particula temporaria
    destroy_Particle(particle1);
}

void simulation_step(pSim simulation, pSpace space1, char* identifier2) {
    pParticle particle1 = hash_table_get(space1->particles, identifier2);  // cria uma particula temporaria
    pParticle particle2;
    int identifier_to_compare = atoi(identifier2);

    double px = simulation->posicao[0];         // posição em x
    double py = simulation->posicao[1];         // posição em y
    double pz = simulation->posicao[2];         // posição em z
    double vx = simulation->velocidade[0];      // velocidade em x
    double vy = simulation->velocidade[1];      // velocidade em y
    double vz = simulation->velocidade[2];      // velocidade em z
    double ax = 0;  // aceleração em x
    double ay = 0;  // aceleração em y
    double az = 0;  // aceleração em z

    double dx = 0;  // distancia em x
    double dy = 0;  // distancia em y
    double dz = 0;  // distancia em

    double fgx = 0;  // força gravitacional em x
    double fgy = 0;  // força gravitacional em y
    double fgz = 0;  // força gravitacional em z
    double fex = 0;  // força elétrica em x
    double fey = 0;  // força elétrica em y
    double fez = 0;  // força elétrica em z

    double fx = 0;  // força resultante em x
    double fy = 0;  // força resultante em y
    double fz = 0;  // força resultante em z

    char key[80];
    for (int i = 1; i <= hash_table_size(space1->particles); i++) {
        sprintf(key, "%d", i);
        if (i != identifier_to_compare || hash_table_get(space1->particles, key) == NULL) {
            particle2 = hash_table_get(space1->particles, key);  // cria uma segunda particula temporaria

            dx = px - particle2->posicao_Inicial[0];  // calcula a distancia em x
            dy = py - particle2->posicao_Inicial[1];  // calcula a distancia em y
            dz = pz - particle2->posicao_Inicial[2];  // calcula a distancia em z

            fgx += (dx == 0) ? 0 : (G * (particle1->massa_Particula) * (particle2->massa_Particula) / pow(dx, 2));
            fgy += (dy == 0) ? 0 : (G * (particle1->massa_Particula) * (particle2->massa_Particula) / pow(dy, 2));
            fgz += (dz == 0) ? 0 : (G * (particle1->massa_Particula) * (particle2->massa_Particula) / pow(dz, 2));

            fex += (dx == 0) ? 0 : -(K * (particle1->carga_Particula) * (particle2->carga_Particula) / pow(dx, 2));
            fey += (dy == 0) ? 0 : -(K * (particle1->carga_Particula) * (particle2->carga_Particula) / pow(dy, 2));
            fez += (dz == 0) ? 0 : -(K * (particle1->carga_Particula) * (particle2->carga_Particula) / pow(dz, 2));
        }
    }

    fx = fgx + fex;  // calcula a força resultante em x
    fy = fgy + fey;  // calcula a força resultante em y
    fz = fgz + fez;  // calcula a força resultante em z

    ax = (particle1->massa_Particula == 0) ? 0 : fx / particle1->massa_Particula;  // calcula a aceleração em x
    ay = (particle1->massa_Particula == 0) ? 0 : fy / particle1->massa_Particula;  // calcula a aceleração em y
    az = (particle1->massa_Particula == 0) ? 0 : fz / particle1->massa_Particula;  // calcula a aceleração em z

    if (simulation->instant_time != 0) {
    vx = vx + (ax * simulation->step_time);  // calcula a velocidade em x
    vz = vz + (az * simulation->step_time);  // calcula a velocidade em z
    vy = vy + (ay * simulation->step_time);  // calcula a velocidade em y
    }

    simulation->p2[0] = simulation->posicao[0];
    simulation->p2[1] = simulation->posicao[1];
    simulation->p2[2] = simulation->posicao[2];

    px = px + (vx * simulation->step_time) + ((ax * pow(simulation->step_time, 2)) / 2);  // calcula a posição em x
    py = py + (vy * simulation->step_time) + ((ay * pow(simulation->step_time, 2)) / 2);  // calcula a posição em y
    pz = pz + (vz * simulation->step_time) + ((az * pow(simulation->step_time, 2)) / 2);  // calcula a posição em z

    simulation->posicao[0] = px;  // atualiza a posição
    simulation->posicao[1] = py;  // atualiza a posição
    simulation->posicao[2] = pz;  // atualiza a posição

    simulation->velocidade[0] = vx;  // atualiza a velocidade
    simulation->velocidade[1] = vy;  // atualiza a velocidade
    simulation->velocidade[2] = vz;  // atualiza a velocidade
    simulation->aceleracao[0] = ax;  // atualiza a aceleração
    simulation->aceleracao[1] = ay;  // atualiza a aceleração
    simulation->aceleracao[2] = az;  // atualiza a aceleração

    simulation->forca_gravitica[0] = fgx;  // atualiza a força gravitacional
    simulation->forca_gravitica[1] = fgy;  // atualiza a força gravitacional
    simulation->forca_gravitica[2] = fgz;  // atualiza a força gravitacional
    simulation->forca_eletrica[0] = fex;   // atualiza a força elétrica
    simulation->forca_eletrica[1] = fey;   // atualiza a força elétrica
    simulation->forca_eletrica[2] = fez;   // atualiza a força elétrica
    simulation->forca_resultante[0] = fx;  // atualiza a força resultante
    simulation->forca_resultante[1] = fy;  // atualiza a força resultante
    simulation->forca_resultante[2] = fz;  // atualiza a força resultante
}