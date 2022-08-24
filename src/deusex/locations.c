#include "locations.h"
#include "heroes.h"
#include "lib/array_list.h"
#include "lib/heap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Location* location_initialize(char* name, int level, int power, int subtlety, int strategy, int charm){
    if(name == NULL) return NULL;
    
    Location* location = malloc(sizeof(Location));
    location->level    = level;
    location->power    = power;
    location->subtlety = subtlety;
    location->strategy = strategy;
    location->charm    = charm;
    location->name     = malloc(100);
    
    strcpy(location->name, name);
 
    return location;
}

ArrayList* locationsArr_generator(char* filename, int N){
    FILE* filePointer = fopen(filename, "r");

    if(filePointer == NULL){
        printf("File not found!");
        return NULL;
    }

    if(N <= 0) return NULL;

    ArrayList* locationsArr = alist_initialize(10, sizeof(Location), "Location");     
    
    char* line2 = malloc(100);
    char* name  = malloc(100);
    int level;
    int power;
    int subtlety;
    int charm;
    int strategy;
    for (int i = 0; i < N; i++) {
        fgets(name, 100, filePointer);
        fgets(line2, 100, filePointer);
        
        name[strlen(name) - 1] = '\0';
        sscanf(line2, "%d, %d, %d, %d, %d", &level, &power, &subtlety, &strategy, &charm);     
        
        alist_add(locationsArr, location_initialize(name, level, power, subtlety, strategy, charm));
    }

    fclose(filePointer);

    return locationsArr;
}

ArrayList* locations_pathGenerator(ArrayList* locationsArr, char* pathType){
    if(locationsArr == NULL || pathType == NULL) return NULL;

    Heap* locationsHeap;
    
    if(strcmp(pathType, "level") == 0){
        locationsHeap = heap_initialize(sizeof(Location), "Location", _level_compare,    _heap_print);
    }else if(strcmp(pathType, "power") == 0){
        locationsHeap = heap_initialize(sizeof(Location), "Location", _power_compare,    _heap_print);
    }else if(strcmp(pathType, "subtlety") == 0){
        locationsHeap = heap_initialize(sizeof(Location), "Location", _subtlety_compare, _heap_print);
    }else if(strcmp(pathType, "strategy") == 0){
        locationsHeap = heap_initialize(sizeof(Location), "Location", _strategy_compare, _heap_print);
    }else if(strcmp(pathType, "charm") == 0){
        locationsHeap = heap_initialize(sizeof(Location), "Location", _charm_compare,    _heap_print); 
    }else{
        return NULL;
    }
    
    ArrayList* locationsTmp = alist_initialize(10, sizeof(Location), "Location");

    for (int i = 0; i < locationsArr->size; i++) {
        heap_insert(locationsHeap, alist_get(locationsArr, i)); //copy from locationsArr to heap
    }

    for (int i = 0; i < locationsArr->size; i++) {
        alist_add(locationsTmp, heap_remove(locationsHeap)); //remove from heap and add to array
    }

    return locationsTmp;
}

bool location_challenge(Hero* hero, Location* location, ArrayList* heroesDead, ArrayList* heroesAlive){
    if(hero        == NULL) return false;    
    if(location    == NULL) return false;
    if(heroesDead  == NULL) return false;
    if(heroesAlive == NULL) return false;

    if(hero->strength < location->power && hero->agility < location->subtlety && hero->intelligence < location->strategy && hero->charisma < location->charm){
        hero->deathBed = location;
        alist_add(heroesDead, hero);
        
        return false;
    }

    hero_levelUp(hero);

    if(hero->level == 200){
        alist_add(heroesAlive, hero);
    }

    return true;
}


void _heap_print(void* el){
    printf("%s", ((Location*)el)->name);
}

int _level_compare(void* a, void* b){
    return ((Location*)b)->level - ((Location*)a)->level; 
}

int _power_compare(void* a, void* b){
    return ((Location*)b)->power - ((Location*)a)->power; 
}

int _subtlety_compare(void* a, void* b){
    return ((Location*)b)->subtlety - ((Location*)a)->subtlety; 
}

int _strategy_compare(void* a, void* b){
    return ((Location*)b)->strategy - ((Location*)a)->strategy; 
}

int _charm_compare(void* a, void* b){
    return ((Location*)b)->charm - ((Location*)a)->charm; 
}

void _location_print(Location* l){
    if(l == NULL) return;

    printf("%s: %d, %d, %d, %d, %d\n", l->name, l->level, l->power, l->subtlety, l->strategy, l->charm);
}
