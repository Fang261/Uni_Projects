#ifndef APP_COMPONENTS
#define APP_COMPONENTS

#include "../utils/hash_table.h"
#include "../utils/list.h"

typedef struct {      // Aplicação
    char *name;  
    HashTable spaces;
    int num_spaces_ever_registed;
    int total_num_simulations;
} tUser, *pUser;

typedef struct {  // espaço de simulação
    HashTable particles;
    char* space_identifier;
    int num_simulations;
    int num_particles;
    int num_particles_ever_registed;
} tSpace, *pSpace;

typedef struct {  // partícula
    char* particle_identifier;
    double carga_Particula;
    double massa_Particula;
    double posicao_Inicial[3];  // vector de 3 posições
    double velocidade_Inicial[3];
    double aceleracao_Inicial[3];
} tParticle, *pParticle;

typedef struct {  // simulação
    int simulation_time;
    int num_steps;
    int step_time;
    int instant_time;  // t
    double posicao[3];    // vector de 3 posições
    double p2[3];
    double velocidade[3];
    double aceleracao[3];
    double forca_gravitica[3];
    double forca_eletrica[3];
    double forca_resultante[3];
    bool sim_finished;
} tSim, *pSim;

#endif
