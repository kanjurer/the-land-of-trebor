#ifndef __HEROES_HEADER
#define __HEROES_HEADER

#include "lib/array_list.h"
#include <stdbool.h>

typedef struct _Hero Hero;


Hero* hero_initialize(char*, char*, double, double, double, double);
ArrayList* heroesArr_generator(char*, int);
bool hero_levelUp(Hero*);
double _max(double, double);
void _hero_print(Hero*);

#include "locations.h"

struct _Hero{
    char* name;
    char* heroClass;
    double strength;
    double agility;
    double charisma;
    int level;
    double intelligence;
    Location* deathBed;
};

#endif
