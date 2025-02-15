#define _POSIX_C_SOURCE 200809L
#define K 8900000000
#define G 0.0000000000667

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {  // partícula
    int particle_identifier;
    double carga_Particula;
    double massa_Particula;
    double posicao_Inicial[3];  // vector de 3 posições
    double velocidade_Inicial[3];
    double aceleracao_Inicial[3];
} tParticle, *pParticle;

typedef struct {  // simulação
    pParticle *Particles;
    int num_part;
    int sim_time;
    int num_steps;
    int step_time;
    int instant_time;        // t
    double posicao[3];  // vector de 3 posições
    double velocidade[3];
    double aceleracao[3];
    double forca_gravitica[3];
    double forca_eletrica[3];
    double forca_resultante[3];
    bool sim_finished;
} tSim, *pSim;

int main() {
    FILE *file;
    pSim sim = (pSim)malloc(sizeof(tSim));
    sim->Particles = NULL;

    printf("Escreva o número de partículas a serem registadas.\n");  // pede o número de partículas
    scanf("%d", &sim->num_part);

    sim->Particles = realloc(sim->Particles, ((sizeof(pParticle)) * sim->num_part));

    printf("Escreva o tempo da simulação.\n");  // pede o tempo da simulação
    scanf("%d", &sim->sim_time);

    printf("Escreva o tempo de cada passo da simulação.\n");  // pede o tempo de cada passo da simulação
    scanf("%d", &sim->step_time);

    for (int i = 0; i < sim->num_part; i++) {
        pParticle particle = malloc(sizeof(tParticle));

        particle->particle_identifier = i + 1;

        printf("Escreva a massa da partícula %d.\n", particle->particle_identifier);  // pede a massa da partícula
        scanf("%lf", &particle->massa_Particula);

        printf("Escreva a carga da partícula %d.\n", particle->particle_identifier);  // pede a carga da partícula
        scanf("%lf", &particle->carga_Particula);

        printf("Escreva a posição da partícula %d.\n", particle->particle_identifier);  // pede a posição da partícula
        scanf("%lf", &particle->posicao_Inicial[0]);
        scanf("%lf", &particle->posicao_Inicial[1]);
        scanf("%lf", &particle->posicao_Inicial[2]);

        particle->velocidade_Inicial[0] = 0;
        particle->velocidade_Inicial[1] = 0;
        particle->velocidade_Inicial[2] = 0;

        printf("Escreva a velocidade inicial %d.\n", particle->particle_identifier);  // pede a velocidade inicial da partícula
        scanf("%lf", &particle->velocidade_Inicial[0]);
        scanf("%lf", &particle->velocidade_Inicial[1]);
        scanf("%lf", &particle->velocidade_Inicial[2]);

        sim->Particles[i] = particle;  // adiciona a partícula ao array
    }
    int identifier = 0;                               // identificador da partícula no array
    sim->num_steps = sim->sim_time / sim->step_time;  // calcula o número de passos

    double px = sim->Particles[identifier]->posicao_Inicial[0];         // posição em x
    double py = sim->Particles[identifier]->posicao_Inicial[1];         // posição em y
    double pz = sim->Particles[identifier]->posicao_Inicial[2];         // posição em z
    double vx = sim->Particles[identifier]->velocidade_Inicial[0];      // velocidade em x
    double vy = sim->Particles[identifier]->velocidade_Inicial[1];      // velocidade em y
    double vz = sim->Particles[identifier]->velocidade_Inicial[2];      // velocidade em z
    double ax = sim->Particles[identifier]->aceleracao_Inicial[0] = 0;  // aceleração em x
    double ay = sim->Particles[identifier]->aceleracao_Inicial[1] = 0;  // aceleração em y
    double az = sim->Particles[identifier]->aceleracao_Inicial[2] = 0;  // aceleração em z

    double dx;  // distancia em x
    double dy;  // distancia em y
    double dz;  // distancia em z

    double Fg;  // força gravitacional
    double Fe;  // força elétrica

    double hipotnusa_a;  // hipotenusa do triangulo dx e dy
    double hipotnusa_b;  // hipotenusa do triangulo dx e dz

    double fgx = 0;  // força gravitacional em x
    double fgy = 0;  // força gravitacional em y
    double fgz = 0;  // força gravitacional em z
    double fex = 0;  // força elétrica em x
    double fey = 0;  // força elétrica em y
    double fez = 0;  // força elétrica em z

    double fx = 0;  // força resultante em x
    double fy = 0;  // força resultante em y
    double fz = 0;  // força resultante em z

    int ip;
    file = fopen("Dados.csv", "a");  // abre o arquivo para escrita
    fprintf(file, "tempo, px ,py ,pz ,vx ,vy ,vz ,ax ,ay ,az ,fgx ,fgy ,fgz ,fex ,fey ,fez ,fx ,fy ,fz\n");  // cabeçalho do arquivo
    for (int i = 0; i < sim->num_steps; i++) {
        for (ip = 0; ip < sim->num_part; ip++) {
            if (ip != identifier) {
                // calcula a distancia entre as particulas
                long double distancia = sqrt(pow((sim->Particles[identifier]->posicao_Inicial[0] - sim->Particles[ip]->posicao_Inicial[0]), 2) + pow((sim->Particles[identifier]->posicao_Inicial[1] - sim->Particles[ip]->posicao_Inicial[1]), 2) + pow((sim->Particles[identifier]->posicao_Inicial[2] - sim->Particles[ip]->posicao_Inicial[2]), 2));

                dx = sim->Particles[ip]->posicao_Inicial[0] - sim->Particles[identifier]->posicao_Inicial[0];  // calcula a distancia em x entre as particulas
                dy = sim->Particles[ip]->posicao_Inicial[1] - sim->Particles[identifier]->posicao_Inicial[1];  // calcula a distancia em y entre as particulas
                dz = sim->Particles[ip]->posicao_Inicial[2] - sim->Particles[identifier]->posicao_Inicial[2];  // calcula a distancia em z entre as particulas

                Fg = G * (sim->Particles[identifier]->massa_Particula) * (sim->Particles[ip]->massa_Particula) / pow(distancia, 2);  // calcula a força gravitacional
                Fe = K * (sim->Particles[identifier]->carga_Particula) * (sim->Particles[ip]->carga_Particula) / pow(distancia, 2);  // calcula a força elétrica

                hipotnusa_a = sqrt(pow(dx, 2) + pow(dy, 2));  // calcula a hipotenusa do triangulo dx e dy
                hipotnusa_b = sqrt(pow(dx, 2) + pow(dz, 2));  // calcula a hipotenusa do triangulo dx e dz

                fgx = dx * Fg / hipotnusa_a;  // calcula a força gravitacional em x
                fgy = dy * Fg / hipotnusa_a;  // calcula a força gravitacional em y
                fgz = dz * Fg / hipotnusa_b;  // calcula a força gravitacional em z
                fex = dx * Fe / hipotnusa_a;  // calcula a força elétrica em x
                fey = dy * Fe / hipotnusa_a;  // calcula a força elétrica em y
                fez = dz * Fe / hipotnusa_b;  // calcula a força elétrica em z

                fx += fgx + fex;  // calcula a força resultante em x
                fy += fgy + fey;  // calcula a força resultante em y
                fz += fgz + fez;  // calcula a força resultante em z
            }
        }

        ax = fx / sim->Particles[identifier]->massa_Particula;  // clacula a aceleração em x
        ay = fy / sim->Particles[identifier]->massa_Particula;  // clacula a aceleração em y
        az = fz / sim->Particles[identifier]->massa_Particula;  // clacula a aceleração em z
        vx = vx + ax * sim->step_time;                          // calcula a velocidade em x
        vy = vy + ay * sim->step_time;                          // calcula a velocidade em y
        vz = vz + az * sim->step_time;                          // calcula a velocidade em z

        px = px + vx * sim->step_time + (ax * pow(sim->step_time, 2)) / 2;  // calcula a posição em x
        py = py + vy * sim->step_time + (ay * pow(sim->step_time, 2)) / 2;  // calcula a posição em y
        pz = pz + vz * sim->step_time + (az * pow(sim->step_time, 2)) / 2;  // calcula a posição em z

        sim->instant_time += sim->step_time;  // atualiza o tempo
        sim->posicao[0] = px;                 // atualiza a posição
        sim->posicao[1] = py;                 // atualiza a posição
        sim->posicao[2] = pz;                 // atualiza a posição
        sim->velocidade[0] = vx;              // atualiza a velocidade
        sim->velocidade[1] = vy;              // atualiza a velocidade
        sim->velocidade[2] = vz;              // atualiza a velocidade
        sim->aceleracao[0] = ax;              // atualiza a aceleração
        sim->aceleracao[1] = ay;              // atualiza a aceleração
        sim->aceleracao[2] = az;              // atualiza a aceleração

        sim->Particles[identifier]->posicao_Inicial[0] = px;     // atualiza a posição inicial x da partícula
        sim->Particles[identifier]->posicao_Inicial[1] = py;     // atualiza a posição inicial y da partícula
        sim->Particles[identifier]->posicao_Inicial[2] = pz;     // atualiza a posição inicial z da partícula
        sim->Particles[identifier]->velocidade_Inicial[0] = vx;  // atualiza a velocidade inicial x da partícula
        sim->Particles[identifier]->velocidade_Inicial[1] = vy;  // atualiza a velocidade inicial y da partícula
        sim->Particles[identifier]->velocidade_Inicial[2] = vz;  // atualiza a velocidade inicial z da partícula
        sim->Particles[identifier]->aceleracao_Inicial[0] = ax;  // atualiza a aceleração inicial x da partícula
        sim->Particles[identifier]->aceleracao_Inicial[1] = ay;  // atualiza a aceleração inicial y da partícula
        sim->Particles[identifier]->aceleracao_Inicial[2] = az;  // atualiza a aceleração inicial z da partícula

        sim->forca_gravitica[0] = fgx;  // atualiza a força gravitacional
        sim->forca_gravitica[1] = fgy;  // atualiza a força gravitacional
        sim->forca_gravitica[2] = fgz;  // atualiza a força gravitacional
        sim->forca_eletrica[0] = fex;   // atualiza a força elétrica
        sim->forca_eletrica[1] = fey;   // atualiza a força elétrica
        sim->forca_eletrica[2] = fez;   // atualiza a força elétrica
        sim->forca_resultante[0] = fx;  // atualiza a força resultante
        sim->forca_resultante[1] = fy;  // atualiza a força resultante
        sim->forca_resultante[2] = fz;  // atualiza a força resultante

        printf("%d, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e\n",  // imprime os dados no terminal
               sim->instant_time,
               sim->posicao[0], sim->posicao[1], sim->posicao[2],
               sim->velocidade[0], sim->velocidade[1], sim->velocidade[2],
               sim->aceleracao[0], sim->aceleracao[1], sim->aceleracao[2],
               sim->forca_gravitica[0], sim->forca_gravitica[1], sim->forca_gravitica[2],
               sim->forca_eletrica[0], sim->forca_eletrica[1], sim->forca_eletrica[2],
               sim->forca_resultante[0], sim->forca_resultante[1], sim->forca_resultante[2]);

        fprintf(file, "%d, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e\n",  // imprime os dados no arquivo
                sim->instant_time,
                sim->posicao[0], sim->posicao[1], sim->posicao[2],
                sim->velocidade[0], sim->velocidade[1], sim->velocidade[2],
                sim->aceleracao[0], sim->aceleracao[1], sim->aceleracao[2],
                sim->forca_gravitica[0], sim->forca_gravitica[1], sim->forca_gravitica[2],
                sim->forca_eletrica[0], sim->forca_eletrica[1], sim->forca_eletrica[2],
                sim->forca_resultante[0], sim->forca_resultante[1], sim->forca_resultante[2]);
    }
    fclose(file);
    return 0;
}