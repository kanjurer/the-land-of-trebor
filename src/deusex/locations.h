#ifndef __LOCATIONS_HEADER
#define __LOCATIONS_HEADER
#include "lib/array_list.h"
#include <stdbool.h>

typedef struct _Location Location;

#include "heroes.h"

Location* location_initialize(char*, int, int, int, int,int);
ArrayList* locationsArr_generator(char*, int);
ArrayList* locations_pathGenerator(ArrayList*, char*);
bool location_challenge(Hero*, Location*, ArrayList*, ArrayList*);
int _heap_compare(void*, void*);
void _heap_print(void*);
int _level_compare(void*, void*);
int _power_compare(void*, void*);
int _subtlety_compare(void*, void*);
int _strategy_compare(void*, void*);
int _charm_compare(void*, void*);
void _all_print(void*);
void _location_print(Location*);

struct _Location{
    char* name;
    int level;
    int power;
    int subtlety;
    int strategy;
    int charm;
};

#endif
