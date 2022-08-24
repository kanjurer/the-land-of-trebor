#include "simulation.h"
#include "locations.h"
#include "heroes.h"
#include "lib/array_list.h"
#include "lib/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>

sem_t wait_here_array[200];
sem_t arr_lock;

int main(int argc, char* argv[]){
    char* locationFile = "../../CI/objects/adventure/locations.lot";
    char* heroesFile   = "../../CI/objects/adventure/heroes.lot";
     
    if(argc == 1) {
        printf("Where da arg bro!\n");
        return 1;
    }

    int N;
    sscanf(argv[1], "%d", &N);
 
    if(N <= 0){
        printf("Too less threads baby!\n");
        return 1;
    } 
    if(N >= 8){
        printf("Chill out baby boiiii!\n");
        return 1;
    } 

    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    path_simulator("level"   , locationsArr_generator(locationFile, 200), heroesArr_generator(heroesFile, 300), N);
    gettimeofday(&end, NULL);
    printf("Level Time: %ld\n", (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000);
    
    gettimeofday(&start, NULL);
    path_simulator("power"   , locationsArr_generator(locationFile, 200), heroesArr_generator(heroesFile, 300), N);
    gettimeofday(&end, NULL);
    printf("Level Time: %ld\n", (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000);

    gettimeofday(&start, NULL);
    path_simulator("subtlety", locationsArr_generator(locationFile, 200), heroesArr_generator(heroesFile, 300), N);
    gettimeofday(&end, NULL);
    printf("Level Time: %ld\n", (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000);
    
    gettimeofday(&start, NULL);
    path_simulator("strategy", locationsArr_generator(locationFile, 200), heroesArr_generator(heroesFile, 300), N);
    gettimeofday(&end, NULL);
    printf("Level Time: %ld\n", (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000);

    gettimeofday(&start, NULL);
    path_simulator("charm"   , locationsArr_generator(locationFile, 200), heroesArr_generator(heroesFile, 300), N);
    gettimeofday(&end, NULL);
    printf("Level Time: %ld\n", (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000);
}

Queue* heroesArr_queue(ArrayList* heroesArr, ArrayList* path, ArrayList* heroesAlive, ArrayList* heroesDead){
    if(heroesArr   == NULL) return NULL;
    if(path        == NULL) return NULL;
    if(heroesAlive == NULL) return NULL;
    if(heroesDead  == NULL) return NULL;

    Queue* argsQueue = queue_initialize(sizeof(Args), "Args");

    for (int i = 0; i < heroesArr->size; i++) {
        Args* args        = malloc(sizeof(Args));
       
        args->is_complete = false;
        args->hero        = alist_get(heroesArr, i);
        args->path        = path;
        args->heroesAlive = heroesAlive;
        args->heroesDead  = heroesDead;
        
        queue_enqueue(argsQueue, args);
    }

    return argsQueue;
}

void path_simulator(char* pathType, ArrayList* locationsArr, ArrayList* heroesArr, int N){
    if(pathType     == NULL) return;
    if(locationsArr == NULL) return;
    if(heroesArr    == NULL) return;

    ArrayList* path        = locations_pathGenerator(locationsArr, pathType);
    ArrayList* heroesAlive = alist_initialize(300, sizeof(Hero), "Hero");
    ArrayList* heroesDead  = alist_initialize(300, sizeof(Hero), "Hero");
    
    for (int i = 0; i < path->size; i++) {
        sem_init(&wait_here_array[i], 0, 1);
    }
    
    sem_init(&arr_lock, 0, 1);

    pthread_t threadArr[N];    
    Args      argsArr[N];
    
    Queue* argsQueue = heroesArr_queue(heroesArr, path, heroesAlive, heroesDead);
    for (int i = 0; i < N; i++) {
        Args* args = queue_dequeue(argsQueue);
        argsArr[i] = *args;

        pthread_create(&threadArr[i], NULL, hero_journey, &argsArr[i]);
    }

    for (int i = 0; queue_size(argsQueue) > 0; i = (i + 1) % N) {
        if(argsArr[i].is_complete){
            pthread_join(threadArr[i], NULL);
            Args* args = queue_dequeue(argsQueue);
            argsArr[i] = *args;
            
            pthread_create(&threadArr[i], NULL, hero_journey, &argsArr[i]);
        }  
    }
    save_alive(heroesAlive, pathType); 
    save_dead(heroesDead, pathType);

    return;
}

void* hero_journey(void* voidArgs){
    if(voidArgs == NULL) return NULL;

    Args* args = voidArgs;
    for (int i = 0; i < 200; i++) {
        sem_wait(&wait_here_array[i]);
        sem_wait(&arr_lock);
        
        bool result = location_challenge(args->hero, alist_get(args->path, i), args->heroesDead, args->heroesAlive);
       
        sem_post(&arr_lock);
        sem_post(&wait_here_array[i]);    
        
        if(!result){
            break;
        } 
    }
    
    args->is_complete = true;

    return NULL;
}

bool save_alive(ArrayList* heroesAlive, char* pathType){
    if(heroesAlive == NULL) return false;
    if(pathType    == NULL) return false;

    char* filename = malloc(100);
    strcpy(filename, pathType);
    strcat(filename, "_alive");
    
    FILE* filePointer = fopen(filename, "w");

    
    if(filePointer == NULL){
        printf("File not found!\n");
        return false;
    }

    char* tmp  = malloc(1000);
    Hero* hero = NULL;
    for (int i = 0; i < heroesAlive->size; i++) {
        hero = (Hero*)alist_get(heroesAlive, i);
        
        sprintf(tmp, "%s", hero->name);
        fputs(hero->name, filePointer);
        fputs(" ", filePointer);

        sprintf(tmp, "%.2lf", hero->strength);
        fputs(tmp, filePointer);
        fputs(" ", filePointer);
        
        sprintf(tmp, "%.2lf", hero->agility);
        fputs(tmp, filePointer);
        fputs(" ", filePointer);
        
        sprintf(tmp, "%.2lf", hero->intelligence);
        fputs(tmp, filePointer);
        fputs(" ", filePointer);
        
        sprintf(tmp, "%.2lf", hero->charisma);
        fputs(tmp, filePointer);
        fputs("\n", filePointer);
    }

    fclose(filePointer);

    return true;
}
 
bool save_dead(ArrayList* heroesDead, char* pathType){
    if(heroesDead == NULL) return false;
    if(pathType    == NULL) return false;

    char* filename = malloc(100);
    strcpy(filename, pathType);
    strcat(filename, "_dead");
    
    FILE* filePointer = fopen(filename, "w");

    
    if(filePointer == NULL){
        printf("File not found!\n");
        return false;
    }

    char* tmp  = malloc(1000);
    Hero* hero = NULL;
    for (int i = 0; i < heroesDead->size; i++) {
        hero = (Hero*)alist_get(heroesDead, i);
        
        sprintf(tmp, "%s", hero->name);
        fputs(hero->name, filePointer);
        fputs(" ", filePointer);

        sprintf(tmp, "%.2lf", hero->strength);
        fputs(tmp, filePointer);
        fputs(" ", filePointer);
        
        sprintf(tmp, "%.2lf", hero->agility);
        fputs(tmp, filePointer);
        fputs(" ", filePointer);
        
        sprintf(tmp, "%.2lf", hero->intelligence);
        fputs(tmp, filePointer);
        fputs(" ", filePointer);
        
        sprintf(tmp, "%.2lf", hero->charisma);
        fputs(tmp, filePointer);
        fputs(" ", filePointer);
    
        sprintf(tmp, "%d", hero->level);
        fputs(tmp, filePointer);
        fputs(" ", filePointer);

        sprintf(tmp, "%s", hero->deathBed->name);
        fputs(tmp, filePointer);
        fputs("\n", filePointer);
    }

    fclose(filePointer);

    return true;
}
