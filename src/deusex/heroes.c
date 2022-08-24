#include "heroes.h"
#include "lib/array_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Hero* hero_initialize(char* name, char* heroClass, double strength, double agility, double charisma, double intelligence){
    if(name == NULL)      return NULL;
    if(heroClass == NULL) return NULL;
    
    Hero* hero         = malloc(sizeof(Hero));
    
    hero->intelligence = intelligence;
    hero->level        = 0;
    hero->strength     = strength;
    hero->agility      = agility;
    hero->charisma     = charisma;
    hero->name         = malloc(100);
    hero->heroClass    = malloc(100);
    hero->deathBed     = NULL;

    strcpy(hero->name, name);
    strcpy(hero->heroClass, heroClass);

    return hero;
}


ArrayList* heroesArr_generator(char* filename, int N){
    FILE* filePointer = fopen(filename, "r");

    if(filePointer == NULL){
        printf("File not found!");
        return NULL;
    }

    if(N <= 0) return NULL;

    ArrayList* heroesArr = alist_initialize(10, sizeof(Hero), "Hero");

    char* name      = malloc(100);
    char* heroClass = malloc(100);
    char* line3     = malloc(100);
    double strength;
    double agility;
    double charisma;
    double intelligence;
    for (int i = 0; i < N; i++) {
        fgets(name, 100, filePointer);
        fgets(heroClass, 100, filePointer);
        fgets(line3, 100, filePointer);

        name[strlen(name) - 1]      = '\0';
        heroClass[strlen(name) - 1] = '\0';
        sscanf(line3, "%lf, %lf, %lf, %lf", &strength, &agility, &intelligence, &charisma);
        
        alist_add(heroesArr, hero_initialize(name, heroClass, strength, agility, charisma, intelligence));    
    }

    fclose(filePointer);

    return heroesArr;
}

bool hero_levelUp(Hero* hero){
    if(hero == NULL) return false;

    hero->level++;

    double maxVal = _max(hero->strength, _max(hero->agility, _max(hero->intelligence, hero->charisma)));

    if(maxVal == hero->strength){
        hero->strength     += 0.35;
        hero->agility      += 0.25;
        hero->intelligence += 0.25;
        hero->charisma     += 0.25;

        return true;
    }
    
    if(maxVal == hero->agility){
        hero->strength     += 0.25;
        hero->agility      += 0.35;
        hero->intelligence += 0.25;
        hero->charisma     += 0.25;

        return true;
    }
    
    if(maxVal == hero->intelligence){
        hero->strength     += 0.25;
        hero->agility      += 0.25;
        hero->intelligence += 0.35;
        hero->charisma     += 0.25;

        return true;
    }
    
    if(maxVal == hero->charisma){
        hero->strength     += 0.25;
        hero->agility      += 0.25;
        hero->intelligence += 0.25;
        hero->charisma     += 0.35;

        return true;
    }

    return false;
}

double _max(double a, double b){
    if(a > b) return a;
    
    return b;
}

void _hero_print(Hero* hero){
    if(hero == NULL) return;

    printf("%s: %d, %lf, %lf, %lf, %lf\n", hero->name, hero->level, hero->strength, hero->agility, hero->intelligence, hero->charisma);
}
