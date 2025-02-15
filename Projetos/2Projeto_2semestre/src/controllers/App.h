#ifndef APP_H
#define APP_H

#include "../utils/list.h"
#include "../utils/hash_table.h"
#include "../models/app_components.h"

typedef struct {  // Aplicação
    HashTable users;
} tApp, *pApp;

/**
 * @brief Destroys the App and all its Users, Spaces and Particles.
 * 
 * @param aplication the App.
 */
void destroy_App(pApp aplication);

/**
 * @brief Destroys an User and all its Spaces and Particles.
 * 
 * @param user the User to be destroyed.
 */
void destroy_User(pUser user);

/**
 * @brief Destroys a Space and all its Particles.
 * 
 * @param space the Space to be destroyed.
 */
void destroy_Space(pSpace space);

/**
 * @brief Destroys a Particle.
 * 
 * @param particle the Particle to be destroyed.
 */
void destroy_Particle(pParticle particle);

/**
 * @brief Destroys a Simulation.
 * 
 * @param sim the Simulation to be destroyed.
 */
void destroy_Sim(pSim sim);

/**
 * @brief Creates an App.
 * 
 * @return pApp the App created.
 */
pApp app_create();

/**
 * @brief Creates a Simulation.
 * 
 * @return pUser the User created.
 */
pSim simulation_create();

/**
 * @brief Checks if two Users have the same name.
 * 
 * @return int 0 if they are equal, 1 if the first is bigger and -1 if the second is bigger.
 */
int user_names_equal(const void* a,const void* b);

/**
 * @brief Checks if an User exists.
 * 
 * @return true if it exists, false otherwise.
 */
bool user_exist(pApp aplication, char* name);

/**
 * @brief Checks if a Space exists.
 * 
 * @return true if it exists, false otherwise.
 */
bool space_exist(pApp aplication, char* name,char* identifier1);

/**
 * @brief Checks if a Space have zero simulations.
 * 
 * @return 1 if it have zero simulations, 0 otherwise.
 */
int space_with_zero_sim(pApp aplication, char* name);

/**
 * @brief Checks if a Particle exists.
 * 
 * @return true if it exists, false otherwise.
 */
bool particle_exist(pApp aplication, char* name, char* identifier1, char* identifier2);

/**
 * @brief Checks if the parameters of the particle are valid.
 * 
 * @return true if they are valid, false otherwise.
 */
bool parameters(pSim simulation, char* time_in_char, char* step_time_in_char);

/**
 * @brief Puts all the dinamic particle struct values in the simulation struct. 
 * 
 */
void particle_to_sim(pApp aplication, pSim simulation, char* name, char* identifier1, char* identifier2);

/**
 * @brief Regists an User.
 * 
 * @param aplication the App.
 * @param name the name of the User.
 */
void regist_user(pApp aplication, char* name);

/**
 * @brief Removes an User.
 * 
 * @param aplication the App.
 * @param name the name of the User.
 */
void remove_user(pApp aplication, char* name);

/**
 * @brief Makes a list of all Users with their Spaces and their Simulations performed.
 * 
 * @param aplication the App.
 */
pUser* users_list(pApp aplication);

/**
 * @brief Regists a Simulation Space.
 * 
 * @param aplication the App.
 * @param name the name of the User.
 * @return The simulation space id.
 */
int regist_simulation_space(pApp aplication, char* name);

/**
 * @brief Removes a Simulation Space.
 * 
 * @param aplication the App.
 * @param name the name of the User.
 * @param identifier1 the identifier of the Space.
 */
void remove_simulation_space(pApp aplication, char* name, char* identifier1);

/**
 * @brief Regist a Particle.
 * 
 * @param aplication the App.
 * @param name the name of the User.
 * @param identifier1 the identifier of the Space.
 * @param input2 the mass and charge of the Particle.
 * @param input3 the position of the Particle.
 * @param input4 the velocity of the Particle.
 * @return -1 if the Particle position is invalid, -2 if the mass is invalid, or the Particle id if it was regist.
 */
int regist_particle(pApp aplication, char* name, char* identifier1, char* input2, char* input3, char* input4);

/**
 * @brief Changes a Particle.
 * 
 * @param aplication the App.
 * @param name the name of the User.
 * @param identifier1 the identifier of the Space.
 * @param identifier2 the identifier of the Particle.s
 * @return -1 if the Particle position is NULL, -2 if the mass is invalid.
 */
int change_particle(pApp aplication, char* name, char* identifier1, char* identifier2, char* input2, char* input3, char* input4);

/**
 * @brief Removes a Particle.
 * 
 * @param aplication the App.
 * @param name the name of the User.
 * @param identifier1 the identifier of the Space.
 * @param identifier2 the identifier of the Particle.
 */
void remove_particle(pApp aplication, char* name, char* identifier1, char* identifier2);

/**
 * @brief Makes a step of the simulation and regist all the results in the simulation struct.
 * 
 * @param space1 the Space.
 * @param identifier2 the identifier of the Dynamic Particle.
 */
void simulation_step(pSim simulation, pSpace space1, char* identifier2);

#endif
