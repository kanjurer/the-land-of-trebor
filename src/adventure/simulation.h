#ifndef __SIMULATION_HEADER
#define __SIMULATION_HEADER

#include "heroes.h"
#include "lib/array_list.h"
#include "lib/queue.h"
#include <stdbool.h>

typedef struct _Args{
    bool is_complete;
    Hero* hero;
    ArrayList* path;
    ArrayList* heroesAlive;
    ArrayList* heroesDead;
} Args;

int main(int, char**);
void path_simulator(char*, ArrayList*, ArrayList*, int);
void* hero_journey(void* args);
bool save_alive(ArrayList*, char*);
bool save_dead(ArrayList*, char*);

Queue* heroesArr_queue(ArrayList*, ArrayList*, ArrayList*, ArrayList*);

#endif
